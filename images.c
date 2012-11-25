#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>

#include "macro.h"
#include "images.h"

/*
 * abstraction of an output Pin.
 */
typedef struct {
	volatile uint8_t* port;
	uint8_t pin;
} Pin;

/*
 * The 9 column pins of the cube
 */
static Pin COLUMNS[] = { { &PORTD, PD6 }, { &PORTB, PB0 }, { &PORTB, PB1 }, { &PORTB, PB2 }, { &PORTB, PB3 }, { &PORTB,
		PB4 }, { &PORTB, PB5 }, { &PORTB, PB7 }, { &PORTB, PB6 } };

/*
 * The 3 layer pins of the cube
 */
static Pin LAYERS[] = { { &PORTD, PD3 }, { &PORTD, PD4 }, { &PORTD, PD5 } };

void on(const Pin* column) {
	*column->port |= (1 << column->pin);
}

void off(const Pin* column) {
	*column->port &= ~(1 << column->pin);
}

/**
 * Sequentially switches on and off the columns led outputs
 * which are indicated in the image for the specified layer.
 */
void mPlexColumns(uint32_t img, uint8_t layer) {
	for (uint8_t c = 0; c < 9; c++) {
		uint32_t isColHi = img & (((uint32_t) 1) << (layer * 9 + c));
		if (isColHi) {
			Pin column = COLUMNS[c];
			on(&column);
			_delay_us(100);
			off(&column);
		}
	}
}

/*
 * counts the first 27 LSB which are set to 1.
 */
uint8_t countBitsSet(uint32_t frm) {
	uint8_t res = 0;
	for (int i = 0; i < 27; i++) {
		res += ((frm >> i) & 1);
	}
	return res;
}

/*
 * the more bits set (leds hi at the same time) the slower the image creation,
 * thus the repetition count is normalized (not very precise heuristic observation)
 */
int normalizeRepetition(uint32_t frm, uint16_t repeat) {
	uint8_t scale = countBitsSet(frm);
	if (scale < 4) {
		scale += 3;
	}
	int nrmlzRep = repeat / scale;
	return nrmlzRep;
}

/*
 * implementation of images.h#setUpLedOutputs
 */
void setUpLedOutputs() {
	DDRD |= ((1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6));
	DDRB |= ((1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5) | (1 << DDB6)
			| (1 << DDB7));
}

/*
 * implementation of images.h#mPlexImage
 */
void mPlexImage(uint32_t frm, uint16_t repeat) {
	int nrmlzRep = normalizeRepetition(frm, repeat);
	for (int i = 0; i < nrmlzRep; i++) {
		for (uint8_t l = 0; l < 3; l++) {
			Pin layer = LAYERS[l];
			on(&layer);
			mPlexColumns(frm, l);
			off(&layer);
		}
	}
}
