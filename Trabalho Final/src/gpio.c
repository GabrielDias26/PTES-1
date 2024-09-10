#include "interrupt.h"
#include "gpio.h"
#include "timer.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "clock.h"


int Init_gpio(gpiomod mod){
    unsigned int aux = (1<<18)  |   (1<<2);
    switch(mod){
        case GPIO1:
            ckmSetCLKModuleRegister(CKM_PER_GPIO1_CLKCTRL, aux);
            break;
        case GPIO2:
            ckmSetCLKModuleRegister(CKM_PER_GPIO2_CLKCTRL, aux);
            break;
        case GPIO3:
            ckmSetCLKModuleRegister(CKM_PER_GPIO3_CLKCTRL, aux);
            break;
        default:
            break;
    }
    return 0;
}

void Init(unsigned int pino, GPMC conf, gpiomod mod,Direction direcao, unsigned int value){
    unsigned int val_temp;
    HWREG(SOC_CONTROL_REGS + conf) |= value;
    switch(mod){
        case GPIO1:
            val_temp = HWREG(SOC_GPIO_1_REGS+GPIO_OE);
            break;
        case GPIO2:
            val_temp = HWREG(SOC_GPIO_2_REGS+GPIO_OE);
            break;
        case GPIO3:
            val_temp = HWREG(SOC_GPIO_3_REGS+GPIO_OE);
            break;
        default:
            break;
    }

    if(direcao == OUTPUT){
        val_temp &= ~(1<<pino);
    }
    else if(direcao == INPUT){
        val_temp |= (1<<pino);
    }

    switch(mod){
        case GPIO1:
            HWREG(SOC_GPIO_1_REGS+GPIO_OE) = val_temp;
            break;
        case GPIO2:
            HWREG(SOC_GPIO_2_REGS+GPIO_OE) = val_temp;
            break;
        case GPIO3:
            HWREG(SOC_GPIO_3_REGS+GPIO_OE) = val_temp;
            break;
        default:
            break;
    }
}

void outState(gpiomod mod, unsigned int pino, State estado){
    switch(mod){
        case GPIO1:
            if(estado == HIGH){
                HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<< pino;
            }
            else if(estado == LOW){
                HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<< pino;
            }
            break;
        case GPIO2:
            if(estado == HIGH){
                HWREG(SOC_GPIO_2_REGS+GPIO_SETDATAOUT) = 1<< pino;
            }
            else if(estado == LOW){
                HWREG(SOC_GPIO_2_REGS+GPIO_CLEARDATAOUT) = 1<< pino;
            }
            break;
        case GPIO3:
            if(estado == HIGH){
                HWREG(SOC_GPIO_3_REGS+GPIO_SETDATAOUT) = 1<< pino;
            }
            else if(estado == LOW){
                HWREG(SOC_GPIO_3_REGS+GPIO_CLEARDATAOUT) = 1<< pino;
            }
            break;
        default:
            break;
    }
}

int gpio_Input(gpiomod mod, unsigned int pino) {
    switch(mod){
        case GPIO0:
            if((HWREG(SOC_GPIO_0_REGS+GPIO_DATAIN) & (1<<pino)) != 0){
                return true;
            }
            return false;
            break;
        case GPIO1:
            if((HWREG(SOC_GPIO_1_REGS+GPIO_DATAIN) & (1<<pino)) != 0){
                return true;
            }
            return false;
            break;
        case GPIO2:
            if((HWREG(SOC_GPIO_2_REGS+GPIO_DATAIN) & (1<<pino)) != 0){
                return true;
            }
            return false;
            break;
        case GPIO3:
            if((HWREG(SOC_GPIO_3_REGS+GPIO_DATAIN) & (1<<pino)) != 0){
                return true;
            }
            return false;
            break;
    }
    return 0;
}

void watchdog(){
	HWREG(WDT1+WDT_WSPR) = 0xAAAA;
	while((HWREG(WDT1+WDT_WWPS) & W_PEND_WSPR) != 0x0){};
	HWREG(WDT1+WDT_WSPR) = 0x5555;
	while((HWREG(WDT1+WDT_WWPS) & W_PEND_WSPR) != 0x0){};
}