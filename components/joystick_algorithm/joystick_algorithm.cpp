#include "joystick_algorithm.h"

struct data_to_send_t joystick_algorithm(float accx, float accy){
    struct data_to_send_t data_to_send;

    if(accx < -0.5) data_to_send.angle=6;
    else if(accx > -0.5 && accx < -0.325) data_to_send.angle=5;
    else if(accx > -0.325 && accx < -0.15) data_to_send.angle=4;
    else if(accx > -0.15 && accx < 0.15) data_to_send.angle=0;
    else if(accx > 0.15 && accx < 0.325) data_to_send.angle=1;
    else if(accx > 0.325 && accx < 0.5) data_to_send.angle=2;
    else if(accx > 0.5) data_to_send.angle=3;
    
    if(accy < -0.5) data_to_send.mode=6;
    else if(accy > -0.5 && accy < -0.325) data_to_send.mode=5;
    else if(accy > -0.325 && accy < -0.15) data_to_send.mode=4;
    else if(accy > -0.15 && accy < 0.15) data_to_send.mode=0;
    else if(accy > 0.15 && accy < 0.325) data_to_send.mode=1;
    else if(accy > 0.325 && accy < 0.5) data_to_send.mode=2;
    else if(accy > 0.5) data_to_send.mode=3;

    return data_to_send;

}