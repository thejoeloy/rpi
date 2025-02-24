#include <stdio.h>
#include <alsa/asoundlib.h>

void print_device_info(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, const char *name) {
    snd_pcm_info_t *info;
    snd_pcm_info_alloca(&info);

    if (snd_pcm_info(pcm, info) < 0) {
        printf("Error getting device info for %s\n", name);
        return;
    }

    const char *device_name = snd_pcm_info_get_name(info);
    const char *device_id = snd_pcm_info_get_id(info);
    snd_pcm_stream_t stream_type = snd_pcm_info_get_stream(info);

    printf("\nDevice: %s (%s)\n", device_name, device_id);
    printf("Type: %s\n", (stream_type == SND_PCM_STREAM_CAPTURE) ? "Capture" : "Playback");
    printf("Device ID: %s\n", device_id);

    // Supported data formats
    printf("Supported data formats:\n");
    for (int format = SND_PCM_FORMAT_UNKNOWN + 1; format < SND_PCM_FORMAT_LAST; ++format) {
        if (snd_pcm_hw_params_test_format(pcm, params, format) == 0) {
            printf("  - %s\n", snd_pcm_format_name(format));
        }
    }

    // Supported sampling rates
    printf("Supported sampling rates:\n");
    unsigned int rate;
    for (rate = 8000; rate <= 192000; rate *= 2) {
        if (snd_pcm_hw_params_test_rate(pcm, params, rate, 0) == 0) {
            printf("  - %u Hz\n", rate);
        }
    }

    // Number of channels (mono, stereo, etc.)
    printf("Supported number of channels:\n");
    unsigned int channels;
    for (channels = 1; channels <= 8; ++channels) {
        if (snd_pcm_hw_params_test_channels(pcm, params, channels) == 0) {
            printf("  - %u channels\n", channels);
        }
    }

    // Period size and buffer size
    unsigned int period_size = 0, buffer_size = 0;
    snd_pcm_uframes_t frames;
    int dir;
    
    // Get period size and buffer size
    snd_pcm_hw_params_get_period_size(params, &frames, &dir);
    period_size = (unsigned int)frames;

    snd_pcm_hw_params_get_buffer_size(params, &frames);
    buffer_size = (unsigned int)frames;

    printf("Period size: %u\n", period_size);
    printf("Buffer size: %u\n", buffer_size);
}

void list_devices() {
    snd_ctl_card_info_t *card_info;
    snd_ctl_card_info_alloca(&card_info);

    int card = -1;
    while (snd_card_next(&card) >= 0 && card >= 0) {
        snd_ctl_t *ctl;
        
        // Get the name of the card (e.g., "hw:0", "hw:1")
        char card_name[32];
        snprintf(card_name, sizeof(card_name), "hw:%d", card);

        if (snd_ctl_open(&ctl, card_name, 0) < 0) {
            continue;
        }

        snd_ctl_card_info(ctl, card_info);
        const char *card_display_name = snd_ctl_card_info_get_name(card_info);

        printf("\nCard %d: %s\n", card, card_display_name);

        snd_pcm_t *pcm;
        snd_pcm_hw_params_t *params;
        snd_pcm_hw_params_alloca(&params);

        // Iterate over playback and capture streams
        for (snd_pcm_stream_t stream = SND_PCM_STREAM_PLAYBACK; stream <= SND_PCM_STREAM_CAPTURE; stream++) {
            if (snd_pcm_open(&pcm, card_name, stream, 0) < 0) {
                continue;
            }

            snd_pcm_hw_params_any(pcm, params);  // Initialize hardware parameters
            print_device_info(pcm, params, card_display_name);
            snd_pcm_close(pcm);  // Close PCM device after use
        }

        snd_ctl_close(ctl);
    }
}

int main() {
    printf("Listing audio capture and playback devices:\n");
    list_devices();
    return 0;
}

