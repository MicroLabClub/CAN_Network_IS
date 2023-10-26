#include "Arduino.h"
#include "dd_can_mcp/dd_can_mcp.h"
#include "dd_can_mcp/dd_can_matrix.h"
#include "dd_joystick/dd_joystick.h"
#include "dd_can_mcp/dd_can_signal.h"

void setup()
{
  Serial.begin(9600);

  dd_can_setup();
  dd_joystick_setup();
}

#define SYS_TICK 1

#define CAN_SEND_REC (5000 / SYS_TICK)
#define CAN_RECV_REC (1 / SYS_TICK)
#define CAN_PRINT_REC (2000 / SYS_TICK)

int send_rec_cnt = CAN_SEND_REC;
int recv_rec_cnt = CAN_RECV_REC;
int print_rec_cnt = CAN_PRINT_REC;

#define DD_JOYSTICK_REC (10 / SYS_TICK)
int dd_joystick_rec_cnt = DD_JOYSTICK_REC;


void loop()
{
  if (--dd_joystick_rec_cnt <= 0)
  {// send data per 100ms
    dd_joystick_loop();
    dd_joystick_rec_cnt = DD_JOYSTICK_REC;
  }  
  
  if (--send_rec_cnt <= 0)

  {// send data per 100ms
    dd_can_send_loop();
    send_rec_cnt = CAN_SEND_REC;
  }

  if (--recv_rec_cnt <= 0)
  {
    dd_can_recv_loop();
    dd_can_signal_loop();
    recv_rec_cnt = CAN_RECV_REC;
  }

  if (--print_rec_cnt <= 0)
  {// print data per 100ms
    dd_can_matrix_print();
    dd_joystick_report();
        dd_can_tx_buff_print();

    print_rec_cnt = CAN_PRINT_REC;
  }

  delay(SYS_TICK); 
}
