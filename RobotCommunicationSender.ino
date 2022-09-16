#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SIG_FWD 0
#define SIG_LEFT 1
#define SIG_RIGHT 2

byte writeAddress[6] = "00002";
RF24 radio = RF24(9,10);

	

void setup() {
	Serial.begin(9600);
	radio.begin();
	radio.openWritingPipe(writeAddress);
	radio.setPALevel(RF24_PA_MIN);
	radio.stopListening();
}

void loop() {
	Serial.println("Enter instruction (fwd = 0, left = 1, right = 2)");
	while(!Serial.available()){}

  char message[2];
	Serial.readString().toCharArray(message, sizeof(message));
	bool recieved = radio.write(message, sizeof(message));
  Serial.println("Instruction sent");
  if(recieved){
    Serial.println("Message acknowledged");
  } else {
    Serial.println("Message failed");
  }
}
