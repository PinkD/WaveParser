#include "play.h"
#include "../log.h"

#include <AL/al.h>
#include <AL/alc.h>


static inline ALenum to_al_format(short channels, short samples) {
    int stereo = (channels > 1);
    switch (samples) {
        case 16:
            if (stereo) {
                return AL_FORMAT_STEREO16;
            } else {
                return AL_FORMAT_MONO16;
            }
        case 8:
            if (stereo) {

                return AL_FORMAT_STEREO8;
            } else {
                return AL_FORMAT_MONO8;
            }
        default:
            return -1;
    }
}


void play(Wave *wave) {
    ALCdevice *device = alcOpenDevice(NULL);

    if (!device) {
        log_e("Fail to open device");
        return;
    }

    ALCcontext *context = alcCreateContext(device, NULL);
    if (!alcMakeContextCurrent(context)) {
        log_e("Fail to make context");
        return;
    }

    ALfloat listenerOri[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};

    alListener3f(AL_POSITION, 0, 0, 1.0f);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListenerfv(AL_ORIENTATION, listenerOri);

    ALuint source;

    alGenSources(1, &source);

    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);


    ALuint buffer;
    alGenBuffers(1, &buffer);


    WaveData *data = wave->data;
    while (!(data->data_chunk_header[0] == 'd' &&
             data->data_chunk_header[1] == 'a' &&
             data->data_chunk_header[2] == 't' &&
             data->data_chunk_header[3] == 'a')) {
        data = data->next;
        if (!data) {
            log_w("no available data to play");
            return;
        }
    }

    byte *bufferData = malloc(data->data_size);
    memcpy(bufferData, data->data, data->data_size);
    alBufferData(buffer,
                 to_al_format(wave->header->fmt.channel, wave->header->fmt.bits_per_sample),
                 bufferData,
                 data->data_size,
                 wave->header->fmt.sample_rate);


    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);

    ALint source_state;
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    while (source_state == AL_PLAYING) {
        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    }

    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    alcMakeContextCurrent(NULL);

    alcDestroyContext(context);
    alcCloseDevice(device);
    free(bufferData);
}
