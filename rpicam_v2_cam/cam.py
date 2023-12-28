import picamera
import keyboard
import threading
import time

def handle_keys(camera):
    is_recording = False
    video_path = ""

    print("Press 'p' to take a photo.")
    print("Press 'r' to start/stop recording.")
    print("Press 'q' to quit.")

    while True:
        if keyboard.is_pressed('p'):
            # Capture a photo
            photo_name = f"photo_{int(time.time())}.jpg"
            camera.capture(photo_name)
            print(f"Photo captured: {photo_name}")
            time.sleep(0.5)  # Avoid multiple captures for a single key press

        if keyboard.is_pressed('r'):
            if is_recording:
                # Stop recording
                camera.stop_recording()
                print(f"Video saved: {video_path}")
                is_recording = False
            else:
                # Start recording
                video_path = f"video_{int(time.time())}.h264"
                camera.start_recording(video_path)
                print("Recording started.")
                is_recording = True
            time.sleep(0.5)  # Avoid toggle too quickly

        if keyboard.is_pressed('q'):
            if is_recording:
                # Stop recording before quitting
                camera.stop_recording()
                print(f"Video saved: {video_path}")
            print("Exiting.")
            camera.stop_preview()
            break

        time.sleep(0.1)  # Reduce CPU usage

def main():
    # Initialize the camera
    with picamera.PiCamera() as camera:
        camera.resolution = (640, 480)
        camera.start_preview()

        # Start the thread for handling keys
        key_thread = threading.Thread(target=handle_keys, args=(camera,))
        key_thread.start()

        # Keep the program running
        key_thread.join()

if __name__ == "__main__":
    main()

