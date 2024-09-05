#include "sus.h"
#include "timer.h"
#include "interrupt.h"
#include "gpio.h"
#include "hw_types.h"
#include "soc_AM335x.h"

unsigned int timer;

void pulse(){
    ledState(GPIO1, 15, HIGH);
    delay(10, TIMER2);
    ledState(GPIO1, 15, LOW);
}

int medir(){
    unsigned int start_time;
    unsigned int end_time;

    while(buttonPressed(GPIO1, 14) == false){
        __asm__("nop");
    }
    start_time = get_timer_value();
    while(buttonPressed(GPIO1, 14) == true){
        __asm__("nop");
    }
    end_time = get_timer_value();
    return end_time - start_time;
}

unsigned int Measuretimer(Timer mod, int duration){
    switch(mod){
        case TIMER2:
            HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TLDR) = 0;
            break;
        case TIMER3:
            HWREG(SOC_DMTIMER_3_REGS + DMTIMER_TLDR) = 0;
            break;
        case TIMER4:
            HWREG(SOC_DMTIMER_4_REGS + DMTIMER_TLDR) = 0;
            break;
        case TIMER5:
            HWREG(SOC_DMTIMER_5_REGS + DMTIMER_TLDR) = 0;
            break;
        case TIMER6:
            HWREG(SOC_DMTIMER_6_REGS + DMTIMER_TLDR) = 0;
            break;
        case TIMER7:
            HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TLDR) = 0;
            break;
        default:
            break;
    }

    timerEnable(mod);
    unsigned startValue;

    switch(mod){
        case TIMER2:
            startValue = HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCRR);
            break;
        case TIMER3:
            startValue = HWREG(SOC_DMTIMER_3_REGS + DMTIMER_TCRR);
            break;
        case TIMER4:
            startValue = HWREG(SOC_DMTIMER_4_REGS + DMTIMER_TCRR);
            break;
        case TIMER5:
            startValue = HWREG(SOC_DMTIMER_5_REGS + DMTIMER_TCRR);
            break;
        case TIMER6:
            startValue = HWREG(SOC_DMTIMER_6_REGS + DMTIMER_TCRR);
            break;
        case TIMER7:
            startValue = HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCRR);
            break;
        default:
            break;
    }

    unsigned int currentTime;
    do{
        switch(mod){
            case TIMER2:
                currentTime = HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCRR);
                break;
            case TIMER3:
                currentTime = HWREG(SOC_DMTIMER_3_REGS + DMTIMER_TCRR);
                break;
            case TIMER4:
                currentTime = HWREG(SOC_DMTIMER_4_REGS + DMTIMER_TCRR);
                break;
            case TIMER5:
                currentTime = HWREG(SOC_DMTIMER_5_REGS + DMTIMER_TCRR);
                break;
            case TIMER6:
                currentTime = HWREG(SOC_DMTIMER_6_REGS + DMTIMER_TCRR);
                break;
            case TIMER7:
                currentTime = HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCRR);
                break;
            default:
                break;
        }
    }
    while((currentTime - startValue) < duration);
    timerDisable(mod);
    return (currentTime - startValue);
}