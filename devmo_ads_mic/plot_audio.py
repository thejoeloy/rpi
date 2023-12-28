import time
import Adafruit_ADS1x15
import numpy as np
import matplotlib.pyplot as plt

# Initialize ADS1115
adc = Adafruit_ADS1x15.ADS1115()

# ADS1115 Configuration
GAIN = 1  # Gain setting (use 1 for +/- 4.096V)
SAMPLES = 1024  # Number of samples to capture for each plot
SAMPLING_RATE = 1000  # Sampling rate in Hz

# Initialize Plot
plt.ion()  # Turn on interactive mode
fig, (ax1, ax2) = plt.subplots(2, 1)

line1, = ax1.plot([], [], lw=2)
line2, = ax2.plot([], [], lw=2)

ax1.set_title("Time-domain Signal")
ax1.set_xlabel("Time [s]")
ax1.set_ylabel("Amplitude")

ax2.set_title("Frequency-domain Signal")
ax2.set_xlabel("Frequency [Hz]")
ax2.set_ylabel("Magnitude")

# Data storage
data = []

# Continuously collect and plot data
while True:
    start_time = time.time()
    
    # Collect data
    for _ in range(SAMPLES):
        value = adc.read_adc(0, gain=GAIN)
        data.append(value)
        if len(data) > SAMPLES:
            data.pop(0)
        time.sleep(1.0 / SAMPLING_RATE)
        
    end_time = time.time()

    # Convert data to NumPy array and mean-subtract
    data_np = np.array(data)
    data_np = data_np - np.mean(data_np)

    # Perform FFT
    frequencies = np.fft.fftfreq(SAMPLES, 1/SAMPLING_RATE)
    fft_values = np.fft.fft(data_np)
    
    # Update plots
    line1.set_data(np.linspace(0, SAMPLES / SAMPLING_RATE, SAMPLES), data_np)
    line2.set_data(np.abs(frequencies), np.abs(fft_values))

    ax1.relim()
    ax1.autoscale_view()
    ax2.relim()
    ax2.autoscale_view()

    plt.draw()
    plt.pause(0.01)
    
    print(f"Plot updated in {end_time - start_time:.2f} seconds.")

