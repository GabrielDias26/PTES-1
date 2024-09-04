#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
#include "interrupt.h"
#include "gpio.h"
#include "timer.h"
#include "hw_types.h"
#include "soc_AM335x.h"

#define INTC_CONTROL    						        0x48
#define GPIO_IRQSTATUS_RAW_0                            0x24
#define INTC_SIR_IRQ    						        0x40
#define GPIO_IRQSTATUS_SET_0                            0x34
#define GPIO_IRQSTATUS_1                                0x30
#define GPIO_IRQSTATUS_0                                0x2C
#define GPIO_IRQSTATUS_SET_1                            0x38
#define GPIO_RISINGDETECT                               0x148
#define GPIO_FALLINGDETECT                              0x14C
#define INTC_BASE       						        0x48200000
#define MIR_CLEAR0                                      0x88
#define MIR_CLEAR1                                      0xA8
#define MIR_CLEAR2 						                0xC8
#define MIR_CLEAR3 					        	        0xE8

int Interrupt_Setup(unsigned int inter);
void pinInterrup(int x, gpiomod mod,int pino);
int gpioIsrHandler(int x, int pino);

#endif