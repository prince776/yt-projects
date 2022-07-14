# How to run

Nodejs:

```
cd nodejs/
node index.js
```

Bun:

```
cd bun/
bun start
```

crowCpp

```
cd crowcpp/
mkdir build && cd build
cmake ..
make
./crowcpp
```

# Benchmarking

`wrk` is used to benchmark.
Command for load testing localhost:3000 for 2 seconds:

```
wrk -t8 -c500 -d2s --latency http://localhost:3000
```

# Results

System used: `m1 macbook air, 16GB ram`

## Small workload

![](https://media.discordapp.net/attachments/912603519054401539/997037985289748490/unknown.png?width=1516&height=1081)

## Big workload

![](https://media.discordapp.net/attachments/912603519054401539/997038329172328468/unknown.png?width=1540&height=1081)
