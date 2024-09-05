#ifndef _SUS_H_
#define _SUS_H_

#include "interrupt.h"
#include "gpio.h"
#include "timer.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "clock.h"

#define TIMER2_BASE      0x48040000
#define TIMER_TCLR       (TIMER2_BASE + 0x38)
#define TIMER_TCRR       (TIMER2_BASE + 0x3C)
#define TIMER_TLDR       (TIMER2_BASE + 0x40)
#define TIMER_TTGR       (TIMER2_BASE + 0x44)

#define TIMER2_TCLR      (*(volatile unsigned int *)TIMER_TCLR)
#define TIMER2_TCRR      (*(volatile unsigned int *)TIMER_TCRR)
#define TIMER2_TLDR      (*(volatile unsigned int *)TIMER_TLDR)
#define TIMER2_TTGR      (*(volatile unsigned int *)TIMER_TTGR)

#define TRIGGER_PIN (1<<15)
#define ECHO_PIN    (1<<14)

void pulse();
int medir();
unsigned int Measuretimer(Timer mod);

#endif