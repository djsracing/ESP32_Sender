#include <CAN.h>
#define TX_GPIO_NUM 18 // Connects to CTX
#define RX_GPIO_NUM 19  // Connects to CRX
#define cs 10
#define irq 2
const int rowNum1 = 16;
const int colNum1 = 8;
const int rowNum2 = 8;
const int colNum2 = 8;
float values1[rowNum1][colNum1] = {
  {0.01, 0.42, 2.13, 1.59, 0.76, 2.87, 3.21, 0.11},
  {3.05, 2.64, 1.77, 0.98, 0.35, 1.12, 2.99, 0.14},
  {2.23, 0.88, 1.65, 2.45, 1.98, 3.25, 0.57, 0.17},
  {1.10, 0.22, 2.08, 0.49, 2.75, 3.08, 0.67, 0.20},
  {3.17, 0.55, 2.05, 2.31, 1.34, 0.91, 1.76, 0.23},
  {1.87, 2.28, 0.12, 0.64, 2.99, 1.54, 3.09, 0.26},
  {0.83, 1.32, 2.74, 0.46, 1.89, 2.47, 1.44, 0.29},
  {2.66, 1.01, 0.72, 1.42, 2.18, 0.31, 3.30, 0.32},
  {0.44, 2.14, 1.56, 3.12, 2.19, 0.06, 0.94, 0.35},
  {1.20, 0.30, 2.73, 1.68, 0.71, 2.32, 3.03, 0.37},
  {2.11, 1.55, 0.33, 2.34, 1.78, 3.23, 0.19, 0.40},
  {0.25, 1.80, 2.68, 0.43, 1.09, 2.54, 1.75, 0.43},
  {3.07, 0.52, 2.37, 2.91, 0.61, 1.66, 1.14, 0.46},
  {1.99, 0.27, 2.46, 0.81, 3.04, 2.44, 1.67, 0.49},
  {2.41, 1.86, 0.39, 3.24, 0.69, 3.14, 1.47, 0.52},
  {1.30, 2.62, 2.03, 0.02, 1.22, 0.94, 0.10, 0.55}
};// 16x8 Array of float values to send
float values2[rowNum2][colNum2] = {
  {0.01, 0.42, 2.13, 1.59, 0.76, 2.87, 3.21, 0.58},
  {3.05, 2.64, 1.77, 0.98, 0.35, 1.12, 2.99, 0.61},
  {2.23, 0.88, 1.65, 2.45, 1.98, 3.25, 0.57, 0.64},
  {1.10, 0.22, 2.08, 0.49, 2.75, 3.08, 0.67, 0.67},
  {3.17, 0.55, 2.05, 2.31, 1.34, 0.91, 1.76, 0.70},
  {1.87, 2.28, 0.12, 0.64, 2.99, 1.54, 3.09, 0.73},
  {0.83, 1.32, 2.74, 0.46, 1.89, 2.47, 1.44, 0.76},
  {2.66, 1.01, 0.72, 1.42, 2.18, 0.31, 3.30, 0.79}
};// 8x8 Array of float values to send
//==================================================================================//
void setup() {
  Serial.begin (115200);
  while (!Serial);
  delay (1000);

  Serial.println ("CAN Sender");
  // Set the pins
  // CAN.setPins (RX_GPIO_NUM, TX_GPIO_NUM);
  CAN.setPins(cs, irq);
  // start the CAN bus at 500 kbps
  if (!CAN.begin (1000E3)) {
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
  uint8_t byteValues1[rowNum1][colNum1];
  uint8_t byteValues2[rowNum2][colNum2];
  unsigned long currentMillis, elapsedMillis;
  Serial.print("Sending packets ... ");
  currentMillis = millis();
  // Code to send 16x8 Array
  for (int i = 0; i < rowNum1; i++) {
  CAN.beginPacket(0x11+i);
  
  // Convert float values to uint8_t and write them to the CAN packet
  for (int j = 0; j < colNum1; j++) {
    byteValues1[i][j] = (uint8_t)(values1[i][j] * 76);
    CAN.write(byteValues1[i][j]);
  }
  
  CAN.endPacket();
  delay(25); // Add a small delay between packets
}
// Code to send 8x8 Array
for (int i = 0; i < rowNum2; i++) {
  CAN.beginPacket(0x21+i);
  
  // Convert float values to uint8_t and write them to the CAN packet
  for (int j = 0; j < colNum2; j++) {
    byteValues2[i][j] = (uint8_t)(values2[i][j] * 76);
    CAN.write(byteValues2[i][j]);
  }
  
  CAN.endPacket();
  delay(25); // Add a small delay between packets
}
  elapsedMillis = millis() - currentMillis;
  Serial.println(elapsedMillis);
  Serial.println("done");
  //delay(3000);

}
//==================================================================================//