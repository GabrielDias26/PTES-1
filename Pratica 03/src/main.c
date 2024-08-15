#include "hw_types.h"
#include "soc_AM335x.h"

#define TIME                                            1000000
#define TOGGLE                                          (0x01u)

// Definindo a ativação do clock.
#define SOC_PRCM_REGS		                            (0x44E00000)
#define SOC_CM_PER_REGS		                            (SOC_PRCM_REGS + 0)

#define CM_PER_GPIO1_CLKCTRL                            0xAC
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE	        (0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK	(0x00040000u)

#define WDT1 													0x44E35000
#define WDT_WSPR 												0x48
#define WDT_WWPS												0x34
#define W_PEND_WSPR												(1<<0x4u)


// Definindo a configuração do MUX.
#define CM_conf_gpmc_a5                                 0x0854
#define CM_conf_gpmc_a6                                 0x0858
#define CM_conf_gpmc_a7                                 0x085C
#define CM_conf_gpmc_a8                                 0x0860
#define CM_conf_gpmc_ben1                               0x878
#define CM_conf_gpmc_a0                                 0x840

// Definição da direção do pino.
#define GPIO_OE                                         0x134
#define GPIO_CLEARDATAOUT                               0x190
#define GPIO_SETDATAOUT                                 0x194
#define GPIO_DATAIN                                     0x138

unsigned int flagBlink0;
unsigned int flagBlink1;
unsigned int flagBlink2;
unsigned int flagBlink3;

static void delay();
static void ledInit();

static void ledToggle0(int x);
static void ledToggle1(int x);
static void ledToggle2(int x);
static void ledToggle3(int x);

static bool buttonPressed1();
static bool buttonPressed2();
static void initButton();
static void watchdog();

int main(void){
    watchdog();
    ledInit();
    initButton();
    int i=0;
    while(1){
        if(buttonPressed1()){
            i++;
            ledToggle0(0);
            ledToggle1(0);
            ledToggle2(0);
            ledToggle3(0);
            delay(TIME);
        }
        if(buttonPressed2()){
            i = 0;
            ledToggle0(0);
            ledToggle1(0);
            ledToggle2(0);
            ledToggle3(0);
            delay(TIME);
        }
        if(i > 15){
            i = 0;
            ledToggle0(0);
            ledToggle1(0);
            ledToggle2(0);
            ledToggle3(0);
        }
        if(i == 1){
            ledToggle0(1);
        }
        if(i == 2){
            ledToggle1(1);
        }
        if(i == 3){
            ledToggle0(1);
            ledToggle1(1);
        }
        if(i == 4){
            ledToggle2(1);
        }
        if(i == 5){
            ledToggle2(1);
            ledToggle0(1);
        }
        if(i == 6){
            ledToggle2(1);
            ledToggle1(1);
        }
        if(i == 7){
            ledToggle0(1);
            ledToggle1(1);
            ledToggle2(1);
        }
        if(i == 8){
            ledToggle3(1);
        }
        if(i == 9){
            ledToggle3(1);
            ledToggle0(1);
        }
        if(i == 10){
            ledToggle3(1);
            ledToggle1(1);
        }
        if(i == 11){
            ledToggle3(1);
            ledToggle1(1);
            ledToggle0(1);
        }
        if(i == 12){
            ledToggle3(1);
            ledToggle2(1);
        }
        if(i == 13){
            ledToggle3(1);
            ledToggle2(1);
            ledToggle0(1);
        }
        if(i == 14){
            ledToggle3(1);
            ledToggle2(1);
            ledToggle1(1);
        }
        if(i == 15){
            ledToggle3(1);
            ledToggle2(1);
            ledToggle1(1);
            ledToggle0(1);
        }
    }
    return(0);
}

void ledInit() {
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

void delay(volatile unsigned int x){
    while(x--);
}

void initButton(){
    unsigned int val_temp;
    HWREG(SOC_CM_PER_REGS+CM_PER_GPIO1_CLKCTRL) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_ben1) |= 7;
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a0) |= 7;

    val_temp=(SOC_CONTROL_REGS+GPIO_OE);
	val_temp |= (1<<28);
    val_temp |= (1<<16);
	HWREG(SOC_CONTROL_REGS+GPIO_OE) = val_temp;

}

bool buttonPressed1() {
    if((HWREG(SOC_GPIO_1_REGS+GPIO_DATAIN) & (1<<28)) != 0){
        return true;
    }
    return false;
}

bool buttonPressed2() {
    if((HWREG(SOC_GPIO_1_REGS+GPIO_DATAIN) & (1<<16)) != 0){
        return true;
    }
    return false;
}

void watchdog(){
	HWREG(WDT1+WDT_WSPR) = 0xAAAA;
	while((HWREG(WDT1+WDT_WWPS) & W_PEND_WSPR) != 0x0){};
	HWREG(WDT1+WDT_WSPR) = 0x5555;
	while((HWREG(WDT1+WDT_WWPS) & W_PEND_WSPR) != 0x0){};
}

void ledToggle0(int x) {
    if(x == 1) {
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<21;
    } else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<21;
    }
}

void ledToggle1(int x) {
    if(x == 1) {
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<22;
    } else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<22;
    }
}

void ledToggle2(int x) {
    if(x == 1) {
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<23;
    } else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<23;
    }
}

void ledToggle3(int x) {
    if(x == 1) {
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<24;
    } else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<24;
    }
}