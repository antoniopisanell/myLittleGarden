import socket
from functools import reduce

from repository import myLittleGardenRepository

repo = myLittleGardenRepository()

# get arguments from command line
#
import sys
if len(sys.argv) == 1 or len(sys.argv) > 3:
  print("Usage: python server.py <ip> <port>")
  sys.exit(1)

UDP_IP = sys.argv[1]
UDP_PORT = int(sys.argv[2])

print(f"UDP target IP: {UDP_IP}")
print(f"UDP target port: {UDP_PORT}")

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
  data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
  document = reduce(lambda acc, x: {**acc, x.split(":")[0]: float(x.split(":")[1].strip())}, data.decode("utf-8").split(","), {})
  print(document)
  repo.insert(document)
