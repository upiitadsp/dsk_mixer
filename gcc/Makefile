INCLUDE_DIRS:= device/include cmsis/include ../include
SOURCE_DIRS:=  device/source ../source

CFILES:= system_TM4C123.c adc.c dac.c main.c spi.c timer.c 
ASM_FILES:= startup_ARMCM4.S



INCLUDE_FLAGS:=$(patsubst %,-I%,$(INCLUDE_DIRS)) 
TCHIP=TM4C123GH6PM
CC=arm-none-eabi-gcc
CFLAGS=-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c99 -g
CPPFLAGS= $(INCLUDE_FLAGS) -D$(TCHIP)
vpath %.h $(INCLUDE_DIRS)
vpath %.c $(SOURCE_DIRS)
vpath %.S device/source
vpath %.o objects

COBJECTS:= $(patsubst %.c,%.o,$(CFILES)) 
ASMOBJECTS:= $(patsubst %.S,%.o,$(ASM_FILES))

all: salida.elf 
objects:
	mkdir objects
salida.elf: objects $(COBJECTS) $(ASMOBJECTS) fir.o
	$(CC) $(CFLAGS) -Ldevice -Tgcc_arm.ld objects/*.o  -o $@
$(COBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o objects/$@
$(ASMOBJECTS): %.o: %.S
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o objects/$@
fir.o: fir.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -O3 -c $< -o objects/$@

.PHONY:clean rebuild burn
clean:
	rm -f  *.elf
	rm -fr objects
rebuild: clean all
burn: salida.elf
	/usr/bin/openocd -fboard/ek-tm4c123gxl.cfg -c"init" -c"reset" -c"sleep 300" -c"reset halt" -c"sleep 300" -c"flash write_image erase salida.elf 0x00 elf" -c"reset" -c"shutdown"
debug: salida.elf
	/usr/bin/openocd -fboard/ek-tm4c123gxl.cfg &
	sleep 1 ;
	! echo "reset" | telnet localhost 4444 &> /dev/null ;
	! echo "reset halt" | telnet localhost 4444 &> /dev/null ;
	sleep 0.5 ;
	arm-none-eabi-gdb --tui --eval-command="target remote localhost:3333" salida.elf ;
	! echo "reset" | telnet localhost 4444 &> /dev/null;
	sleep 0.5 ;
	! echo "shutdown" | telnet localhost 4444 &> /dev/null;
	sleep 0.1 ;