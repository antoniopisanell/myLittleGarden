import time
from repository import myLittleGardenRepository

repo = myLittleGardenRepository()
repo.removeCollection()

mockSensors = [
    {"umidity": 30.0, "temp": 25.0, "light": 100.0},
    {"umidity": 35.0, "temp": 26.0, "light": 20.0},
    {"umidity": 40.0, "temp": 27.0, "light": 30.0},
    {"umidity": 45.0, "temp": 28.0, "light": 44.0},
    {"umidity": 50.0, "temp": 29.0, "light": 95.0},
]

for sensor in mockSensors:
  repo.insert(sensor)
  time.sleep(1)