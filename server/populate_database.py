import time
from repository import myLittleGardenRepository

repo = myLittleGardenRepository()
repo.removeCollection()

mockSensors = [
    {"Humidity": 30.0, "Temperature": 25.0, "Light": 100.0},
    {"Humidity": 35.0, "Temperature": 26.0, "Light": 20.0},
    {"Humidity": 40.0, "Temperature": 27.0, "Light": 30.0},
    {"Humidity": 45.0, "Temperature": 28.0, "Light": 44.0},
    {"Humidity": 50.0, "Temperature": 29.0, "Light": 95.0},
]

for sensor in mockSensors:
  repo.insert(sensor)
  time.sleep(1)