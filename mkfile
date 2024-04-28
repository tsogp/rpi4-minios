#--------------------------------------Makefile-------------------------------------

CFILES = $(shell find ./src -name "*.c" -not -path "./src/uart/*")
OFILES = $(CFILES:./src/%.c=./build/%.o)

GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib

all: clean uart1_build kernel8.img run1
uart1: clean uart1_build kernel8.img run1
uart0: clean uart0_build kernel8.img run0

uart1_build: src/uart/uart1.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/uart/uart1.c -o ./build/uart.o

uart0_build: src/uart/uart0.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/uart/uart0.c -o ./build/uart.o

./build/boot.o: ./link/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./link/boot.S -o ./build/boot.o

./build/%.o: ./src/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: ./build/boot.o ./build/uart.o $(OFILES)
	aarch64-none-elf-ld -nostdlib ./build/boot.o ./build/uart.o $(OFILES) -T ./link/link.ld -o ./build/kernel8.elf
	aarch64-none-elf-objcopy -O binary ./build/kernel8.elf kernel8.img

clean:
	rm -rf .\build\kernel8.elf .\build\*.o *.img
	mkdir -p ./build/uart
	mkdir -p ./build/utils/error/
	mkdir -p ./build/utils/string/

run1:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial null -serial stdio

run0:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio
