#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#ifdef __cplusplus
extern "C" {
#endif

int registerHandlerProcess(int irqno);
int resetHandlerProcess(int irqno);

#ifdef __cplusplus
}
#endif

#endif
 
