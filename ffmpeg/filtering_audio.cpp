#include <iostream>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfiltergraph.h>
#include <libavfilter/avcodec.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libavutil/opt.h>
}
static const char *filter_descr = "aresample=8000, aformat=sample_fmts=s16:channel_layouts=mono";
static const char *player = "ffplay -f s16le -ac 1 -";

static AVFormatContext *fmt_ctx;
static AVCodecContext *dec_ctx;
AVFilterContext *buffersink_ctx;
AVFilterContext *buffersrc_ctx;
AVFilterGraph *filter_graph;
static int audio_stream_index = -1;

static int open_input_file(const char *filename)
{
    int ret;
    AVCodec *dec;
    if ((ret = avformat_open_input(&fmt_ctx, filename, NULL, NULL)) < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Cannot open input file\n");
        return ret;
    }

    if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
        return ret;
    }

    /* select the audio stream */
    ret = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_AUDIO, -1, -1, &dec, 0);
    if (ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Cannot find a audio stream in the input file\n");
        return ret;
    }
    audio_stream_index = ret;
    dec_ctx = fmt_ctx->streams[audio_stream_index]->codec;
    av_opt_set_int(dec_ctx, "refcounted_frames", 1, 0);

    /* init the audio decoder */
    if ((ret = avcodec_open2(dec_ctx, dec, NULL)) < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Cannot open audio decoder\n");
        return ret;
    }
    return 0;
}

