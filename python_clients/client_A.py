import grpc
import data_pb2
import data_pb2_grpc
import time

def run():
    channel = grpc.insecure_channel("localhost:50051")
    stub = data_pb2_grpc.DataServiceStub(channel)

    for i in range(5):
        data = data_pb2.DataPacket(id=str(i), payload=f"Payload {i}")
        ack = stub.PushData(data)
        print(f"Sent: Payload {i}, Received Ack: {ack.received}")
        time.sleep(1)

if __name__ == "__main__":
    run()
