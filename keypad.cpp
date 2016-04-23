#include "keypad.h"
#include "alarm.h"
#include "lcd.h"

const byte ROWS = 4; // Four rows
const byte COLS = 4; // columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {
    '1','2','3','A'  }
  ,
  {
    '4','5','6','B'  }
  ,
  {
    '7','8','9','C'  }
  ,
  {
    '*','0','#','D'  }
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 
  9, 8, 7, 6 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 
  5, 4, 3 ,2 };


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

Password password = Password("1234"); //password to unlock, can be changed

boolean activation = false;

void checkPassword(){
  if (isActive() == 0 && password.evaluate() && activation){  //if password is right open
      activate();  
  }

  else if (isActive() == 1 && password.evaluate() && !activation){  //if password is right open
    deactivate();
    }
  
  else{
    invalidCode();
  }
  password.reset();
}

void setActivation(boolean e){
 activation = e; 
}
