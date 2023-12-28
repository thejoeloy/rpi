import sounddevice as sd
import numpy as np

def callback(indata, frames, time, status):
    print(f"indata: {indata}")

# List available audio devices
print(sd.query_devices())

# Choose the appropriate device and channel (change these as needed)
device_id = 1  # Replace with the ID of your device
channels = 1   # Number of channels

# Create an input audio stream
with sd.InputStream(device=device_id, channels=channels, callback=callback):
    while True: pass  # Keep the program running
