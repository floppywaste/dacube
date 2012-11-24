#ifndef MACRO_H
#define MACRO_H

#define SET(port,b) (port) |= (1<<(b))
#define CLR(port,b) (port) &= ~(1<<(b))

#define IS_SET(port, pin)            ((port&(1 << pin)) == (1 << pin))
#define IS_NOT_SET(port, pin)         ((port&(1 << pin)) == 0)

#define IS_OP(cmd) (cmd & 0b10000000)
#define IS_FRM_STRT(cmd) (IS_OP(cmd) && ((cmd & 0b01000000) == 0))
#define IS_FRM_RPT(cmd) ((cmd & 0b11100000) == 0b11100000)
#define FRM_RPT(cmd) (cmd & 0b00011111)

#define LEDS_IN_FRM(cmd) (cmd & 0b00111111)

#define IS_ON(cmd) (cmd & 0b01000000)
#define IS_OFF(cmd) (cmd ^ 0b01000000)

#define X(cmd) (cmd & 0b00110000)
#define Y(cmd) (cmd & 0b00001100)

#define COL(cmd) (cmd & 0b00111100)

#define Z(cmd) (cmd & 0b00000011)

#endif
