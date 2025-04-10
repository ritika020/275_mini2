# Mini 2: Distributed System for Efficient Data Ingestion and Querying

## Project Overview

This project implements a distributed data ingestion and processing pipeline across multiple nodes using **gRPC** and **shared memory (mmap)**. The architecture is designed to ensure high throughput, memory-safe operations, and optimized data partitioning.

- **Client Language**: Python  
- **Server Language**: C++  
- **Communication**: gRPC  
- **Memory Handling**: POSIX shared memory (mmap)  
- **Deployment**: Multi-process simulation, tested on 1 and 2 machines  

---

## Architecture

           +--------------+
           |  Python CSV  |
           |   Client     |
           +------+-------+
                  |
                  v
              [ Node A ]
           (Global Hash Partition)
             /          \
            v            v
        [Node B]      [Node C]
     (Local Partitioning to D/E)
        |   \           /   |
        v    v         v    v
      [Node D]       [Node E]
      (Final Storage + Query)





## Project Structure:

275_mini2/
├── cpp_servers/
│   ├── common/
│   └── node_{A,B,C,D,E}/
├── proto/
├── python_clients/
├── build/
└── CMakeLists.txt


---

## How It Works

### Data Ingestion Flow

1. **Client** reads a large CSV file and sends rows to Node A via gRPC.  
2. **Node A** uses a global hash to distribute rows to Node B or C.  
3. **Nodes B/C** use a local partition to either write to shared memory or forward to D/E.  
4. **Nodes D/E** store data in shared memory using high-speed `mmap` writes.  

### Query Support

- `count(*)`, `sum(value)`, `avg(value)`, and custom filters are handled by leaf nodes and aggregated up to Node A.

---

## How to Run

### Build C++ servers

```bash
rm -rf build
mkdir build
cd build
cmake ..
make -j
```

## Start Servers (in separate terminals)

./build/node_A
./build/node_B
./build/node_C
./build/node_D
./build/node_E


## Run Python Client
cd python_clients
python3 client.py



