#--------------------------------------Makefile-------------------------------------

BUILD_DIR = mkbuild
CFILES = $(shell find ./src -name "*.c" -not -path "./src/uart/*")
OFILES = $(CFILES:./src/%.c=./${BUILD_DIR}/%.o)

GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib


all: clean uart1_build kernel8.img run1
uart1: clean uart1_build kernel8.img run1
uart0: clean uart0_build kernel8.img run0

uart1_build: src/uart/uart1.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/uart/uart1.c -o ./${BUILD_DIR}/uart.o

uart0_build: src/uart/uart0.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/uart/uart0.c -o ./${BUILD_DIR}/uart.o

./${BUILD_DIR}/boot.o: ./link/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./link/boot.S -o ./${BUILD_DIR}/boot.o

./${BUILD_DIR}/%.o: ./src/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: ./${BUILD_DIR}/boot.o ./${BUILD_DIR}/uart.o $(OFILES)
	aarch64-none-elf-ld -nostdlib ./${BUILD_DIR}/boot.o ./${BUILD_DIR}/uart.o $(OFILES) -T ./link/link.ld -o ./${BUILD_DIR}/kernel8.elf
	aarch64-none-elf-objcopy -O binary ./${BUILD_DIR}/kernel8.elf ./${BUILD_DIR}/kernel8.img

clean:
	rm -rf .\${BUILD_DIR}\kernel8.elf .\${BUILD_DIR}\*.o *.img
	mkdir -p ./${BUILD_DIR}/uart
	mkdir -p ./${BUILD_DIR}/utils/error/
	mkdir -p ./${BUILD_DIR}/utils/string/

run1:
	qemu-system-aarch64 -M raspi3b -kernel ./${BUILD_DIR}/kernel8.img -serial null -serial stdio

run0:
	qemu-system-aarch64 -M raspi3b -kernel ./${BUILD_DIR}/kernel8.img -serial stdio
