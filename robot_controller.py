import cv2
import time
from inference_sdk import InferenceHTTPClient
import serial

# Initialize the Roboflow inference client
CLIENT = InferenceHTTPClient(
    api_url="https://detect.roboflow.com",
    api_key="KpESVmh32WW0iQhdnckC"
)

# Initialize the serial connection to the Arduino
arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)  

# Initialize the camera
cap = cv2.VideoCapture(0)

cap.set(cv2.CAP_PROP_FRAME_WIDTH, 4)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 3)

def send_to_arduino(command):
    
    #Sends a command to the Arduino via serial communication.
    command += '\n'  
    arduino.write(command.encode('utf-8'))
    print(f"Sent to Arduino: {command.strip()}")

def move_to_object():
    #Moves the robot toward the detected object based on its position in the frame.
    send_to_arduino("Forward")

def stop_at_object():
    
    #Stops the robot if it is close enough to the detected object.
  
    send_to_arduino("STOP")

def main():
    while True:
        ret, frame = cap.read()
        if not ret:
            print("Error: Unable to read from camera.")
            break
        
        # Save the current frame for inference
        cv2.imwrite('current_frame.jpg', frame)
        
        # Run inference on the captured frame
        try:
            result = CLIENT.infer('current_frame.jpg', model_id="trash-plastic-bottle-detection-rr50p/1")
        except Exception as e:
            print(f"Inference error: {e}")
            continue
        
        # Parse predictions
        predictions = result.get('predictions', [])
        print(predictions)  # For debugging

        object_detected = False  # Flag to track if plastic bottle is detected with sufficient confidence

        # Check for plastic bottles in the predictions
        for prediction in predictions:
            label = prediction.get('class', '')
            confidence = prediction.get('confidence', 0)
            send_to_arduino(str(confidence))
        # If no plastic bottle with sufficient confidence is detected, stop the robot
        if not object_detected:
            stop_at_object()

        # Display the frame with bounding boxes
        
        cv2.imshow("Plastic Bottle Detection", frame)

        # Wait and allow the user to exit with 'q'
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        # Pause for 0.5 seconds between frames
        time.sleep(0.5)

    # Release resources
    cap.release()
    cv2.destroyAllWindows()
    arduino.close()

if __name__ == "__main__":
    main()
