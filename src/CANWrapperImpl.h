//
// Created by tom on 23.05.18.
//

#ifndef HMI_PROTOCOL_CANWRAPPER_H
#define HMI_PROTOCOL_CANWRAPPER_H

#include <linux/can.h>
#include <linux/can/bcm.h>

class CANWrapperImpl {
private:
    int openSocket();

public:



    int close();

    int can_write(can_msg msg);

    can_msg can_read(int can_id);


};

#endif //HMI_PROTOCOL_CANWRAPPER_H
