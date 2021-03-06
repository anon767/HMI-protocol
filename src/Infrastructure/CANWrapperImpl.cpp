
#include "util.h"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include "CANWrapperImpl.h"


const static int DELAY = 10000;


CANWrapperImpl::CANWrapperImpl(char *iface) {
    this->iface = iface;
    this->socketHandle = this->openSocket();

}


int CANWrapperImpl::openSocket() {
    int flags;
    struct ifreq ifr;
    struct sockaddr_can addr;

    /* Open the CAN interface */
    int s = socket(PF_CAN, SOCK_DGRAM, CAN_BCM);
    if (s < 0) {
        perror("socket");
        return errno;
    }

    strncpy(ifr.ifr_name, this->iface, IFNAMSIZ);
    if (ioctl(s, SIOCGIFINDEX, &ifr) < 0) {
        perror("ioctl");
        return errno;
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (connect(s, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("connect");
        return errno;
    }


    return s;
}

int CANWrapperImpl::can_close() {
    if (close(this->socketHandle) < 0) {
        perror("close");
        return errno;
    }
    return 0;
}


int CANWrapperImpl::can_write(can_msg message) {
    ssize_t nbytes;
    nbytes = write(this->socketHandle, &message, sizeof(message));
    if (nbytes < 0) {
        perror("write: TX_SEND");
    } else if (nbytes < (ssize_t)sizeof(message))
    {
        fputs("write: incomplete BCM message\n", stderr);
    }else{
        /* Print the transmitted CAN frame */
        printf("TX:  ");
        print_can_frame(message.frame);
        printf("\n");
    }
    return 0;
}

can_msg CANWrapperImpl::can_read(int can_id) {

    can_msg msg;
    msg.msg_head.opcode = RX_SETUP;
    msg.msg_head.can_id = can_id;
    msg.msg_head.flags = 0;
    msg.msg_head.nframes = 0;

    if (write(this->socketHandle, &msg, sizeof(msg)) < 0) {
        perror("write: RX_SETUP");
    }
    ssize_t nbytes = read(this->socketHandle, &msg, sizeof(msg));
    if (nbytes < 0) {
        if (errno != EAGAIN) {
            perror(": read");
        }
        usleep(DELAY);
    } else if (nbytes < (ssize_t)sizeof(msg))
    {
        fputs("read: incomplete BCM message\n", stderr);
        usleep(DELAY);
    }else{
        return msg;
    }


}