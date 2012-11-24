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

typedef struct {
	uint8_t layer;
	uint8_t column;
} Led;

typedef struct {
	uint8_t count;
	uint8_t cycles;
	Led leds[];
} Image;

/*
 * the main loop
 */
void loop();

/*
 * initializes inputs, outputs and all devices.
 */
void setUp();

int main(void) {
	setUp();
//	SET(PORTD, PD4);
//	SET(PORTB, PB6);
	while (1) {
		loop();
	}
}

void setUp() {
	DDRD |= ((1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6));
	DDRB |= ((1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5) | (1 << DDB6)
			| (1 << DDB7));
}

void onOff(int layer, int column) {
	*LAYERS[layer].port |= (1 << LAYERS[layer].pin);
	*COLUMNS[column].port |= (1 << COLUMNS[column].pin);
	_delay_ms(1);
	*LAYERS[layer].port &= ~(1 << LAYERS[layer].pin);
	*COLUMNS[column].port &= ~(1 << COLUMNS[column].pin);
}

void showLeds(Led *leds, int count, int cycles) {
	for (int cycle = 0; cycle < cycles; cycle++) {
		for (int i = 0; i < count; i++) {
			onOff(leds[i].layer, leds[i].column);
		}
	}
}

void showLeds2(Image image) {
	for (int cycle = 0; cycle < image.cycles; cycle++) {
		for (int i = 0; i < image.count; i++) {
			onOff(image.leds[i].layer, image.leds[i].column);
		}
	}
}


Led leds[2][9] = { { { 0, 0 }, { 0, 2 }, { 2, 0 }, { 2, 2 }, { 0, 6 }, { 0, 8 }, { 2, 6 }, { 2, 8 }, { 1, 4 } },
				   { { 1, 0 }, { 1, 2 }, { 1, 0 }, { 1, 2 }, { 1, 6 }, { 1, 8 }, { 1, 6 }, { 2, 4 }, { 0, 4 } }};

//Led leds[4][9] = { { { 0, 3 }, { 0, 4 }, { 0, 5 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 2, 3 }, { 2, 4 }, { 2, 5 } },
//				   { { 0, 2 }, { 0, 4 }, { 0, 6 }, { 1, 2 }, { 1, 4 }, { 1, 6 }, { 2, 2 }, { 2, 4 }, { 2, 6 } },
//				   { { 0, 1 }, { 0, 4 }, { 0, 7 }, { 1, 1 }, { 1, 4 }, { 1, 7 }, { 2, 1 }, { 2, 4 }, { 2, 7 } },
//				   { { 0, 0 }, { 0, 4 }, { 0, 8 }, { 1, 0 }, { 1, 4 }, { 1, 8 }, { 2, 0 }, { 2, 4 }, { 2, 8 } }};

//Led leds[1][9] = {
//				   { { 0, 0 }, { 0, 4 }, { 0, 8 }, { 1, 0 }, { 1, 4 }, { 1, 8 }, { 2, 0 }, { 2, 4 }, { 2, 8 } }};

void loop() {

	for (int i = 0; i < 2; i++) {
		showLeds(leds[i], 9, 80);
		_delay_ms(5000);
	}

	//	Image image = { 3, 200,{ { 0, 1 }, { 1, 2 }, { 2, 1 } }};
//	showLeds2(image);
//	showLeds2({{ { 0, 2 }, { 1, 3 }, { 2, 2 } }, 3, 200});
//	Led leds[3] = { { 0, 1 }, { 1, 2 }, { 2, 1 } };
//	leds[2] = {{2,2}};
//	showLeds(leds, 3, 255);
}

