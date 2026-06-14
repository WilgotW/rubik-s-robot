import serial
import time 

PORT = '/dev/cu.usbmodem11303' 
BAUD_RATE = 9600 
TIMEOUT = 5

def start_communication():
    with serial.Serial(PORT, BAUD_RATE, timeout=TIMEOUT) as ser:


def read_cube_face():
    with serial.Serial(PORT, BAUD_RATE, timeout=TIMEOUT) as ser:
        print(f"Listening on {ser.name} at {BAUD_RATE} baud...")
        print("Waiting for 9 bytes of face data...")

        raw_data = ser.read(9) #read 9 bits of data

        #Verify we got the whole facce
        if len(raw_data) == 9:
            print("\nSuccess! Received a full face.")
            
            #Convert the raw bytes into a readable list of integers or characters
            color_values = list(raw_data) 
            print(f"Data array: {color_values}")
            
            return color_values
        else:
            print(f"\nTimeout Error: Expected 9 bytes, but only received {len(raw_data)}.")
            return None

face_data = read_cube_face()