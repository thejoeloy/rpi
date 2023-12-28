import pyaudio
import numpy as np
import matplotlib.pyplot as plt

# Initialize PyAudio
p = pyaudio.PyAudio()

# Open stream
stream = p.open(format=pyaudio.paInt16, channels=2, rate=44100, input=True, frames_per_buffer=1024)

# Set interactive mode
plt.ion()

fig, axs = plt.subplots(2)
fig.suptitle('Real-time audio waveform')
left_line, = axs[0].plot([], [], lw=2)
right_line, = axs[1].plot([], [], lw=2)

while True:
    try:
        # Read some data
        data = stream.read(1024)
        audio_data = np.fromstring(data, dtype=np.int16)

        # Separate stereo channels
        left_channel = audio_data[0::2]
        right_channel = audio_data[1::2]

        # Create time axis in seconds
        time_axis = np.linspace(0, len(left_channel) / 44100., num=len(left_channel))

        # Update plot data
        left_line.set_data(time_axis, left_channel)
        right_line.set_data(time_axis, right_channel)

        # Update plot limits
        axs[0].relim()
        axs[0].autoscale_view()
        axs[1].relim()
        axs[1].autoscale_view()

        # Draw plot
        plt.draw()
        plt.pause(0.01)

    except KeyboardInterrupt:
        break

# Close stream
stream.stop_stream()
stream.close()
p.terminate()
