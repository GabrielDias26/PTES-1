/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/07/2024 00:00:00
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Thiago Werlley, thiagowerlley@ufc.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

_start:
   mrs r0, cpsr
   bic r0, r0, #0x1F @ clear mode bits
   orr r0, r0, #0x13 @ set SVC mode
//   orr r0, r0, #0xC0 @ disable FIQ and IRQ
   msr cpsr, r0

   ldr sp, =0x4030CDFC  @6kB public stack  TMR 26.1.3.2

   bl main


.loop: b .loop

