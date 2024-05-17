import socket
import time
import random
import sys
from pynput import keyboard

def on_key_press(key):
  # so this is a bit of a quirk with pynput,
  # if an alpha-numeric key is pressed the key object will have an attribute
  # char which contains a string with the character, but it will only have
  # this attribute with alpha-numeric, so if a special key is pressed
  # this attribute will not be in the object.
  # so, we end up having to check if the attribute exists with the hasattr
  # function in python, and then check the character
  # here is that in action:
  if hasattr(key, "char"):
    global min_humidity, max_humidity
    global min_temp, max_temp
    global min_light, max_light

    match key.char:
      case "z":
        print("La plante a été arosée")
        min_humidity, max_humidity = 60, 80
      case "u":
        print("La plante a séché")
        min_humidity, max_humidity = 0, 20
      case "h":
        print("La plante a été déplacée à la lumière")
        min_light, max_light = 60, 80
      case "j":
        print("La plante a été déplacée à l'ombre")
        min_light, max_light = 0, 20


# same as the key press callback, but for releasing keys
def on_key_release(key):
  # do so like this:
  if key == keyboard.Key.shift:
    print("SHIFT KEY RELEASED!")

keyboard_listener = keyboard.Listener(
    on_press=on_key_press,
    on_release=on_key_release)
keyboard_listener.start()

if len(sys.argv) != 2:
    print("Usage: python mock_esp32.py <port>")
    sys.exit(1)

UDP_IP = "127.0.0.1"
UDP_PORT = int(sys.argv[1])

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

min_humidity, max_humidity = 0, 20
min_temp, max_temp = 20, 35
min_light, max_light = 0, 20

try:
  while True:
      humidity = round(random.uniform(min_humidity, max_humidity), 2)
      temp = round(random.uniform(min_temp,max_temp), 2)
      light = round(random.uniform(min_light, max_light), 2)
      
      data = f"Humidity:{humidity},Temperature:{temp},Light:{light}"
      sock.sendto(data.encode(), (UDP_IP, UDP_PORT))
      print(f"Sent data: {data}")
      
      time.sleep(1)
finally:
  keyboard_listener.stop()
  keyboard_listener.join()
