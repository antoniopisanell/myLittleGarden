import socket
import time
import random
import sys

if len(sys.argv) != 2:
    print("Usage: python mock_esp32.py <port>")
    sys.exit(1)

UDP_IP = "127.0.0.1"
UDP_PORT = int(sys.argv[1])

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    humidity = round(random.uniform(0, 100), 2)
    temp = round(random.uniform(15, 35), 2)
    light = round(random.uniform(0, 1000), 2)
    
    data = f"Humidity:{humidity},Temperature:{temp},Light:{light}"
    sock.sendto(data.encode(), (UDP_IP, UDP_PORT))
    print(f"Sent data: {data}")
    
    time.sleep(1)
