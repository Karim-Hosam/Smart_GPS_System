#ifndef Bit_Utilies
#define Bit_Utilies

#define READ_BIT(reg1,bit)   ((reg1>>bit)&1)
#define READ_REG(reg)        (reg&0xff)

#define SET(reg,val)        reg |= val
#define SET_BIT(reg,val)    reg |= (1<<val)

#define CLEAR(reg,val)        reg &=~val
#define CLEAR_BIT(reg,val)    reg &=~(1<<val)

#endif