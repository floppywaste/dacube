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

	while (1) {
		loop();
	}
}

void setUpLedOutputs() {
	DDRD |= ((1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6));
	DDRB |= ((1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5) | (1 << DDB6)
			| (1 << DDB7));
}

void switchColumns(uint32_t frm, uint8_t layer) {
	for (uint8_t c = 0; c < 9; c++) {
		if (frm & (((uint32_t)1) << (layer * 9 + c))) {
			Pin column = COLUMNS[c];
			*column.port |= (1 << column.pin);
			_delay_us(100);
			*column.port &= ~(1 << column.pin);
		}
	}
}

void setFrame(uint32_t frm, uint16_t repeat) {
	for (int i = 0; i < repeat; i++) {
		for (uint8_t l = 0; l < 3; l++) {
			Pin layer = LAYERS[l];
			*layer.port |= (1 << layer.pin);
			switchColumns(frm, l);
			*layer.port &= ~(1 << layer.pin);
		}
	}
}

#define L1 (uint32_t) 0x1FF
#define L2 (uint32_t) 0x3FE00
#define L3 (uint32_t) 0x7FC0000

#define C1 (uint32_t) 0x40201
#define C2 C1 << 1
#define C3 C1 << 2
#define C4 C1 << 3
#define C5 C1 << 4
#define C6 C1 << 5
#define C7 C1 << 6
#define C8 C1 << 7
#define C9 C1 << 8


#define W1 C1 | C2 | C3
#define W2 C4 | C5 | C6
#define W3 C7 | C8 | C9

#define W4 C1 | C4 | C7
#define W5 C2 | C5 | C8
#define W6 C3 | C6 | C9



void loop() {
	setFrame(L1, 100);
	setFrame(L2, 100);
	setFrame(L3, 100);
	setFrame(L2, 100);
	setFrame(W1, 100);
	setFrame(W2, 100);
	setFrame(W3, 100);
	setFrame(W4, 100);
	setFrame(W5, 100);
	setFrame(W6, 100);

}

