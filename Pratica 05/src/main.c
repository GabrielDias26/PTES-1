#include "interrupt.h"
#include "gpio.h"
#include "timer.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "clock.h"

unsigned int time;

void ISR_Handler(unsigned int interrupcao){
    unsigned int irq_number = HWREG(INTC_BASE+INTC_SIR_IRQ) & 0x7f;
    if(irq_number == 98){
        if(HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_RAW_0)&(1<<16)){
            gpioIsrHandler(buttonPressed(GPIO1, 16), 16);
            time += 100;
            if(time > 1000){
                time = 50;
            }
        }
    }
    HWREG(INTC_BASE+INTC_CONTROL) = 0x1;
}

int main(void){
    watchdog();

    time = 50;
    Init_gpio(GPIO1);
    Init(16, A16, GPIO1, INPUT, 7);
    Init(21, A21, GPIO1, OUTPUT, 7);
    Interrupt_Setup(98);
    pinInterrup(buttonPressed(GPIO1, 16), GPIO1, 16);
    
    while(1){
        ledState(GPIO1, 21, HIGH);
        delay(time, TIMER2);
        ledState(GPIO1, 21, LOW);
        delay(time, TIMER2);
    }
    return (0);
}