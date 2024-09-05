/*Alunos: GABRIEL BARBOSA DIAS - 539956
	  CAIO JORDAN OLIVEIRA DE SIQUEIRA - 509827
*/

#include "interrupt.h"
#include "gpio.h"
#include "timer.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "clock.h"
#include "sus.h"
#include <stdint.h>



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



int main(void){
    watchdog();
    Init_gpio(GPIO1);
    Init(15, A15, GPIO1, OUTPUT, 7);
    Init(14, A14, GPIO1, INPUT, 7);
    while(1){
        timer_init();
        pulse();
        get_timer_value();
        medir();
        timerDisable(TIMER2);
    }

    return (0);
}