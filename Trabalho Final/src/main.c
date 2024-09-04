/*Alunos: GABRIEL BARBOSA DIAS - 539956
	  CAIO JORDAN OLIVEIRA DE SIQUEIRA - 509827
*/

#include "interrupt.h"
#include "gpio.h"
#include "timer.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "clock.h"
#include <stdint.h>

#define TIMER2_BASE      0x48040000
#define TIMER_TCLR       (TIMER2_BASE + 0x38)
#define TIMER_TCRR       (TIMER2_BASE + 0x3C)
#define TIMER_TLDR       (TIMER2_BASE + 0x40)
#define TIMER_TTGR       (TIMER2_BASE + 0x44)

#define TIMER2_TCLR      (*(volatile uint32_t *)TIMER_TCLR)
#define TIMER2_TCRR      (*(volatile uint32_t *)TIMER_TCRR)
#define TIMER2_TLDR      (*(volatile uint32_t *)TIMER_TLDR)
#define TIMER2_TTGR      (*(volatile uint32_t *)TIMER_TTGR)

#define TRIGGER_PIN (1<<15)
#define ECHO_PIN    (1<<14)

unsigned int time;

void ISR_Handler(unsigned int interrupcao){
    unsigned int irq_number = HWREG(INTC_BASE+INTC_SIR_IRQ) & 0x7f;
    if(irq_number == 98){
        if(HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_RAW_0)&(1<<16)){
            gpioIsrHandler(buttonPressed(GPIO1, 16), 16);
        }
    }
    HWREG(INTC_BASE+INTC_CONTROL) = 0x1;
}

void pulse(){
    ledState(GPIO1, TRIGGER_PIN, HIGH);
    delay(10, TIMER2);
    ledState(GPIO1, TRIGGER_PIN, LOW);
}

float medir(){
    uint32_t start_time;
    uint32_t end_time;

    while(buttonPressed(GPIO1, ECHO_PIN) == false){
        __asm__("nop");
    }
    start_time = get_timer_value();
    while(buttonPressed(GPIO1, ECHO_PIN) == true){
        __asm__("nop");
    }
    end_time = get_timer_value();
    return end_time - start_time;
}

void timer_init() {
    TIMER2_TCLR = 0;
    
    TIMER2_TLDR = 0;
    TIMER2_TCRR = 0;

    TIMER2_TCLR = (1 << 0) | (1 << 1);
}

uint32_t get_timer_value() {
    return TIMER2_TCRR;
}

int main(void){
    watchdog();
    timer_init();
    Init_gpio(GPIO1);
    Init(TRIGGER_PIN, A15, GPIO1, OUTPUT, 7);
    Init(ECHO_PIN, A14, GPIO1, INPUT, 7);

    return (0);
}