#ifndef MACRO_H
#define MACRO_H

#define SET(port,b) (port) |= (1<<(b))
#define CLR(port,b) (port) &= ~(1<<(b))

#define IS_SET(port, pin)            ((port&(1 << pin)) == (1 << pin))
#define IS_NOT_SET(port, pin)         ((port&(1 << pin)) == 0)

#endif
