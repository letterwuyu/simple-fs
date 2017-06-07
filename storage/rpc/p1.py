#! /usr/bin/env python
#
from pymongo import MongoClient
import pymongo

def Run():
	client = MongoClient();
	db = client["virtual_volume_db"]
	collection = db["VirtualVolume"]
	str = ""
	for u in db.VirtualVolume.find({}):
		print(u["name"])
		str += u["name"];
		str += '\n'
	print(str)

if __name__ == '__main__':
	Run();
