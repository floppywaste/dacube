#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
//#include <avr/eeprom.h>

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
		if (frm & (((uint32_t) 1) << (layer * 9 + c))) {
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

#define W1 (C1 | C2 | C3)
#define W2 (C4 | C5 | C6)
#define W3 (C7 | C8 | C9)

#define W4 (C1 | C4 | C7)
#define W5 (C2 | C5 | C8)
#define W6 (C3 | C6 | C9)

#define VL1 (uint32_t) 7
#define VL2 (VL1 << 3)
#define VL3 (VL1 << 6)

#define VL4 (VL1 << 9)
#define VL5 (VL2 << 9)
#define VL6 (VL3 << 9)

#define VL7 (VL4 << 9)
#define VL8 (VL5 << 9)
#define VL9 (VL6 << 9)

#define VH1 (uint32_t) 73
#define VH2 (VH1 << 1)
#define VH3 (VH1 << 2)

#define VH4 (VH1 << 9)
#define VH5 (VH2 << 9)
#define VH6 (VH3 << 9)

#define VH7 (VH4 << 9)
#define VH8 (VH5 << 9)
#define VH9 (VH6 << 9)

#define D1 (C1 | C5 | C9)
#define D2 (C3 | C5 | C7)

#define D3 (VL1 | VL5 | VL9)
#define D4 (VL7 | VL5 | VL3)

#define CTR 8192

void circleCols() {
	setFrame(C1, 100);
	setFrame(C2, 100);
	setFrame(C3, 100);
	setFrame(C6, 100);
	setFrame(C9, 100);
	setFrame(C8, 100);
	setFrame(C7, 100);
	setFrame(C4, 100);
}

void circleColsWithCtr() {
	setFrame(C1 | C5, 100);
	setFrame(C2 | C5, 100);
	setFrame(C3 | C5, 100);
	setFrame(C6 | C5, 100);
	setFrame(C9 | C5, 100);
	setFrame(C8 | C5, 100);
	setFrame(C7 | C5, 100);
	setFrame(C4 | C5, 100);
}

void circleColsWithHlx() {
	setFrame(C1 | C5, 100);
	setFrame(C2 | C5, 100);
	setFrame(C3 | C5, 100);
	setFrame(C6 | C5, 100);
	setFrame(C9 | C5, 100);
	setFrame(C8  | C5, 100);
	setFrame(C7 | C5, 100);
	setFrame(C4 | C5, 100);
}

void rotate1() {
	setFrame(D3 & ~VL5, 200);
	setFrame(W2 & ~VL5, 200);
	setFrame(D4 & ~VL5, 200);
	setFrame(L2 & ~VL5, 200);
}

void rotate2() {
	setFrame(D3 & ~CTR, 100);
	setFrame(W2 & ~CTR, 100);
	setFrame(D4 & ~CTR, 100);
	setFrame(L2 & ~CTR, 100);
}

void rotateHi() {
	//
	setFrame(W2 & ~L1, 100);
	setFrame(D1 & ~L1, 100);
	setFrame(W5 & ~L1, 100);
	setFrame(D2 & ~L1, 100);
}

void rotateLo() {
	setFrame(W2 & ~L3, 100);
	setFrame(D1 & ~L3, 100);
	setFrame(W5 & ~L3, 100);
	setFrame(D2 & ~L3, 100);
}

void layerLift() {
	//
	setFrame(L1, 100);
	setFrame(L2, 100);
	setFrame(L3, 100);
	setFrame(L2, 100);
}

void rotatePlate() {
	setFrame(W2, 100);
	setFrame(D1, 100);
	setFrame(W5, 100);
	setFrame(D2, 100);
}

void runl1v() {
	setFrame(VL1, 200);
	setFrame(VL2, 200);
	setFrame(VL3, 200);
}

void runl2v() {
	setFrame(VL4, 200);
	setFrame(VL5, 200);
	setFrame(VL6, 200);
}

void runl3v() {
	setFrame(VL7, 200);
	setFrame(VL8, 200);
	setFrame(VL9, 200);
}

void runl1h() {
	//	rotate1();
	//	rotate2();
	//	rotateHi();
	//	rotateLo();
	//	layerLift();
	//	rotatePlate();
	//	runl1v();
	//	runl2v();
	//	runl3v();
	//
	setFrame(VH1, 200);
	setFrame(VH2, 200);
	setFrame(VH3, 200);
}

void runl2h() {
	setFrame(VH4, 200);
	setFrame(VH5, 200);
	setFrame(VH6, 200);
}

void runl3h() {
	setFrame(VH7, 200);
	setFrame(VH8, 200);
	setFrame(VH9, 200);
}

void loop() {

//	rotate1();
//	rotate2();
	rotateHi();
	rotateLo();
	rotateHi();
	rotateLo();
	rotateHi();
	rotateLo();
	rotateHi();
	rotatePlate();
	rotatePlate();
	circleColsWithCtr();
	circleColsWithCtr();
	circleCols();
	circleCols();
	setFrame(CTR, 400);
	setFrame(L2, 400);
	setFrame(CTR, 400);
	setFrame(L2, 400);
	setFrame(L3 | L1, 250);
	setFrame(L2, 300);
	setFrame(L3 | L1, 250);
	setFrame(L2, 300);
	setFrame(L3 | L1, 250);
	setFrame(L2, 300);
	layerLift();
	layerLift();
	rotate2();
	rotate2();
	rotate2();
	layerLift();


//	rotatePlate();

//	runl1v();
//	runl2v();
//	runl3v();
//
//	runl1h();
//	runl2h();
//	runl3h();
//
//	setFrame(W5, 100);
//	setFrame(W6, 100);
//
//	circleCols();
//	circleColsWithCtr();
}

