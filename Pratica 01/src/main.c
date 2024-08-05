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

// Definição da direção do pino.
#define GPIO_OE                                         0x134
#define GPIO_CLEARDATAOUT                               0x190
#define GPIO_SETDATAOUT                                 0x194

unsigned int flagBlink0;
//unsigned int flagBlink1;
//unsigned int flagBlink2;
//unsigned int flagBlink3;

static void delay();
static void ledInit();
static void ledToggle0();
//static void ledToggle1();
//static void ledToggle2();
//static void ledToggle3();

int main(void){
    flagBlink0 = 0;
    //flagBlink1 = 0;
    //flagBlink2 = 0;
    //flagBlink3 = 0;

    ledInit();
	
	while(1){
		ledToggle0();
        //ledToggle1();
        //ledToggle2();
        //ledToggle3();
		delay(1000000);
	}
	return (0);
}

void delay(volatile unsigned int count) {
    while (count--);
}


void ledInit(){
    unsigned int val_temp;
    HWREG(SOC_CM_PER_REGS+CM_PER_GPIO1_CLKCTRL) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a5) |= 7;
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a6) |= 7;
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a7) |= 7;
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a8) |= 7;

    val_temp = HWREG(SOC_GPIO_1_REGS+GPIO_OE);
    val_temp &= ~(1<<21);
    val_temp &= ~(1<<22);
    val_temp &= ~(1<<23);
    val_temp &= ~(1<<24);
    HWREG(SOC_GPIO_1_REGS+GPIO_OE) = val_temp;
}

void ledToggle0(){
    flagBlink0 ^= TOGGLE;

    if(flagBlink0){
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<21;
    }
    else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<21;
    }
}

/*void ledToggle1(){
    flagBlink1 ^= TOGGLE;

    if(flagBlink1){
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<22;
    }
    else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<22;
    }
}

void ledToggle2(){
    flagBlink2 ^= TOGGLE;

    if(flagBlink2){
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<23;
    }
    else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<23;
    }
}

void ledToggle3(){
    flagBlink3 ^= TOGGLE;

    if(flagBlink3){
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<24;
    }
    else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<24;
    }
}*/