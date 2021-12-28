/*
 * syscalls.h
 *
 *  Created on: Nov. 17, 2021
 *      Author: peter
 */

#ifndef SYSCALLS_H_
#define SYSCALLS_H_
#define DEMCR        			*((volatile uint32_t*) 0xE000EDFCU )

/* ITM register addresses */
#define ITM_STIMULUS_PORT0   	*((volatile uint32_t*) 0xE0000000 )
#define ITM_TRACE_EN          	*((volatile uint32_t*) 0xE0000E00 )

void ITM_SendChar(uint8_t ch);
__attribute__((weak)) int _write(int file, char *ptr, int len);

#endif /* SYSCALLS_H_ */
