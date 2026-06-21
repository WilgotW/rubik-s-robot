import serial
import time 

PORT = '/dev/cu.usbmodem11303' 
BAUD_RATE = 9600 
TIMEOUT = 5

def send_rotation_commands(solve_commands):
    with serial.Serial(PORT, BAUD_RATE, timeout=TIMEOUT) as ser:
        print("Initiating solve sequence...")
        ser.write(b'S')
            
        #wait for ACK
        ack = ser.read(1)
        if ack != b'A':
            print("Error: Robot did not acknowledge solve command")
            return None
        
        for ch in solve_commands:
            print(f"sending: {ch}")
            ser.write(ch.encode('utf-8'))

            #wait for ACK
            ack = ser.read(1)
            if ack == b'':
                print(f"Error: TIMEOUT waiting for motor to finish '{ch}'.")
                return False
            elif ack != b'A':
                print(f"Error: Robot rejected move '{ch}'. Received: {ack}")
                return False
        
        print("sedning END command")
        ser.write(b'-') #end command

        ack = ser.read(1)
        if ack != b'A':
            print(f"Error: Robot failed END command. Received: {ack}")
            return False
            
        print("Success, cube is solved!")
        return True

            
            
            


        
def scan_all_faces():
    full_cube_data = []

    with serial.Serial(PORT, BAUD_RATE, timeout=TIMEOUT) as ser:
        for face_num in range(6):
            print(f"\nscanning face {face_num + 1}")

            ser.write(b'R') #send read command in byte

            #wait for ACK
            ack = ser.read(1)
            if ack != b'A':
                print("Error: Robot did not acknowledge read command")
                return None
            
            print("Robot acknowledge and is now scanning face");

            face_data = ser.read(9)

            if len(face_data) == 9:
                ser.write(b'A') #send ACK
                full_cube_data.extend(list(face_data))
                print(f"Face {face_num + 1} successfully read")
            else:
                ser.write(b'N') #send NACK
                print(f"Error: incomplete data. recieved: {len(face_data)} bytes")

            time.sleep(0.5) #wait some time before asking for next face
        
    return full_cube_data


