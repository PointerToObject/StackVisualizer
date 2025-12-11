#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
	unsigned __int64 stack[10];
	unsigned __int64 RSP;
	unsigned __int64 RBP;
} ThreadStack;

typedef struct
{
	unsigned __int64 RAX;
	unsigned __int64 RBX;
	unsigned __int64 RCX;
	unsigned __int64 RDX;
	unsigned __int64 RSI;
	unsigned __int64 RDI;
} Registers;

typedef struct
{
	ThreadStack t_stack;
	Registers regs;
	unsigned __int32 id;
} Thread;

void push(Thread* thread, unsigned __int64 value)
{
	memcpy(&thread->t_stack.stack[thread->t_stack.RSP], &value, 8);
	thread->t_stack.RSP += 1;
	printf("push called!\n");
}

void pop(Thread* thread, unsigned __int64* buffer)
{
	thread->t_stack.RSP -= 1;
	memcpy(buffer, &thread->t_stack.stack[thread->t_stack.RSP], 8);
	memset(&thread->t_stack.stack[thread->t_stack.RSP], 0, 8);
	printf("pop called!\n");
}

void call(Thread* thread, unsigned __int64 return_address)
{
	push(thread, return_address);
	printf("call: pushed return address 0x%llx\n", return_address);
}

void ret(Thread* thread)
{
	pop(thread, &thread->regs.RAX);
	printf("ret: popped return address 0x%llx into RAX\n", thread->regs.RAX);
}