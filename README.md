# HMI Protocol over CAN with SocketCAN

Sample Use-Case Implementation.

Use-Case:

Driver engages Rear reverse gear (e.g. tilt sensor). Board-Display should enable Rear Camera for parking assistance.

## Run

```
$ make clean
$ make
$ ./displaycontroller &
$ ./reversegearcontroller
```
