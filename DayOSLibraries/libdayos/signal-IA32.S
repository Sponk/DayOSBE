# Contains functions needed for raising  signals

.text

.globl os_signal_handler
.globl c_os_signal_handler

os_signal_handler:
	pusha # Save all registers
	
	pushl %eax # Give the signal number as arg1
	call c_os_signal_handler
	addl $4, %esp
	
	popa # Restore all registers
	jmp *%ecx # Return to the point where the signal was called
	