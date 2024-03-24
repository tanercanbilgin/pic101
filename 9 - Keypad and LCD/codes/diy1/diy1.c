//Connect two buttons to any two desired pins of the circuit containing an LCD, 
//and increment and decrement a 16-bit number using these buttons. 
//Also, display this number on the LCD screen.

#include <16f877.h>
#fuses XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay(clock = 4000000)
#use fast_io(b)
#define use_portb_lcd TRUE
#include <lcd.c>
void main()
{
    setup_psp(PSP_DISABLED);          // PSP devre disi
    setup_spi(SPI_SS_DISABLED);       // SPI devre disi
    setup_timer_1(T1_DISABLED);       // T1 devre disi
    setup_timer_2(T2_DISABLED, 0, 1); // T1 devre disi
    setup_adc_ports(NO_ANALOGS);      // analog giris yok
    setup_adc(ADC_OFF);               // ADC kapali
    setup_CCP1(CCP_OFF);              // CCP2 devredisi
    setup_CCP2(CCP_OFF);              // CCP2 devredisi

    set_tris_b(0x00);
    lcd_init();

    delay_ms(500);

    int sayi = 0;
    delay_ms(200);

    lcd_gotoxy(1, 1);
    lcd_putc("Sayi:");
    lcd_gotoxy(1, 2);
    printf(lcd_putc, "%d", sayi);

    while (1)
    {
        if (input(pin_a0) == 1)
        {
            delay_ms(500);
            sayi++;
            lcd_gotoxy(1, 1);
            lcd_putc("Sayi:");
            lcd_gotoxy(1, 2);
            printf(lcd_putc, "%d", sayi);
        }
        if (input(pin_a1) == 1)
        {
            delay_ms(500);
            sayi--;
            lcd_gotoxy(1, 1);
            lcd_putc("Sayi:");
            lcd_gotoxy(1, 2);
            printf(lcd_putc, "%d", sayi);
        }
    }
}
