#include <VirtualWire.h>
#include "sensors.h"
#include "output.h"
#include "alarm.h"

int val = 0;

void contactDetector(){
  val= digitalRead(bouton);
  if(val==LOW){
    digitalWrite(led_bouton, LOW);
    alarmTriggered();
  }
  else{
    digitalWrite(led_bouton, HIGH);
  }
}

void motionDetector(){
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    if(buf[0]=='1'){
      alarmTriggered();
    }
  }
}
