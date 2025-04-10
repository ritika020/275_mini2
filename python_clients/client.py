import sys
import os
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

import grpc
import csv
import time
from data_pb2 import DataRow
from data_pb2_grpc import DataPushServiceStub

import hashlib

def send_data(stub, key, value):
    data_row = DataRow(key=key, value=value)
    response = stub.SendData(data_row)
    return response.status

def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = DataPushServiceStub(channel)

    total_start = time.time()
    row_count = 0
    batch_start = time.time()

    with open("Motor_Vehicle_Collisions_-_Crashes_20250123.csv", "r") as f:
        reader = csv.reader(f)
        next(reader)  # skip header

        for i, row in enumerate(reader):
            if len(row) >= 2:
                key, value = row[0], row[1]
                start = time.time()
                status = send_data(stub, key, value)
                end = time.time()

                row_time_ms = (end - start) * 1000
                row_count += 1

                if row_count % 10000 == 0:
                    batch_time = time.time() - batch_start
                    print(f"[Client] Sent {row_count} rows | Avg time: {row_time_ms:.2f} ms | Batch time: {batch_time:.2f} s")
                    batch_start = time.time()

                print(f"Sent: {key}, Response: {status}")
                time.sleep(0.1)

    total_end = time.time()
    total_duration_sec = total_end - total_start
    avg_time_ms = (total_duration_sec / row_count) * 1000
    throughput = row_count / total_duration_sec

    print("\nIngestion Summary:")
    print(f"Total Rows Sent: {row_count}")
    print(f"Avg Time per Row: {avg_time_ms:.2f} ms")
    print(f"Total Time: {total_duration_sec/60:.2f} minutes")
    print(f"Throughput: {throughput:.2f} rows/sec")

if __name__ == "__main__":
    run()
