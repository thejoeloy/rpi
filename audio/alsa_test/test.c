#include <alsa/asoundlib.h>
#include <stdio.h>

int main() {
	int status;
	snd_pcm_t *handle;
	status = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
	if (status < 0) {
		printf("Error : %s\n", snd_strerror(status));
		return 1;
	}
	printf("Success\n");
	return 0;
}
