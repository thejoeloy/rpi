#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

#define PCM_CAPTURE_DEVICE "hw:1" // Your microphone device (card 1)
#define PCM_PLAYBACK_DEVICE "hw:2" // Your speaker device (card 2)
#define BUFFER_SIZE 1024  // Number of frames to capture/play per period

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    snd_pcm_t *capture_handle, *playback_handle;
    snd_pcm_hw_params_t *capture_params, *playback_params;
    snd_pcm_uframes_t frames;
    int err;

    // Open capture device (microphone)
    if ((err = snd_pcm_open(&capture_handle, PCM_CAPTURE_DEVICE, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
        error("Error opening capture device");
    }

    // Open playback device (speaker)
    if ((err = snd_pcm_open(&playback_handle, PCM_PLAYBACK_DEVICE, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        error("Error opening playback device");
    }

    // Set hardware parameters for capture device
    snd_pcm_hw_params_alloca(&capture_params);
    if ((err = snd_pcm_hw_params_any(capture_handle, capture_params)) < 0) {
        error("Error setting capture device parameters");
    }
    if ((err = snd_pcm_hw_params_set_access(capture_handle, capture_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        error("Error setting capture access type");
    }
    if ((err = snd_pcm_hw_params_set_format(capture_handle, capture_params, SND_PCM_FORMAT_S16_LE)) < 0) {
        error("Error setting capture format");
    }

    unsigned int rate = 44100;
    if ((err = snd_pcm_hw_params_set_rate_near(capture_handle, capture_params, &rate, 0)) < 0) {
        error("Error setting capture rate");
    }
    if ((err = snd_pcm_hw_params_set_channels(capture_handle, capture_params, 1)) < 0) {
        error("Error setting capture channels");
    }
    if ((err = snd_pcm_hw_params(capture_handle, capture_params)) < 0) {
        error("Error applying capture parameters");
    }

    // Set hardware parameters for playback device
    snd_pcm_hw_params_alloca(&playback_params);
    if ((err = snd_pcm_hw_params_any(playback_handle, playback_params)) < 0) {
        error("Error setting playback device parameters");
    }
    if ((err = snd_pcm_hw_params_set_access(playback_handle, playback_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        error("Error setting playback access type");
    }
    if ((err = snd_pcm_hw_params_set_format(playback_handle, playback_params, SND_PCM_FORMAT_S16_LE)) < 0) {
        error("Error setting playback format");
    }

    if ((err = snd_pcm_hw_params_set_rate_near(playback_handle, playback_params, 32000, 0)) < 0) {
        error("Error setting playback rate");
    }
    if ((err = snd_pcm_hw_params_set_channels(playback_handle, playback_params, 2)) < 0) {
        error("Error setting playback channels");
    }
    if ((err = snd_pcm_hw_params(playback_handle, playback_params)) < 0) {
        error("Error applying playback parameters");
    }

    // Allocate a buffer to store audio data
    short *buffer = (short *)malloc(BUFFER_SIZE * 2 * sizeof(short)); // 2 bytes per sample (16-bit)

    // Capture and playback loop
    while (1) {
        // Capture audio from microphone
        if ((err = snd_pcm_readi(capture_handle, buffer, BUFFER_SIZE)) < 0) {
            error("Error capturing audio");
        }

        // Play the captured audio through the speaker
        if ((err = snd_pcm_writei(playback_handle, buffer, BUFFER_SIZE)) < 0) {
            error("Error playing audio");
        }
    }

    // Clean up
    free(buffer);
    snd_pcm_close(capture_handle);
    snd_pcm_close(playback_handle);

    return 0;
}