static int init_filters(const char *filter_descr)
{
    char args[512];
    int ret = 0;
    AVFilter *abuffersrc = avfilter_get_by_name("abuffer");
    AVFilter *abuffersink = avfilter_get_by_name("abuffersink");
    AVFilterInOut *outputs = avfilter_inout_alloc();
    AVFilterInOut *inputs = avfilter_inout_alloc();

    static const int out_sample_fmts[] = {AV_SAMPLE_FMT_S16, -1};
    static const int64_t out_channel_layouts[] = {AV_CH_LAYOUT_MONO, -1};
    static const int out_sample_rates[] = {8000, -1};
    AVFilterLink *outlink;
    AVRational time_base = fmt_ctx->streams[audio_stream_index]->time_base;

    filter_graph = avfilter_graph_alloc();
    if (!outputs || !inputs || !filter_graph)
    {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    /*  buffer audio source; the decoded frames from the decoder 
     *  will be intrested here 
     */
    if (!dec_ctx->channel_layout)
        dec_ctx->channel_layout = av_get_default_channel_layout(dec_ctx->channels);
    sprintf(args, sizeof(args),
            "time_base=%d/%d:sample_rate=%d:sample_fmt=%s:channel_layout=0x%lld",
            time_base.num, time_base.den, dec_ctx->sample_rate,
            av_get_sample_fmt_name(dec_ctx->sample_fmt), dec_ctx->channel_layout);
    ret = avfilter_graph_create_filter(&buffersrc_ctx, abuffersrc, "in", args, NULL, filter_graph);
    if (ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Cannot create audio buffer source\n");
        goto end;
    }

    /* buffer audio sink: to terminate the filter chain */
    ret = avfilter_graph_create_filter(&buffersink_ctx, abuffersink, "out", NULL, NULL, filter_graph);
    if (ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Cannot create audio buffer sink\n");
        goto end;
    }
    ret = av_opt_set_int_list(buffersink_ctx, "sample_fmts", out_sample_fmts, -1, AV_OPT_SEARCH_CHILDREN);
    if (ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Cannot st output sample format\n");
        goto end;
    }

    ret = av_opt_set_int_list(buffersink_ctx, "channel_layouts", out_channel_layouts, -1, AV_OPT_SEARCH_CHILDREN);
    if(ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Cannot set output channel layout\n");
        goto end;
    }

    ret = av_opt_set_int_list(buffersink_ctx, "sample_rates", out_sample_rates, -1, AV_OPT_SEARCH_CHILDREN);
    if (ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Cannot set output sample rate\n");
        goto end;
    }

    /*  Endpoints for the filter graph */
    outputs->name        = av_strdup("in");
    outputs->filter_ctx  = buffersrc_ctx;
    outputs->pad_idx     = 0;
    outputs->next        = NULL;

    inputs->name         = av_strdup("out");
    inputs->filter_ctx   = buffersink_ctx;
    inputs->pad_idx      = 0;
    inputs->next         = NULL;

    if ((ret = avfilter_graph_parse_ptr(filter_graph, filter_descr, &inputs, &outputs, NULL)) < 0)
        goto end;
    if ((ret = avfilter_graph_config(filter_graph, NULL)) < 0)
        goto end;

    outlink = buffersink_ctx->inputs[0];
    av_get_channel_layout_string(args, sizeof(args), -1, outlink->channel_layout);
    av_log(NULL, AV_LOG_ERROR, "Output: srate: %dHz fmt:%s chlayout:%s\n", 
            (int)outlink->sample_rate,
            (char*)av_x_if_null(av_get_sample_fmt_name(outlink->format), "?"),
            args);
end:
    avfilter_inout_free(&inputs);
    avfilter_inout_free(&outputs);

    return ret;
}

static void print_frame(const AVFrame *frame)
{
    const int n = frame->nb_samples * av_get_channel_layout_nb_channels(av_frame_get_channel_layout(frame));
    const uint16_t *p = (uint16_t *)frame->data[0];
    const uint16_t *p_end = p + n;
    while (p < p_end)
    {
        fputc(*p    & 0xff, stdout);
        fputc(*p>>8 & 0xff, stdout);
        p++;
    }
    fflush(stdout);
}

int main ( int argc, char *argv[] )
{
    int ret;
    AVPacket packet0, packet;
    AVFrame *frame = av_frame_alloc();
    AVFrame *filt_frame = av_frame_alloc();
    int got_frame;
    
    if (!frame || !filt_frame)
    {
        perror("Could not allocate frame");
        exit(1);
    }
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s file |%s\n", argv[0], player);
        exit(1);
    }

    avcodec_register_all();
    av_register_all();
    avfilter_register_all();

    if ((ret = open_input_file(argv[1])) < 0)
        goto end;
    if ((ret = init_filters(filter_descr)) < 0)
        goto end;

    /* read all packets */
    packet0.data = NULL;
    packet.data = NULL;
    while(1) 
    {
        if (!packet0.data)
        {
            if ((ret = av_read_frame(fmt_ctx, &packet)) < 0)
                break;
            packet0 = packet;
        }

        if (packet.stream_index == audio_stream_index)
        {
            avcodec_get_frame_defaults(frame);
            got_frame = 0;
            ret = avcodec_decode_audio4(dec_ctx, frame, &got_frame, &packet);
            if (ret < 0)
            {
                av_log(NULL, AV_LOG_ERROR, "Error decoding audio\n");
                continue;
            }
            packet.size -= ret;
            packet.data += ret;
            
            if (got_frame)
            {
                /* push the audio data from decoded frame into the filtergraph */
                if (av_buffersrc_add_frame_flags(buffersrc_ctx, frame, 0) < 0)
                {
                    av_log(NULL, AV_LOG_ERROR, "ERROR while feeding the audio filtergraph\n");
                    break;
                }
                /* pull filtered audio from the filtergraph */
                while(1)
                {
                    ret = av_buffersink_get_frame(buffersink_ctx, filt_frame);
                    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                        break;
                    if (ret < 0)
                        goto end;
                    print_frame(filt_frame);
                    av_frame_unref(filt_frame);
                }
            }

            if (packet.size <= 0)
                av_free_packet(&packet0);
        }
        else
        {
            /* discard non-wanted packets */
            av_free_packet(&packet0);
        }
    }

end:
    avfilter_graph_free(&filter_graph);
    avcodec_close(dec_ctx);
    avformat_close_input(&fmt_ctx);
    av_frame_free(&frame);
    av_frame_free(&filt_frame);

    if (ret < 0 && ret != AVERROR_EOF)
    {
        fprintf(stderr, "Error ocurred: %s\n","sss");
        exit(1);
    }

    exit(0);

}			/* ----------  end of function main  ---------- */
