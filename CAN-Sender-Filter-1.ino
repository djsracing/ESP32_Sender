#include <CAN.h>
#define TX_GPIO_NUM 17 // Connects to CTX
#define RX_GPIO_NUM 16  // Connects to CRX
#define cs 10
#define irq 2
//==================================================================================//
void setup() {
  Serial.begin (115200);
  while (!Serial);
  delay (1000);

  Serial.println ("CAN Sender");
  // Set the pins
  CAN.setPins (RX_GPIO_NUM, TX_GPIO_NUM);
  //CAN.setPins(cs, irq);
  // start the CAN bus at 500 kbps
  if (!CAN.begin (500E3)) {
    Serial.println ("Starting CAN failed!");
    while (1);
  }
  else {
    Serial.println ("CAN Initialized");
  }
}
//==================================================================================//
void loop() {
   canSender();
 // canReceiver();
}
//==================================================================================//
void canSender() {
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print ("Sending packet ... ");

  CAN.beginPacket (0x13);  //sets the ID and clears the transmit buffer
  // CAN.beginExtendedPacket(0xabcdef);
  CAN.write ('4'); //write data to buffer. data is not sent until endPacket() is called.
  CAN.write ('0');
  CAN.write ('1');
  CAN.write ('2');
  CAN.write ('5'); 
  CAN.write ('9');
  CAN.write ('3');
  CAN.write ('6');
  CAN.endPacket();

  CAN.beginPacket (0x14);  //sets the ID and clears the transmit buffer
  //CAN.beginExtendedPacket(0xabcdef);
  CAN.write ('6');
  CAN.write ('10'); //write data to buffer. data is not sent until endPacket() is called.
  CAN.write ('8');
  CAN.write ('12');
  CAN.write ('21');
  CAN.endPacket();
  //RTR packet with a requested data length
  //CAN.beginPacket (0x13, 3, true);
  //CAN.endPacket();
  Serial.println ("done");
  delay (1000);
}
//==================================================================================//
void canReceiver() {
  // try to parse packet
  int packetSize = CAN.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print ("Received ");
    if (CAN.packetExtended()) {
      Serial.print ("extended ");
    }
    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      Serial.print ("RTR ");
    }
    Serial.print ("packet with id 0x");
    Serial.print (CAN.packetId(), HEX);
    if (CAN.packetRtr()) {
      Serial.print (" and requested length ");
      Serial.println (CAN.packetDlc());
    } else {
      Serial.print (" and length ");
      Serial.println (packetSize);
      // only print packet data for non-RTR packets
      while (CAN.available()) {
        Serial.print ((char) CAN.read());
      }
      Serial.println();
    }
    Serial.println();
  }
}
//==================================================================================//