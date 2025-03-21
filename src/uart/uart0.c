#include "include/uart/uart0.h"
#include "include/mbox.h"
#include "include/uart/config.h"

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void uart_init()
{
        unsigned int r;

        /* Turn off UART0 */
        UART0_CR = 0x0;

        /* Setup GPIO pins 14 and 15 */

        /* Set GPIO14 and GPIO15 to be pl011 TX/RX which is ALT0	*/
        r = GPFSEL1;
        r &=  ~((7 << 12) | (7 << 15)); //clear bits 17-12 (FSEL15, FSEL14)
        r |= (0b100 << 12)|(0b100 << 15);   //Set value 0b100 (select ALT0: TXD0/RXD0)

        if (cf.handshake == &handshakes[1]) {
                r &= ~((7 << 18) | (7 << 21));
                r |= ((7 << 18) | (7 << 21));
        }

        GPFSEL1 = r;


        /* enable GPIO 14, 15 */
#ifdef RPI3 //RPI3
        GPPUD = 0;            //No pull up/down control
	//Toogle clock to flush GPIO setup
	r = 150; while(r--) { asm volatile("nop"); } //waiting 150 cycles
	GPPUDCLK0 = (1 << 14)|(1 << 15); //enable clock for GPIO 14, 15

        if (cf.handshake == &handshakes[1]) {
                GPPUDCLK0 |= (1 << 16) | (1 << 17);
        }

        r = 150; while(r--) { asm volatile("nop"); } //waiting 150 cycles
	GPPUDCLK0 = 0;        // flush GPIO setup

#else //RPI4
        r = GPIO_PUP_PDN_CNTRL_REG0;
        r &= ~((3 << 28) | (3 << 30)); //No resistor is selected for GPIO 14, 15
        GPIO_PUP_PDN_CNTRL_REG0 = r;
        if (cf.handshake == &handshakes[1]) {
                r = GPIO_PUP_PDN_CNTRL_REG1;
                r &= ~((3 << 0) | (3 << 2)); // no resistor
                GPIO_PUP_PDN_CNTRL_REG1 = r;

                // GPIO_PUP_PDN_CNTRL_REG1 &= ~((3 << 0) | (3 << 2));
        }
#endif

        /* Mask all interrupts. */
        UART0_IMSC = 0;

        /* Clear pending interrupts. */
        UART0_ICR = 0x7FF;

        float baud_divider = (float) UART_FREQUENCY / (16 * cf.baud_rate);
        int IBRD = (int) baud_divider;

        float frac = (float) (baud_divider - IBRD) * 64 + 0.5f;
        float diff = frac - (int) frac;
        frac = (diff >= 0.5) ? frac + 0.5f : frac;

        int FBRD = (int) frac;

        /* Set up Baud Rate */
        UART0_IBRD = IBRD;
        UART0_FBRD = FBRD;

        UART0_LCRH = cf.parity->value | UART0_LCRH_FEN | cf.data_bit->value | cf.stop_bit->value;

        UART0_CR = cf.handshake->value | UART0_CR_UARTEN | UART0_CR_TXE | UART0_CR_RXE;
}

/**
 * Send a character
 */
void uart_sendc(char c) {

        /* Check Flags Register */
        /* And wait until transmitter is not full */
        do {
                asm volatile("nop");
        } while (UART0_FR & UART0_FR_TXFF);

        /* Write our data byte out to the data register */
        UART0_DR = c ;
}

/**
 * Receive a character
 */
char uart_getc() {
        char c = 0;

        /* Check Flags Register */
        /* Wait until Receiver is not empty
         * (at least one byte data in receive fifo)*/
        do {
                asm volatile("nop");
        } while ( UART0_FR & UART0_FR_RXFE );

        /* read it and return */
        c = (unsigned char) (UART0_DR);

        /* convert carriage return to newline */
        return (c == '\r' ? '\n' : c);
}

/**
 * Display a string
 */
void uart_puts(const char *s) {
        while (*s) {
                /* convert newline to carriage return + newline */
                if (*s == '\n')
                        uart_sendc('\r');
                uart_sendc(*s++);
        }
}

void uart_hex(unsigned int num)
{
        uart_puts("0x");
        for (int pos = 28; pos >= 0; pos = pos - 4)
        {
                // Get highest 4-bit nibble
                char digit = (num >> pos) & 0xF;
                /* Convert to ASCII code */
                // 0-9 => '0'-'9', 10-15 => 'A'-'F'
                digit += (digit > 9) ? (-10 + 'A') : '0';
                uart_sendc(digit);
        }
}
/**
 * Display a value in decimal format
 */
void uart_dec(int num)
{
        // A string to store the digit characters
        char str[33] = "";
        // Calculate the number of digits
        int len = 1;
        int temp = num;
        while (temp >= 10)
        {
                len++;
                temp = temp / 10;
        }
        // Store into the string and print out
        for (int i = 0; i < len; i++)
        {
                int digit = num % 10; // get last digit
                num = num / 10;       // remove last digit from the number
                str[len - (i + 1)] = digit + '0';
        }
        str[len] = '\0';
        uart_puts(str);
}