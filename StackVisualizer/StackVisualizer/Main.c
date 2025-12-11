#include "Main.h"



int main(int argc, char** argv)
{
	Thread thread1 = { 0 };

	thread1.id = 1;

	char input[256];

	while (1)
	{
		printf("===== STACK =====\n");
		for (int i = 0; i < 10; i++)
		{
			printf("[ %d ] [  %llu  ]\n", i, thread1.t_stack.stack[i]);
		}
		printf("\n===== REGISTERS =====\n");
		printf("RAX = 0x%llx (%llu)\n", thread1.regs.RAX, thread1.regs.RAX);
		printf("RBX = 0x%llx\n", thread1.regs.RBX);
		printf("RCX = 0x%llx\n", thread1.regs.RCX);
		printf("RDX = 0x%llx\n", thread1.regs.RDX);
		printf("RSP = 0x%llx\n", thread1.t_stack.RSP);
		printf("RBP = 0x%llx\n", thread1.t_stack.RBP);

		printf("\nEnter command: ");

		fgets(input, 256, stdin);

		if (strncmp(input, "push", 4) == 0)
		{
			unsigned __int64 val;
			sscanf(input, "push %llu", &val);
			push(&thread1, val);
		}
		else if (strncmp(input, "pop", 3) == 0)
		{
			char reg[10];
			sscanf(input, "pop %s", reg);

			if (strcmp(reg, "rax") == 0)
			{
				pop(&thread1, &thread1.regs.RAX);
			}
			else if (strcmp(reg, "rbx") == 0)
			{
				pop(&thread1, &thread1.regs.RBX);
			}
			else if (strcmp(reg, "rcx") == 0)
			{
				pop(&thread1, &thread1.regs.RCX);
			}
			else if (strcmp(reg, "rdx") == 0)
			{
				pop(&thread1, &thread1.regs.RDX);
			}
		}
		else if (strncmp(input, "mov", 3) == 0)
		{
			char dest[20];
			char src[20];
			sscanf(input, "mov %s %s", dest, src);

			if (strcmp(dest, "rax") == 0)
			{
				unsigned __int64 val;
				sscanf(src, "%llx", &val);
				thread1.regs.RAX = val;
			}
			else if (strcmp(dest, "rbx") == 0)
			{
				unsigned __int64 val;
				sscanf(src, "%llx", &val);
				thread1.regs.RBX = val;
			}
			else if (strcmp(dest, "rcx") == 0)
			{
				unsigned __int64 val;
				sscanf(src, "%llx", &val);
				thread1.regs.RCX = val;
			}
			else if (strcmp(dest, "rdx") == 0)
			{
				unsigned __int64 val;
				sscanf(src, "%llx", &val);
				thread1.regs.RDX = val;
			}
			else if (dest[0] == '[')
			{
				if (strstr(dest, "rsp") != NULL)
				{
					int offset = 0;
					if (strstr(dest, "-") != NULL)
					{
						sscanf(dest, "[rsp-%d]", &offset);
						offset = -offset;
					}
					else if (strstr(dest, "+") != NULL)
					{
						sscanf(dest, "[rsp+%d]", &offset);
					}

					unsigned __int64 val;
					sscanf(src, "%llx", &val);
					thread1.t_stack.stack[thread1.t_stack.RSP + offset] = val;
				}
			}
		}
		else if (strncmp(input, "call", 4) == 0)
		{
			unsigned __int64 addr;
			sscanf(input, "call %llx", &addr);
			call(&thread1, addr);
		}
		else if (strncmp(input, "ret", 3) == 0)
		{
			ret(&thread1);
		}

		Sleep(250);
		system("CLS");
	}
}