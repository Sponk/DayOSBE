#include <interrupts.h>
#include <syscall.h>

int registerHandlerProcess(int irqno)
{
	return syscall1(6, irqno);
}

int resetHandlerProcess(int irqno)
{
	return syscall1(7, irqno);
}
