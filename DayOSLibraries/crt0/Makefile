USRSRCS = $(shell find usercrt0src/ -name '*.cpp')
USRSRCS += $(shell find usercrt0src/ -name '*.c')

SVCSRCS = $(shell find servicecrt0src/ -name '*.cpp')
SVCSRCS += $(shell find servicecrt0src/ -name '*.c')

USROBJS = $(addsuffix .o,$(basename $(USRSRCS)))
SVCOBJS = $(addsuffix .o,$(basename $(SVCSRCS)))

CC = g++
GCC = gcc
AR = ar
ARFLAGS = rcs

CFLAGS = -m32 -Wall -g -fstack-protector-all -I include -I ../../kernel/sys -I ../libdayos/include -I ../libkernel/include
LDFLAGS = -melf_i386 -T kernel.ld

all: usercrt0 servicecrt0

usercrt0: $(USROBJS)
	@echo "\033[34m[ Linking usercrt0 ]"
	@$(AR) $(ARFLAGS) usercrt0.a $(USROBJS)
	@echo "\033[0m"

servicecrt0: $(SVCOBJS)
	@echo "\033[34m[ Linking servicecrt0 ]"
	@$(AR) $(ARFLAGS) servicecrt0.a $(SVCOBJS)
	@echo "\033[0m"
	
%.o: %.cpp
	@echo -n "\033[32m( Compiling $^ )"
	@echo "\033[31m"
	@$(CC) $(CFLAGS) -c -o $@ $^
	@echo "\033[0m"

%.o: %.c
	@echo -n "\033[32m( Compiling $^ )"
	@echo "\033[31m"
	@$(GCC) $(CFLAGS) -c -o $@ $^
	@echo "\033[0m"

clean:
	@rm -rf $(SVCOBJS) $(USROBJS)
	@rm -rf *.a

.PHONY: clean all
