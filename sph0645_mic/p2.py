import sounddevice as sd
import numpy as np
import matplotlib.pyplot as plt
from queue import Queue

# Buffer for audio data
buffer_size = 1000
audio_buffer = np.zeros(buffer_size)
x_axis = np.arange(buffer_size)

# Initialize plot
plt.ion()
fig, ax = plt.subplots()
line, = ax.plot(x_axis, audio_buffer, lw=2)
ax.set_ylim(-1, 1)
ax.set_xlim(0, buffer_size)

# Queue to pass data between threads
audio_queue = Queue()

def callback(indata, frames, time, status):
    audio_queue.put(indata.flatten())

# List available audio devices
print(sd.query_devices())

# Choose the appropriate device and channel (change these as needed)
device_id = 1  # Replace with the ID of your device
channels = 1   # Number of channels

# Create an input audio stream
with sd.InputStream(device=device_id, channels=channels, callback=callback):
    try:
        while True:  # Keep the program running
            if not audio_queue.empty():
                # Append new audio data and remove old data
                new_data = audio_queue.get()
                audio_buffer = np.concatenate((audio_buffer, new_data))[-buffer_size:]
                # Update the plot
                line.set_ydata(audio_buffer)
                plt.draw()
                plt.pause(1e-7)
    except KeyboardInterrupt:
        print("Exiting...")



