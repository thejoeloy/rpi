import alsaaudio
import wave

DEVICE = "default"
CHANNELS = 1
RATE = 44100
FORMAT = alsaaudio.PCM_FORMAT_S16_LE
PERIODSIZE = 1024
DURATION = 5
FILENAME = "test.wav"

input_device = alsaaudio.PCM(alsaaudio.PCM_CAPTURE, alsaaudio.PCM_NORMAL, device=DEVICE)
input_device.setchannels(CHANNELS)
input_device.setrate(RATE)
input_device.setformat(FORMAT)
input_device.setperiodsize(PERIODSIZE)

wav_file = wave.open(FILENAME, 'wb')
wav_file.setnchannels(CHANNELS)
wav_file.setsampwidth(2)
wav_file.setframerate(RATE)

print(f"Recording {DURATION} secondsof audio...")

frames = []
for _ in range(int(RATE / PERIODSIZE * DURATION)):
    length, data = input_device.read()
    if length:
        frames.append(data)

wav_file.writeframes(b''.join(frames))
wav_file.close()

print(f"Recordingsave as {FILENAME}")
