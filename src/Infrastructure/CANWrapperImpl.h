//
// Created by tom on 23.05.18.
//

#ifndef HMI_PROTOCOL_CANWRAPPER_H
#define HMI_PROTOCOL_CANWRAPPER_H
#include <linux/can.h>
#include <linux/can/bcm.h>
const static int NFRAMES = 1;
typedef struct  {
    struct bcm_msg_head msg_head;
    struct can_frame frame[NFRAMES];
}can_msg;



class CANWrapperImpl  {

public:
    CANWrapperImpl(char * iface);
    virtual int can_close();
    virtual int can_write(can_msg msg);
    virtual can_msg can_read(int can_id);

private:
    int socketHandle;
    int openSocket();
    char * iface;

};

#endif //HMI_PROTOCOL_CANWRAPPER_H
