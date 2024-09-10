#ifndef _SUS_H_
#define _SUS_H_

#include "interrupt.h"
#include "gpio.h"
#include "timer.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "clock.h"
#include "uart.h"



int get_timer_value();
void mandar_pulso();
void delay1(volatile unsigned int count);
int medir();

#endif