#! /usr/bin/env python
# -*- coding: utf-8 -*-
import grpc
import time
from concurrent import futures
import data_pb2, data_pb2_grpc

from pymongo import MongoClient

_ONE_DAY_IN_SECONDS = 60 * 60 * 24
_HOST = 'localhost'
_PORT = '8080'

class FormatData(data_pb2_grpc.FormatDataServicer):
    def DoFormat(self, request, context):
		client = MongoClient();
		db = client["virtual_volume_db"]
		collection = db["VirtualVolume"]
		str = ""
		for u in db.VirtualVolume.find({}):
			str += u["name"]
			str += '\n'
		return data_pb2.Data(text=str)

def serve():
    grpcServer = grpc.server(futures.ThreadPoolExecutor(max_workers=4))
    data_pb2_grpc.add_FormatDataServicer_to_server(FormatData(), grpcServer)
    grpcServer.add_insecure_port(_HOST + ':' + _PORT)
    grpcServer.start()
    try:
        while True:
            time.sleep(_ONE_DAY_IN_SECONDS)
    except KeyboardInterrupt:
        grpcServer.stop(0)

if __name__ == '__main__':
    serve()
