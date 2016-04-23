#include "rfid.h"
#include "alarm.h"
#include "output.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

byte correctID[] = {0x76, 0xEF, 0x37, 0xD5};

void checkRFID(){
    // Look for new cards, and select one if present
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }
  
  // Now a card is selected. The UID and SAK is in mfrc522.uid.
  boolean idValid = true;
  // Dump UID
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if( correctID[i] != mfrc522.uid.uidByte[i]){
      idValid = false;
    }
  } 
  Serial.println();
  if(idValid && isActive() == 0){
    Serial.print("Valide");
    activate();
  }
  else if(idValid && isActive() == 1){
    deactivate();
  }
}
