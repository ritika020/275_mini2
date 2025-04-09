import grpc
import csv
import time
import json
from data_pb2 import DataPacket
from data_pb2_grpc import DataServiceStub

channel = grpc.insecure_channel("localhost:50050")  # Node A
stub = DataServiceStub(channel)

start = time.time()
with open("Motor_Vehicle_Collisions_-_Crashes_20250223.csv", newline='') as csvfile:
    reader = csv.DictReader(csvfile)
    for i, row in enumerate(reader):
        payload = {
            "crash_date": row["CRASH_DATE"],
            "borough": row["BOROUGH"],
            "street": row["ON_STREET_NAME"],
            "injuries": row["NUMBER_OF_PERSONS_INJURED"]
        }
        # Use row number as ID or combine fields
        pkt = DataPacket(id=str(i), payload=json.dumps(payload))
        ack = stub.PushData(pkt)
        print(f"Sent row {i}, Ack: {ack.received}")
        if i > 1000:  # limit for test
            break
end = time.time()
print(f"Total time: {end - start:.2f}s")
