#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <avr/eeprom.h>

#include "macro.h"

typedef struct {
	volatile uint8_t* port;
	uint8_t pin;
} Pin;

static Pin COLUMNS[] = { { &PORTD, PD6 }, { &PORTB, PB0 }, { &PORTB, PB1 }, { &PORTB, PB2 }, { &PORTB, PB3 }, { &PORTB,
		PB4 }, { &PORTB, PB5 }, { &PORTB, PB7 }, { &PORTB, PB6 } };
static Pin LAYERS[] = { { &PORTD, PD3 }, { &PORTD, PD4 }, { &PORTD, PD5 } };

//		uint8_t frameSize;
uint8_t frame[27];
static uint8_t frameIdx = 0;

/*
 * the main loop
 */
void loop();

/*
 * initializes inputs, outputs and all devices.
 */
void setUpLedOutputs();

int main(void) {
	setUpLedOutputs();

	frame[0] = 0b01000000;
	frame[1] = 0b01000001;
	frame[2] = 0b01000101;

	while (1) {
		loop();
	}
}

void setUpLedOutputs() {
	DDRD |= ((1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6));
	DDRB |= ((1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5) | (1 << DDB6)
			| (1 << DDB7));
}

void onOff(int layer, int column) {
	*LAYERS[layer].port |= (1 << LAYERS[layer].pin);
	*COLUMNS[column].port |= (1 << COLUMNS[column].pin);
	_delay_ms(5);
	*LAYERS[layer].port &= ~(1 << LAYERS[layer].pin);
	*COLUMNS[column].port &= ~(1 << COLUMNS[column].pin);
}

void switchOn(uint8_t cmd) {
	Pin layer = LAYERS[Z(cmd)];
	Pin column = COLUMNS[COL(cmd)];

	*layer.port |= (1 << layer.pin);
	*column.port |= (1 << column.pin);
}

void switchOff(uint8_t cmd) {
	Pin layer = LAYERS[Z(cmd)];
	Pin column = COLUMNS[COL(cmd)];

	*layer.port &= ~(1 << layer.pin);
	*column.port &= ~(1 << column.pin);
}

void repeat(uint8_t repeat) {
	for (int i = 0; i < repeat * 10; i++) {
		for (int j = 0; j < frameIdx; j++) {
			switchOn(frame[j]);
			_delay_ms(2);
			switchOff(frame[j]);
		}
	}
}

void command(uint8_t cmd) {
	if (IS_FRM_STRT(cmd)) {
		frameIdx = 0;
//		frameSize = LEDS_IN_FRM(cmd);
	} else if (IS_FRM_RPT(cmd)) {
		repeat(FRM_RPT(cmd));
	} else if (IS_ON(cmd)) {
		if (frameIdx < 27) {
			frame[frameIdx++] = cmd;
		}
//		switchOn(cmd);
	} else {
//		switchOff(cmd);
	}
}

uint8_t rep(uint8_t count) {
	return 0b11100000 | count;
}

#define FRM 0x80

void loop() {
//	if (IS_FRM_RPT(0b10000000))
//		for (int j = 0; j < 3; j++) {
//			switchOn(frame[j]);
//			_delay_ms(2);
//			switchOff(frame[j]);
//		}

//	command(0b10000000);
//	command(0b01000000);
//	command(0b01000001);
//	command(0b01000101);
//	command(0b11111111);

	command(FRM);
	command(0b01000000);
	command(rep(31));
//	_delay_ms(1000);
//	switchOff(0b01000000);
	_delay_ms(1000);

	command(FRM);
	command(0b01000001);
	command(0b01000101);
	command(rep(31));

	_delay_ms(1000);
}

