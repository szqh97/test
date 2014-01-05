#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/fifo.h"

#include <stdio.h>

/* 单通道下，每个sample所占的字节数
	AV_SAMPLE_FMT_FLT = 4bytes
	AV_SAMPLE_FMT_S16 = 2bytes
*/
static int g_in_bytes = 2;
static int g_out_bytes = 2;

AVCodecContext* output_decode_init(AVCodecContext* in_cctx, AVFormatContext* out_fctx, int codec_id);
int output_decode_open(AVCodecContext* cc);

int main(int argc, char* argv[])
{
	AVFormatContext* in_fctx;	
	AVCodecContext* in_cctx;
	AVCodec* in_codec;
	const char* in_filename;
	const char* out_filename;
	char* decoded_buf;
	char* output_buf;
	char* resample_buf;
	char* before_encoding_buf;
	int ret = 0;

	if (argc != 3)
	{
		printf("./audio_convertor input ouput\n");
		return -1;
	}
	//in_filename = "../input/input.aac";
	//out_filename = "output/aac2mp3.mp3";
	in_filename = argv[1];
	out_filename = argv[2];
	decoded_buf = (char*)av_malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE);
	output_buf = (char*)av_malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE);
	resample_buf = (char*)av_malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE); 
	before_encoding_buf = (char*)av_malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE); 

	avcodec_register_all();
	av_register_all();

	in_fctx = avformat_alloc_context();

	ret = av_open_input_file(&in_fctx, in_filename, NULL, 0, NULL);
	if ( ret != 0 )
	{
		printf("open input audio file[%s] fail\n", in_filename);
		return -1;
	}

	ret = av_find_stream_info(in_fctx);
	if ( ret < 0 )
	{
		printf("find stream in audio file[%s] fail\n", in_filename);
		return -1;
	}

	dump_format(in_fctx, 0, in_filename, 0);

	//这里我们假设，如果一个文件包含多个音频流，
	//只对第一个音频流做转码，而对于视频流则忽略
	int i;
	int ast_index = -1;
	for (i = 0; i<(int)in_fctx->nb_streams; ++i)
	{
		if (in_fctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			ast_index = i;
			break;
		}
	}
	if (ast_index == -1)
	{
		printf("there is not any audio stream in file[%s]\n", in_filename);
		return 0;
	}
	else
	{
		printf("find audio stream in file[%s]\n", in_filename);
	}
	
	in_cctx = in_fctx->streams[ast_index]->codec;
	//in_cctx->codec_id = CODEC_ID_GSM;
	in_codec = avcodec_find_decoder(in_cctx->codec_id);
	if (!in_codec)
	{
		printf("find decoder for codec_id[%d] fail, file[%s]\n", in_cctx->codec_id, in_filename);
		return -1;
	}
	ret = avcodec_open(in_cctx, in_codec);
	if (ret >= 0)
	{
		printf("open codec[name:%s] for stream[idx:%d] of file[%s]\n", in_codec->name, ast_index, in_filename);
	}

	// 输出部分初始化
	AVOutputFormat* out_fmt;
	AVFormatContext* out_fctx;
	AVCodecContext* out_cctx = NULL;

	out_fmt = av_guess_format(NULL, out_filename, NULL);
	if (!out_fmt)
	{
		printf("Could not deduce output format from file extension: using MPEG-3.\n");
		out_fmt = av_guess_format("mp3", NULL, NULL);
	}
	if (!out_fmt)
	{
		fprintf(stderr, "Could not find suitable output format\n");
		exit(1);
	}

	out_fctx = avformat_alloc_context();
	if (!out_fctx)
	{
		fprintf(stderr, "avformat_alloc_context fail\n");
		exit(1);
	}
	out_fctx->oformat = out_fmt;

	out_cctx = output_decode_init(in_cctx, out_fctx, out_fmt->audio_codec);
	if (!out_cctx)
	{
		fprintf(stderr, "output_codec_init fail\n");
		exit(1);
	}
	/* set the output parameters (must be done even if no parameters). */
	if (av_set_parameters(out_fctx, NULL) < 0) 
	{
		fprintf(stderr, "Invalid output format parameters\n");
		exit(1);
	}
	dump_format(out_fctx, 0, out_filename, 1);

	output_decode_open(out_cctx);

	/* open the output file */
	if (!(out_fmt->flags & AVFMT_NOFILE)) 
	{
		if (url_fopen(&out_fctx->pb, out_filename, URL_WRONLY) < 0)
		{
			fprintf(stderr, "Could not open '%s'\n", out_filename);
			exit(1);
		}
	}
	/* write the stream header, if any */
	if(av_write_header(out_fctx) < 0)
	{
		fprintf(stderr, "Could not write header for output file\n");
		return -1;
	}

	int decoded_size;
	AVPacket in_packet;
	AVPacket out_packet;
	ReSampleContext *rs_ctx = NULL;
	/*
	参考链接：http://hi.baidu.com/wg_wang/item/34396781d20b4b1ec316270b
	两点需要注意：
	(1) 从输入文件中按帧读取数据，解码，按照输出文件的要求，编码，并按帧写入到输出文件中。
	在这里，由于sample_rate和channels可能不同，需要对音频数据进行重采样。
	(2) 由于不同编码类型对一帧音频的数据要求不同，可能需要将输入数据保存起来，直到够输出的编码使用，
	或者，一帧的输入数据可能需要被多次输出。
	这样，要求初始化重采样以及libavutil提供的fifo（libavutils/fifo.h声明）以临时保存数据。
	举个例子：aac的frame_size=1024,mp3的frame_size=1152。若不用这个fifo，则生成的mp3文件是有问题的
	*/
	// 设置从采样
	rs_ctx = av_audio_resample_init(
				out_cctx->channels, in_cctx->channels,
				out_cctx->sample_rate, in_cctx->sample_rate,
				out_cctx->sample_fmt, in_cctx->sample_fmt,
				16, 10, 0, 0.8);

	AVFifoBuffer *iofifo;
	iofifo = av_fifo_alloc(AVCODEC_MAX_AUDIO_FRAME_SIZE*2);
	av_init_packet(&in_packet);
	av_init_packet(&out_packet);

	while (av_read_frame(in_fctx, &in_packet) >= 0)
	{
		while (in_packet.size > 0)
		{
			int used_size;
			decoded_size = AVCODEC_MAX_AUDIO_FRAME_SIZE;
			used_size = avcodec_decode_audio3(in_cctx, (int16_t *)decoded_buf, &decoded_size, &in_packet);
			if (used_size < 0)
			{
				printf("avcodec_decode_audio3 fail\n");
				exit(1);
			}
			int bs, frame_bytes;

			bs = audio_resample(rs_ctx, (short *)resample_buf, (short *)decoded_buf, decoded_size/(in_cctx->channels*g_in_bytes));
			ret = av_fifo_generic_write(iofifo, (uint8_t *)resample_buf, bs*out_cctx->channels*g_out_bytes, NULL);
			//ret = av_fifo_generic_write(iofifo, (uint8_t *)decoded_buf, in_cctx->frame_size*in_cctx->channels*g_out_bytes, NULL);

			frame_bytes = out_cctx->frame_size * g_out_bytes * out_cctx->channels;
			while(av_fifo_size(iofifo) >= frame_bytes)
			{
				ret = av_fifo_generic_read(iofifo, before_encoding_buf, frame_bytes, NULL);
				out_packet.size = avcodec_encode_audio(out_cctx, (uint8_t*)output_buf, frame_bytes, (short *)before_encoding_buf);
				out_packet.data = (uint8_t *)output_buf;
				av_write_frame(out_fctx, &out_packet);
			}

			in_packet.size -= used_size;
			in_packet.data += used_size;
		}
	}
	/* write the trailer, if any */
	av_write_trailer(out_fctx);
	if (!(out_fmt->flags & AVFMT_NOFILE)) {
		/* close the output file */
		url_fclose(out_fctx->pb);
	}
}

