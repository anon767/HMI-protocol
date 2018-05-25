//
// Created by tg on 24.05.18.
//

#include "ReverseGearController.h"
#include "../Infrastructure/CANWrapperImpl.h"
#include "Events.h"
#include <stdio.h>

ReverseGearController::ReverseGearController() {}


void ReverseGearController::doWork() {
    CANWrapperImpl canWrapper{"vcan0"};
    can_msg msg;
    msg.frame->can_id = REVERSE_GEAR_TRIGGERED;
    msg.frame->can_dlc = CAN_MAX_DLEN;
    msg.msg_head.opcode = TX_SEND;
    msg.msg_head.flags = 0;
    msg.msg_head.can_id = REVERSE_GEAR_TRIGGERED;
    msg.msg_head.nframes = 1;
    canWrapper.can_write(msg);


}

main() {
    ReverseGearController app;

    app.doWork();
    printf("sent event for enabling rear camera\n");
}

