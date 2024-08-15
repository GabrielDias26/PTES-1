#include "hw_types.h"
#include "soc_AM335x.h"

#define TIME                                            100000000000
#define TOGGLE                                          (0x01u)

// Definindo a ativação do clock.
#define SOC_PRCM_REGS		                            (0x44E00000)
#define SOC_CM_PER_REGS		                            (SOC_PRCM_REGS + 0)

#define CM_PER_GPIO1_CLKCTRL                            0xAC
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE	        (0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK	(0x00040000u)

// Definindo a configuração do MUX.
#define CM_conf_gpmc_a5                                 0x0854
#define CM_conf_gpmc_a6                                 0x0858
#define CM_conf_gpmc_a7                                 0x085C
#define CM_conf_gpmc_a8                                 0x0860
#define CM_conf_gpmc_ben1                               0x878

// Definição da direção do pino.
#define GPIO_OE                                         0x134
#define GPIO_CLEARDATAOUT                               0x190
#define GPIO_SETDATAOUT                                 0x194

unsigned int flagBlink0;

static void delay();
static void ledInitEX();
static void ledToggle0();

int main(void){
    flagBlink0 = 0;

    ledInitEX();
	
	while(1){
		ledToggle0();
		delay(1000000);
	}
	return (0);
}

void delay(volatile unsigned int count) {
    while (count--);
}

void ledInitEX(){
    unsigned int val_temp;
    HWREG(SOC_CM_PER_REGS+CM_PER_GPIO1_CLKCTRL) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_ben1) |= 7;
    val_temp = HWREG(SOC_GPIO_1_REGS+GPIO_OE);
    val_temp &= ~(1<<28);
    HWREG(SOC_GPIO_1_REGS+GPIO_OE) = val_temp;
}

void ledToggle0(){
    flagBlink0 ^= TOGGLE;

    if(flagBlink0){
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<28;
    }
    else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<28;
    }
}