int output_decode_open(AVCodecContext* cc)
{
	AVCodec *codec;

	/* find the audio encoder */
	codec = avcodec_find_encoder(cc->codec_id);
	if (!codec) 
	{
		fprintf(stderr, "codec not found\n");
		exit(1);
	}

	/* open it */
	if (avcodec_open(cc, codec) < 0) {
		fprintf(stderr, "could not open audio codec\n");
		exit(1);
	}

	return 0;
}

AVCodecContext* output_decode_init(AVCodecContext* in_cctx, AVFormatContext* out_fctx, int codec_id)
{
	AVCodecContext *cc;
	AVStream *st;

	st = av_new_stream(out_fctx, 0);
	if (!st) 
	{
		fprintf(stderr, "Could not alloc stream\n");
		exit(1);
	}
	
	cc = st->codec;
	//cc->codec_id = (CodecID)codec_id;
	cc->codec_id = codec_id;
	cc->codec_type = AVMEDIA_TYPE_AUDIO;
	/* 
	   google keep的录音笔记的sample_fmt的格式为AV_SAMPLE_FMT_FLT
	*/
	cc->sample_fmt = AV_SAMPLE_FMT_S16;  // 默认采用AV_SAMPLE_FMT_S16
	//cc->sample_fmt = in_cctx->sample_fmt;
	if (in_cctx->sample_fmt == AV_SAMPLE_FMT_FLT)
	{
		g_in_bytes = 4;
	}
	if (cc->sample_fmt == AV_SAMPLE_FMT_S16)
	{
		g_out_bytes = 2;
	}
	

	if (codec_id == CODEC_ID_AMR_NB)
	{
		cc->channels = 1;
		cc->bit_rate = 12200;
	}
	else
	{
		cc->channels = in_cctx->channels;
		cc->bit_rate = in_cctx->bit_rate;
	}
	//cc->sample_rate = in_cctx->sample_rate;
	//cc->sample_rate = 44100;
	cc->sample_rate = 8000;
	
	return cc;
}
