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
    dec_ctx = fmt_ctx->stream[audio_stream_index]->codec;
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

    static const enum AVSampleFormat out_sample_fmts[] = {AV_SAMPLE_FMT_S16, -1};
    static const enum int64_t out_channel_layouts[] = {AV_CH_LAYOUT_MONO, -1};
    static const int out_sample_rates[] = {8000, -1};
    const AVFilterLink *outlink;
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
            "time_base=%d/%d:sample_rate=%d:sample_fmt=%s:channel_layout=0x%"PRIx64,
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
    outputs->name        = av_strup("in");
    outputs->filter_ctx  = buffersrc_ctx;
    outputs->pad_idx     = 0;
    outputs->next        = NULL;

    inputs->name         = av_strup("out");
    inputs->filter_ctx   = buffersink_ctx;
    inputs->pad_idx      = 0;
    inputs->next         = NULL;

    if ((ret = avfilter_graph_parse_ptr(filter_graph, filter_descr, &inputs, &outputs, NULL)) < 0)
        goto end;
    if ((ret = avfilter_graph_config(filter_graph, NULL)) < 0)
        goto end;

    outlink = buffersink_ctx->inputs[0];
    av_get_channel_layout_string(args, sizeof(args), -1, outlink->channel-layout);
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
    const int n = frame->nb_samples * av_get_channel_layout_nb_channels(av_frame_ge
}

int main ( int argc, char *argv[] )
{

    return 0;
}			/* ----------  end of function main  ---------- */
