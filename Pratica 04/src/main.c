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
#define CM_conf_gpmc_ben1                               0x878 //LED externo
#define CM_conf_gpmc_a0                                 0x840
#define CM_conf_gpmc_a1                                 0x844

// Definição da direção do pino.
#define GPIO_OE                                         0x134
#define GPIO_CLEARDATAOUT                               0x190
#define GPIO_SETDATAOUT                                 0x194
#define GPIO_DATAIN                                     0x138

// Watchdog
#define WDT1 											0x44E35000
#define WDT_WSPR 										0x48
#define WDT_WWPS										0x34
#define W_PEND_WSPR										(1<<0x4u)

// Interrupção
#define INTC_CONTROL    						        0x48
#define GPIO_IRQSTATUS_RAW_0                            0x24
#define INTC_SIR_IRQ    						        0x40
#define GPIO_IRQSTATUS_SET_0                            0x34
#define GPIO_IRQSTATUS_1                                0x30
#define GPIO_IRQSTATUS_0                                0x2C
#define GPIO_IRQSTATUS_SET_1                            0x38
#define GPIO_RISINGDETECT                               0x148
#define GPIO_FALLINGDETECT                              0x14C
#define INTC_BASE       						        0x48200000
#define MIR_CLEAR0                                      0x88
#define MIR_CLEAR1                                      0xA8
#define MIR_CLEAR2 						                0xC8
#define MIR_CLEAR3 					        	        0xE8

unsigned int flagBlink0;

static void watchdog();
void pinInterrup(bool x, int pino);
void delay();
void ledInitEX();
void initButton();
void ledToggle0();
bool buttonPressed1();
bool buttonPressed2();
int Interrupt_Setup(unsigned int inter);
int gpioIsrHandler(bool x, int pino);
void ISR_Handler();

int main(void){
    watchdog();
    flagBlink0 = 0;

    ledInitEX();
    initButton();


Interrupt_Setup(98);
        pinInterrup(buttonPressed1(), 16);
        pinInterrup(buttonPressed2(), 17);


    while(1){
        
        ledToggle0();
        delay(100000000);
    }
    return (0);
}

void ISR_Handler(){
    unsigned int irq_number = HWREG(INTC_BASE+INTC_SIR_IRQ) & 0x7f;
    if(irq_number == 98){
        if(HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_RAW_0)&(1<<16)){
            gpioIsrHandler(buttonPressed1(), 16);
            HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<28;
        }
        else if(HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_RAW_0)&(1<<17)){
            gpioIsrHandler(buttonPressed2(), 17);
            HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<28;
        }
    }
    HWREG(INTC_BASE+INTC_CONTROL) = 0x1;
}

int gpioIsrHandler(bool x, int pino){
    if(!x){
        HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_0) |= (1<<pino);
    }
    else{
        HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_1) |= (1<<pino);
    }
    return 1;
}

void pinInterrup(bool x, int pino){
    if(!x){
        HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_SET_0) |= (1<<pino);
        HWREG(SOC_GPIO_1_REGS+GPIO_RISINGDETECT) |= (1<<pino);
    }
    else{
        HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_SET_1) |= (1<<pino);
        HWREG(SOC_GPIO_1_REGS+GPIO_RISINGDETECT) |= (1<<pino);
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

bool buttonPressed1() {
    if((HWREG(SOC_GPIO_1_REGS+GPIO_DATAIN) & (1<<16)) != 0){
        return true;
    }
    return false;
}

bool buttonPressed2() {
    if((HWREG(SOC_GPIO_1_REGS+GPIO_DATAIN) & (1<<17)) != 0){
        return true;
    }
    return false;
}

void initButton(){
    unsigned int val_temp;
    HWREG(SOC_CM_PER_REGS+CM_PER_GPIO1_CLKCTRL) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a0) |= 7;
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a1) |= 7;

    val_temp=(SOC_CONTROL_REGS+GPIO_OE);
	val_temp |= (1<<16);
    val_temp |= (1<<17);
	HWREG(SOC_CONTROL_REGS+GPIO_OE) = val_temp;

}

void watchdog(){
	HWREG(WDT1+WDT_WSPR) = 0xAAAA;
	while((HWREG(WDT1+WDT_WWPS) & W_PEND_WSPR) != 0x0){};
	HWREG(WDT1+WDT_WSPR) = 0x5555;
	while((HWREG(WDT1+WDT_WWPS) & W_PEND_WSPR) != 0x0){};
}
