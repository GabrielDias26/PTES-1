/*Alunos: 
        GABRIEL BARBOSA DIAS - 539956
	    CAIO JORDAN OLIVEIRA DE SIQUEIRA - 509827
        LUCAS NOBREGA DAMACENA - 535873
*/

#include "interrupt.h"
#include "gpio.h"
#include "timer.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "clock.h"
#include "uart.h"

#define TIMER2_BASE      0x48040000
#define TIMER_TCLR       (TIMER2_BASE + 0x38)
#define TIMER_TCRR       (TIMER2_BASE + 0x3C)
#define TIMER_TLDR       (TIMER2_BASE + 0x40)
#define TIMER_TTGR       (TIMER2_BASE + 0x44)

#define TIMER2_TCLR      (*(volatile int *)TIMER_TCLR)
#define TIMER2_TCRR      (*(volatile int *)TIMER_TCRR)
#define TIMER2_TLDR      (*(volatile int *)TIMER_TLDR)
#define TIMER2_TTGR      (*(volatile int *)TIMER_TTGR)

#define TRIGGER_PIN      (15)
#define ECHO_PIN         (14)
#define RED_LED_PIN      (13)
#define GREEN_LED_PIN    (12)
#define YELLOW_LED_PIN   (16)
#define BUZZER           (17)

#define VELOCIDADE_DO_SOM 343

int get_timer_value() {
    return TIMER2_TCRR;
}

void delay1(volatile unsigned int count) {
    while (count--);
}

void mandar_pulso(){
    outState(GPIO1, TRIGGER_PIN, LOW);
    delay1(20000);
    outState(GPIO1, TRIGGER_PIN, HIGH);
    delay1(100000);
    outState(GPIO1, TRIGGER_PIN, LOW);
}

int medir() {
    int start_time;
    int end_time;

    while (!gpio_Input(GPIO1, ECHO_PIN)) {
        delay1(1);
    }

    start_time = get_timer_value();
    timerEnable(TIMER2);
    while (gpio_Input(GPIO1, ECHO_PIN)) {
        delay1(1);
    }
    end_time = get_timer_value();
    timerDisable(TIMER2);
    HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) = 0x0;
    HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCRR) = 0x0;
    HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TLDR) = 0x0;
    return end_time - start_time;   
}

void ISR_Handler(unsigned int interrupcao){
    /*unsigned int irq_number = HWREG(INTC_BASE+INTC_SIR_IRQ) & 0x7f;
    if(irq_number == 98){
        if(HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_RAW_0)&(1<<16)){
            gpioIsrHandler(gpio_Input(GPIO1, 16), 16);
        }
    }
    HWREG(INTC_BASE+INTC_CONTROL) = 0x1;*/
}

int main(void){
    watchdog();
    
    Init_gpio(GPIO1); 

    timerSetup(TIMER2);

    Init(TRIGGER_PIN, A15, GPIO1, OUTPUT, 7);
    Init(ECHO_PIN, A14, GPIO1, INPUT, 7);
    
    Init(RED_LED_PIN, A13, GPIO1, OUTPUT, 7);
    Init(GREEN_LED_PIN, A12, GPIO1, OUTPUT, 7);
    Init(YELLOW_LED_PIN, A16, GPIO1, OUTPUT, 7);
    Init(BUZZER, A17, GPIO1, OUTPUT, 7);

    outState(GPIO1, RED_LED_PIN, LOW);
    outState(GPIO1, GREEN_LED_PIN, LOW);
    outState(GPIO1, YELLOW_LED_PIN, LOW);
    outState(GPIO1, BUZZER, LOW);

    int tempo;
    int distancia;
    while(true){

        mandar_pulso();
        tempo = medir();
        distancia = (tempo*VELOCIDADE_DO_SOM)/2000;
        if(distancia < 5000){
            outState(GPIO1, RED_LED_PIN, HIGH);
            outState(GPIO1, GREEN_LED_PIN, LOW);
            outState(GPIO1, YELLOW_LED_PIN, LOW);
            outState(GPIO1, BUZZER, LOW);

        }else if((distancia > 5000) && (distancia < 9999)){
            outState(GPIO1, RED_LED_PIN, LOW);
            outState(GPIO1, GREEN_LED_PIN, LOW);
            outState(GPIO1, YELLOW_LED_PIN, HIGH);
            outState(GPIO1, BUZZER, LOW);

        }else if(distancia > 10000){
            outState(GPIO1, RED_LED_PIN, LOW);
            outState(GPIO1, GREEN_LED_PIN, HIGH);
            outState(GPIO1, YELLOW_LED_PIN, LOW);
            outState(GPIO1, BUZZER, LOW);

        }else{
            outState(GPIO1, RED_LED_PIN, LOW);
            outState(GPIO1, GREEN_LED_PIN, LOW);
            outState(GPIO1, YELLOW_LED_PIN, LOW);
            outState(GPIO1, BUZZER, LOW);
        }
        delay(10, TIMER2);
    }

    return (0);
}