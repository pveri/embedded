/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE (128 * 1024)
#define SRAM_END ((SRAM_START)+(SRAM_SIZE))
#define STACK_START SRAM_END
#define STACK_MSP_START STACK_START
#define STACK_MSP_END ((STACK_MSP_START) - 512)
#define STACK_PSP_START STACK_MSP_END

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

__attribute__((naked)) void change_sp_to_psp(void) {

	__asm volatile (".equ SRAM_END, (0x20000000 + (128 * 1024))"); //ASM way of defining macro
	__asm volatile (".equ PSP_START, ((SRAM_END) - 512)"); // Asm way of defining a MACRO
	__asm volatile ("LDR R0,=PSP_START"); //Set value of R0 to PSP_START macro
	__asm volatile ("MSR PSP, R0");// Initialize PSP to value in R0 (PSP START address)
	__asm volatile("MOV R0,#0X02"); // Set R0 to immediate value 0X02
	__asm volatile("MSR CONTROL,R0"); //Move value from R0 into special register control
	__asm volatile ("BX LR"); // Return equivalent in naked ASM function
	// BX -> Branch Indirect
	// LR -> Pointer to the origin of this function call (in this case, in main())
}

void generate_exception(void) {
	__asm volatile("SVC #0x034");
}


int fun_add(int a, int b, int c, int d) {
	return a+b+c+d;
}

int main(void)
{
	change_sp_to_psp();
	int ret;
	ret = fun_add(1,2,3,4);
	generate_exception();
    /* Loop forever */
	for(;;);
}


void SVC_Handler(void) {
	printf("In SVC handler\n");
}
