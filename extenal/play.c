#include "play.h"
#include "../log.h"

#define PCM_DEVICE "default"

void play(Wave *wave) {
    uint rate, channel, tmp;
    int ret;
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *params;
    snd_pcm_uframes_t frames;
    size_t buff_size, loops;

    rate = wave->header->fmt.sample_rate;
    channel = wave->header->fmt.channel;
//    seconds = 200;

    /* Open the PCM device in playback mode */
    if ((ret = snd_pcm_open(&pcm_handle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0)) < 0)
        printf("ERROR: Can't open \"%s\" PCM device. %s\n",
               PCM_DEVICE, snd_strerror(ret));

    /* Allocate parameters object and fill it with default values*/
    snd_pcm_hw_params_alloca(&params);

    snd_pcm_hw_params_any(pcm_handle, params);

    /* Set parameters */
    if ((ret = snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
        printf("ERROR: Can't set interleaved mode. %s\n", snd_strerror(ret));

    if ((ret = snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE)) < 0)
        printf("ERROR: Can't set format. %s\n", snd_strerror(ret));

    if ((ret = snd_pcm_hw_params_set_channels(pcm_handle, params, channel)) < 0)
        printf("ERROR: Can't set channels number. %s\n", snd_strerror(ret));

    if ((ret = snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, 0)) < 0)
        printf("ERROR: Can't set rate. %s\n", snd_strerror(ret));

    /* Write parameters */
    if ((ret = snd_pcm_hw_params(pcm_handle, params)) < 0)
        printf("ERROR: Can't set harware parameters. %s\n", snd_strerror(ret));

    /* Allocate buffer to hold single period */
    snd_pcm_hw_params_get_period_size(params, &frames, 0);

    buff_size = frames * channel * 2 /* 2 -> sample size */;
    size_t count = 0;


    snd_pcm_hw_params_get_period_time(params, &tmp, NULL);

    WaveData *data = wave->data;
    while (!(data->data_chunk_header[0] == 'd' &&
             data->data_chunk_header[1] == 'a' &&
             data->data_chunk_header[2] == 't' &&
             data->data_chunk_header[3] == 'a')
            ) {
        data = data->next;
        if (!data) {
            log_w("no available data to play");
            return;
        }
    }

    for (loops = data->data_size / buff_size; loops > 0; loops--) {
        if ((ret = (int) snd_pcm_writei(pcm_handle, data->data + count, frames)) == -EPIPE) {
            printf("XRUN.\n");
            snd_pcm_prepare(pcm_handle);
        } else if (ret < 0) {
            printf("ERROR. Can't write to PCM device. %s\n", snd_strerror(ret));
        }
        count += buff_size;
    }

    snd_pcm_drain(pcm_handle);
    snd_pcm_close(pcm_handle);

}
