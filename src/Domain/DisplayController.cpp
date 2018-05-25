//
// Created by tg on 24.05.18.
//

#include "DisplayController.h"
#include "../Infrastructure/CANWrapperImpl.h"
#include "../Infrastructure/util.h"
#include "Events.h"
#include <stdio.h>



DisplayController::DisplayController() {
    printf("Display waiting for events\n");
}

void DisplayController::doWork() {
    CANWrapperImpl can{"vcan0"};


    while (1) {
        can_msg msg = can.can_read(REVERSE_GEAR_TRIGGERED);
        printf("Enable Rear Camera for Parking Assistance\n");
    }
}

main() {
    DisplayController app{};

    app.doWork();

}