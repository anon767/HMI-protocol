# HMI Protocol over CAN with SocketCAN

Sample Use-Case Implementation.

Use-Case:

Driver engages Rear reverse gear (e.g. tilt sensor). Board-Display should enable Rear Camera for parking assistance.

## Prerequisites

```
$ sudo modprobe vcan
$ sudo ip link set up vcan0 
```

## Run

```
$ make clean
$ make
$ ./displaycontroller &
$ ./reversegearcontroller
```
