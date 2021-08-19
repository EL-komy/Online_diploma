

CC=arm-none-eabi-
CFLAGS=-gdwarf-2 -mcpu=cortex-m3 

INCS=-I .
LIBS=
SCR =$(wildcard *.c)
OBJ =$(SCR:.c=.o)
AS  =$(wildcard *.s)
ASOBJ=$(AS:.s=.o)
Project_name=toggle

all:$(Project_name).bin
	@echo "=====Build is done====="
%.o:%.s	 
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o:%.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(Project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker.ld $(LIBS) $(OBJ) $(ASOBJ) -o $@ -Map=map_file.map
$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@

symbol: $(Project_name).elf
	&(CC)nm.exe $@

clean:
	rm *.elf *.bin


