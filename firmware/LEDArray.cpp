/*
 * LEDArray.cpp
 *
 *  Created on: Jul 15, 2018
 *      Author: baixiao
 */
#include <Arduino.h>
#include "../../defines.h"
#include "../ModulesBaudRate.h"
#include "../InputConnection.h"
#include "../MessageConstants.h"

#if defined(LED_ARRAY)

InputConnection input;

void setup() {
	input = InputConnection(&Serial, LED_ARRAY_BAUD_RATE);
	DDRB = 0x0f;
	DDRD = 0xf0;
}

void loop() {
	if (input.newMessageAvailable()) {
		sp::DataType dataType = input.getMessage().getDataType();
		if (dataType == sp::INTEGER) {
			int data = input.getMessage().getIntData();

			PORTB &= 0x00;
			PORTB |= (data & 0xf0) >> 4;

			PORTD &= 0x00;
			PORTD |= (data & 0x0f) << 4;
		}
	}
}

void serialEvent() {
	input.update();
}

#elif defined(LED_ARRAY_MASTER)

#include "../SerializerUtils.h"
#include "../LEDArrayConnection.h"

char buffer[sp::MAX_MESSAGE_SIZE];
LEDArrayConnection ledConnection;

void display(uint8_t byte) {
//	Serialize(buffer, (int)byte, sp::DataType::INTEGER);
//	Serial.print(buffer);
	ledConnection.setLEDArrayState(byte);
	delay(7);
}

void setup() {
	Serial.begin(LED_ARRAY_BAUD_RATE);
	ledConnection.setSerial(&Serial);
}

void loop() {
//	for (int i=0; i<256; i++) {
//		Serialize(buffer, i, sp::DataType::INTEGER);
//		Serial.print(buffer);
//		delay(1);
//	}
//	if (Serial.available()) {
//		Serialize(buffer, (int) Serial.parseInt(), sp::DataType::INTEGER);
//		Serial.print(buffer);
//	}


//	display(0b01110000);
//	display(0b11111000);
//	display(0b11111110);
//	display(0b00111111);
//	display(0b00011111);
//	display(0b00111111);
//	display(0b11111110);
//	display(0b11111000);
//	display(0b01110000);
//	display(0x00);
//	display(0x00);

	for (int i=0; i<=8; i++) {
		ledConnection.setNumberOfLEDsOn(i);
		delay(200);
	}
	for (int i=8; i>=0; i--) {
		ledConnection.setNumberOfLEDsOn(i);
		delay(200);
	}
}

#endif

