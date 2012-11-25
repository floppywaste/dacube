/*
 * render images
 */

#ifndef IMAGES_H
#define IMAGES_H

/*
 * some demo macros
 */

// layers
#define L1 (uint32_t) 0x1FF
#define L2 (uint32_t) 0x3FE00
#define L3 (uint32_t) 0x7FC0000

// columns
#define C1 (uint32_t) 0x40201
#define C2 C1 << 1
#define C3 C1 << 2
#define C4 C1 << 3
#define C5 C1 << 4
#define C6 C1 << 5
#define C7 C1 << 6
#define C8 C1 << 7
#define C9 C1 << 8

// walls
#define W1 (C1 | C2 | C3)
#define W2 (C4 | C5 | C6)
#define W3 (C7 | C8 | C9)

#define W4 (C1 | C4 | C7)
#define W5 (C2 | C5 | C8)
#define W6 (C3 | C6 | C9)

// lines
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

// diagonal column groups
#define D1 (C1 | C5 | C9)
#define D2 (C3 | C5 | C7)

// diagonal layers
#define D3 (VL1 | VL5 | VL9)
#define D4 (VL7 | VL5 | VL3)

// the center
#define CTR 8192

/*
 * initializes outputs.
 */
void setUpLedOutputs();

/*
 * Sequentially switches on and off the led outputs indicated by the hi bits in the specified image.
 */
void mPlexImage(uint32_t frm, uint16_t repeat);

#endif
