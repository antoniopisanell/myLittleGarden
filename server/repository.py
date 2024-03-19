import pymongo  # package for working with MongoDB
import datetime


class myLittleGardenRepository():
  def __init__(self):
    self.client = pymongo.MongoClient("mongodb://localhost:27017/")
    self.db = self.client["myLittleGarden"]
    self.sensorData = self.db["sensorsData"]
  
  def insert(self, data: dict) -> str:
    # insert data into the collection and return the id of the inserted document
    data["timestamp"] = datetime.datetime.now()
    return self.sensorData.insert_one(data).inserted_id
  
  def getLastInserted(self):
    return self.sensorData.find().sort("timestamp", pymongo.DESCENDING).limit(1).next()
  
  def removeCollection(self): #used for testing purposes, and populate_database.py
    self.sensorData.drop()