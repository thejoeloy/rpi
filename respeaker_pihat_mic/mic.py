import pyaudio
import numpy as np
import matplotlib
matplotlib.use('TKAgg')
import matplotlib.pyplot as plt

print(plt.get_backend())

# Initialize PyAudio
p = pyaudio.PyAudio()

# Open stream with specified input_device_index for ReSpeaker
try:
    stream = p.open(format=pyaudio.paInt16,
                    channels=2,
                    rate=48000,
                    input=True,
                    frames_per_buffer=4096,
                    input_device_index=2)
except IOError as e:
    print(f"Failed to open stream: {e}")

# Set interactive mode for matplotlib
plt.ion()

# Initialize plots
fig, axs = plt.subplots(4, 1)  # 4 subplots: 2 for waveforms and 2 for FFT
fig.suptitle('Real-time audio waveform and FFT')

left_line, = axs[0].plot([], [], lw=2)
right_line, = axs[1].plot([], [], lw=2)
left_fft_line, = axs[2].plot([], [], lw=2)
right_fft_line, = axs[3].plot([], [], lw=2)

while True:
    try:
        # Read some data
        data = stream.read(4096, exception_on_overflow=False)
        audio_data = np.frombuffer(data, dtype=np.int16)

        # Separate stereo channels
        left_channel = audio_data[0::2]
        right_channel = audio_data[1::2]

        # Create time axis in seconds
        time_axis = np.linspace(0, len(left_channel) / 48000., num=len(left_channel))

        # FFT
        left_fft = np.abs(np.fft.fft(left_channel))[:len(left_channel)//2]  # Taking only positive frequencies
        right_fft = np.abs(np.fft.fft(right_channel))[:len(right_channel)//2]
        freq_axis = np.linspace(0, 48000//2, len(left_fft))

        # Update waveform plots
        left_line.set_data(time_axis, left_channel)
        right_line.set_data(time_axis, right_channel)

        # Update FFT plots
        left_fft_line.set_data(freq_axis, left_fft)
        right_fft_line.set_data(freq_axis, right_fft)

        # Update plot limits
        for ax in axs:
            ax.relim()
            ax.autoscale_view()

        # Draw plot
        plt.draw()
        plt.pause(0.01)

    except KeyboardInterrupt:
        break

# Close stream
stream.stop_stream()

