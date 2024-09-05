#include "interrupt.h"
#include "gpio.h"
#include "timer.h"
#include "hw_types.h"
#include "soc_AM335x.h"

int gpioIsrHandler(int x, int pino){
    if(!x){
        HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_0) |= (1<<pino);
    }
    else{
        HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_1) |= (1<<pino);
    }
    return 1;
}

void pinInterrup(int x, gpiomod mod,int pino){
    switch(mod){
        case GPIO0:
            if(x == 0){
                HWREG(SOC_GPIO_0_REGS+GPIO_IRQSTATUS_SET_0) |= (1<<pino);
                HWREG(SOC_GPIO_0_REGS+GPIO_RISINGDETECT) |= (1<<pino);
            }
            else{
                HWREG(SOC_GPIO_0_REGS+GPIO_IRQSTATUS_SET_1) |= (1<<pino);
                HWREG(SOC_GPIO_0_REGS+GPIO_RISINGDETECT) |= (1<<pino);
            }
            break;
        case GPIO1:
            if(x == 0){
                HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_SET_0) |= (1<<pino);
                HWREG(SOC_GPIO_1_REGS+GPIO_RISINGDETECT) |= (1<<pino);
            }
            else{
                HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_SET_1) |= (1<<pino);
                HWREG(SOC_GPIO_1_REGS+GPIO_RISINGDETECT) |= (1<<pino);
            }
            break;
        case GPIO2:
            if(x == 0){
                HWREG(SOC_GPIO_2_REGS+GPIO_IRQSTATUS_SET_0) |= (1<<pino);
                HWREG(SOC_GPIO_2_REGS+GPIO_RISINGDETECT) |= (1<<pino);
            }
            else{
                HWREG(SOC_GPIO_2_REGS+GPIO_IRQSTATUS_SET_1) |= (1<<pino);
                HWREG(SOC_GPIO_2_REGS+GPIO_RISINGDETECT) |= (1<<pino);
            }
            break;
        case GPIO3:
            if(x == 0){
                HWREG(SOC_GPIO_3_REGS+GPIO_IRQSTATUS_SET_0) |= (1<<pino);
                HWREG(SOC_GPIO_3_REGS+GPIO_RISINGDETECT) |= (1<<pino);
            }
            else{
                HWREG(SOC_GPIO_3_REGS+GPIO_IRQSTATUS_SET_1) |= (1<<pino);
                HWREG(SOC_GPIO_3_REGS+GPIO_RISINGDETECT) |= (1<<pino);
            }
            break;
    }
}

int Interrupt_Setup(unsigned int inter){
    if(inter < 0 || inter > 127){
        return false;
    }
    unsigned int aux = inter >> 5;

    switch(aux){
        case 0:
            HWREG(INTC_BASE + MIR_CLEAR0) |= (1<<(inter%32));
            break;
        case 1:
            HWREG(INTC_BASE + MIR_CLEAR1) |= (1<<(inter%32));
            break;
        case 2:
            HWREG(INTC_BASE + MIR_CLEAR2) |= (1<<(inter%32));
            break;
        case 3:
            HWREG(INTC_BASE + MIR_CLEAR3) |= (1<<(inter%32));
            break;
        default:
            break;
    }
    return true;
}