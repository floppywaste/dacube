#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
//#include <util/delay.h>

#include <stdio.h>
//#include <avr/eeprom.h>

//#include "macro.h"
#include "images.h"

void circleCols() {
	mPlexImage(C1, 1000);
	mPlexImage(C2, 1000);
	mPlexImage(C3, 1000);
	mPlexImage(C6, 1000);
	mPlexImage(C9, 1000);
	mPlexImage(C8, 1000);
	mPlexImage(C7, 1000);
	mPlexImage(C4, 1000);
}

void circleColsWithCtr() {
	mPlexImage(C1 | C5, 1000);
	mPlexImage(C2 | C5, 1000);
	mPlexImage(C3 | C5, 1000);
	mPlexImage(C6 | C5, 1000);
	mPlexImage(C9 | C5, 1000);
	mPlexImage(C8 | C5, 1000);
	mPlexImage(C7 | C5, 1000);
	mPlexImage(C4 | C5, 1000);
}

void circleColsWithHlx() {
	mPlexImage(C1 | C5, 1000);
	mPlexImage(C2 | C5, 1000);
	mPlexImage(C3 | C5, 1000);
	mPlexImage(C6 | C5, 1000);
	mPlexImage(C9 | C5, 1000);
	mPlexImage(C8 | C5, 1000);
	mPlexImage(C7 | C5, 1000);
	mPlexImage(C4 | C5, 1000);
}

void rotate1() {
	mPlexImage(D3 & ~VL5, 1000);
	mPlexImage(W2 & ~VL5, 1000);
	mPlexImage(D4 & ~VL5, 1000);
	mPlexImage(L2 & ~VL5, 1000);
}

void rotate2() {
	mPlexImage(D3 & ~CTR, 1000);
	mPlexImage(W2 & ~CTR, 1000);
	mPlexImage(D4 & ~CTR, 1000);
	mPlexImage(L2 & ~CTR, 1000);
}

void rotateHi() {
	//
	mPlexImage(W2 & ~L1, 1000);
	mPlexImage(D1 & ~L1, 1000);
	mPlexImage(W5 & ~L1, 1000);
	mPlexImage(D2 & ~L1, 1000);
}

void rotateLo() {
	mPlexImage(W2 & ~L3, 1000);
	mPlexImage(D1 & ~L3, 1000);
	mPlexImage(W5 & ~L3, 1000);
	mPlexImage(D2 & ~L3, 1000);
}

void layerLift() {
	//
	mPlexImage(L1, 1000);
	mPlexImage(L2, 1000);
	mPlexImage(L3, 1000);
	mPlexImage(L2, 1000);
}

void rotatePlate() {
	mPlexImage(W2, 1000);
	mPlexImage(D1, 1000);
	mPlexImage(W5, 1000);
	mPlexImage(D2, 1000);
}

void runl1v() {
	mPlexImage(VL1, 1000);
	mPlexImage(VL2, 1000);
	mPlexImage(VL3, 1000);
}

void runl2v() {
	mPlexImage(VL4, 1000);
	mPlexImage(VL5, 1000);
	mPlexImage(VL6, 1000);
}

void runl3v() {
	mPlexImage(VL7, 1000);
	mPlexImage(VL8, 1000);
	mPlexImage(VL9, 1000);
}

void runl1h() {
	mPlexImage(VH1, 1000);
	mPlexImage(VH2, 1000);
	mPlexImage(VH3, 1000);
}

void runl2h() {
	mPlexImage(VH4, 1000);
	mPlexImage(VH5, 1000);
	mPlexImage(VH6, 1000);
}

void runl3h() {
	mPlexImage(VH7, 1000);
	mPlexImage(VH8, 1000);
	mPlexImage(VH9, 1000);
}

void testNormalization() {
	uint32_t f = 1;
//	uint32_t fb = 0;
	for (int i = 0; i < 27; i++) {
//		fb += f;
		//		setFrame(fb, 200);
		mPlexImage(0, 300);
		mPlexImage(f, 1000);
		f *= 2;
	}
}

void loop() {

//	rotate1();
//	rotate2();
//	rotateHi();
//	rotateLo();
//	rotateHi();
//	rotateLo();
//	rotateHi();
//	rotateLo();
//	rotateHi();
//	rotatePlate();
//	rotatePlate();
//	circleColsWithCtr();
//	circleColsWithCtr();
//	circleCols();
//	circleCols();
//	setFrame(CTR, 1000);
//	setFrame(L2, 1000);
//	setFrame(CTR, 1000);
//	setFrame(L2, 1000);
//	setFrame(L3 | L1, 1000);
//	setFrame(L2, 1000);
//	setFrame(L3 | L1, 1000);
//	setFrame(L2, 1000);
//	setFrame(L3 | L1, 1000);
//	setFrame(L2, 1000);
//	layerLift();
//	layerLift();
//	rotate2();
//	rotate2();
//	rotate2();
//	layerLift();

//	testNormalization();
	rotatePlate();

	runl1v();
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

int main(void) {
	setUpLedOutputs();

	while (1) {
		loop();
	}
}
