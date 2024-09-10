#ifndef _GPIO_H_
#define _GPIO_H_


#define TOGGLE                                          (0x01u)

// Definindo a ativação do clock.
#define SOC_PRCM_REGS		                            (0x44E00000)
#define SOC_CM_PER_REGS		                            (SOC_PRCM_REGS + 0)

#define CM_PER_GPIO1_CLKCTRL                            0xAC
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE	        (0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK	(0x00040000u)

#define CM_PER_GPIO2_CLKCTRL                            0x44E000AC
#define CM_PER_GPIO2_CLKCTRL_MODULEMODE_ENABLE          0x00000002
#define CM_PER_GPIO2_CLKCTRL_OPTFCLKEN_GPIO_2_GDBCLK    0x00040000

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

#define CM_conf_gpmc_ad0              0x0800
#define CM_conf_gpmc_ad1              0x0804
#define CM_conf_gpmc_ad2              0x0808
#define CM_conf_gpmc_ad3              0x080C
#define CM_conf_gpmc_ad4              0x0810
#define CM_conf_gpmc_ad5              0x0814
#define CM_conf_gpmc_ad6              0x0818
#define CM_conf_gpmc_ad7              0x081C
#define CM_conf_gpmc_ad8              0x0820
#define CM_conf_gpmc_ad9              0x0824
#define CM_conf_gpmc_ad10             0x0828
#define CM_conf_gpmc_ad11             0x082C
#define CM_conf_gpmc_ad12             0x0830
#define CM_conf_gpmc_ad13             0x0834
#define CM_conf_gpmc_ad14             0x0838
#define CM_conf_gpmc_ad15             0x083C
#define CM_conf_gpmc_a0               0x0840
#define CM_conf_gpmc_a1               0x0844
#define CM_conf_gpmc_a2               0x0848
#define CM_conf_gpmc_a3               0x084C
#define CM_conf_gpmc_a4               0x0850
#define CM_conf_gpmc_a5               0x0854
#define CM_conf_gpmc_a6               0x0858
#define CM_conf_gpmc_a7               0x085C
#define CM_conf_gpmc_a8               0x0860
#define CM_conf_gpmc_a9               0x0864
#define CM_conf_gpmc_a10              0x0868
#define CM_conf_gpmc_a11              0x086C
#define CM_conf_gpmc_ben1             0x0878

// Definindo a configuração do MUX.
typedef enum {
   A0 = CM_conf_gpmc_ad0,
   A1 = CM_conf_gpmc_ad1,
   A2 = CM_conf_gpmc_ad2,
   A3 = CM_conf_gpmc_ad3,
   A4 = CM_conf_gpmc_ad4,
   A5 = CM_conf_gpmc_ad5,
   A6 = CM_conf_gpmc_ad6,
   A7 = CM_conf_gpmc_ad7,
   A8 = CM_conf_gpmc_ad8,
   A9 = CM_conf_gpmc_ad9,
   A10 = CM_conf_gpmc_ad10,
   A11 = CM_conf_gpmc_ad11,
   A12 = CM_conf_gpmc_ad12,
   A13 = CM_conf_gpmc_ad13,
   A14 = CM_conf_gpmc_ad14,
   A15 = CM_conf_gpmc_ad15,
   A16 = CM_conf_gpmc_a0,
   A17 = CM_conf_gpmc_a1,
   A18 = CM_conf_gpmc_a2,
   A19 = CM_conf_gpmc_a3,
   A20 = CM_conf_gpmc_a4,
   A21 = CM_conf_gpmc_a5,
   A22 = CM_conf_gpmc_a6,
   A23 = CM_conf_gpmc_a7,
   A24 = CM_conf_gpmc_a8,
   A25 = CM_conf_gpmc_a9,
   A26 = CM_conf_gpmc_a10,
   A27 = CM_conf_gpmc_a11,
   A28 = CM_conf_gpmc_ben1,
} GPMC;

typedef enum gpiomod{
    GPIO0,
    GPIO1,
    GPIO2,
    GPIO3
}gpiomod;

typedef enum Direction{
    OUTPUT,
    INPUT
}Direction;

typedef enum State{
    LOW,
    HIGH
}State;

int Init_gpio(gpiomod mod);
void Init(unsigned int pino, GPMC conf, gpiomod mod,Direction direcao, unsigned int value);
void outState(gpiomod mod, unsigned int pino, State estado);
int gpio_Input(gpiomod mod, unsigned int pino);
void watchdog();

#endif