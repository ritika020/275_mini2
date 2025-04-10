import sys
import os
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

import grpc
import csv
import time
from data_pb2 import DataRow
from data_pb2_grpc import DataPushServiceStub

# from python_clients import data_pb2
# from python_clients import data_pb2_grpc

# DataRow = data_pb2.DataRow
# DataPushServiceStub = data_pb2_grpc.DataPushServiceStub


# Sends a single row to Node A
def send_data(stub, key, value):
    data_row = DataRow(key=key, value=value)
    response = stub.SendData(data_row)
    print(f"Sent: {key}, Response: {response.status}")

def run():
    # Connect to Node A
    channel = grpc.insecure_channel('localhost:50051')
    stub = DataPushServiceStub(channel)

    # Read CSV and send each row
    with open("Motor_Vehicle_Collisions_-_Crashes_20250123.csv", "r") as f:
        reader = csv.reader(f)

        # for row in reader:
        #     key, value = row[0], row[1]
        #     send_data(stub, key, value)
        #     time.sleep(0.1)  # simulate delay

        next(reader)  # skip header
        for i, row in enumerate(reader):
            if len(row) >= 2:
                key, value = row[0], row[1]
                send_data(stub, key, value)
                time.sleep(0.1)
            # if i > 20:  # only send first 20 rows for testing
            #     break

if __name__ == "__main__":
    run()
