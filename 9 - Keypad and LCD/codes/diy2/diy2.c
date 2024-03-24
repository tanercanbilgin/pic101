//Generate a square wave using TIMER1 unit. 
//Change the frequency of the square wave using the buttons. 
//Display this value on the LCD screen.

#include <16f877a.h>

#fuses XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay(clock = 4000000)
#use fast_io(b)
#use fast_io(c)
#define use_portb_lcd TRUE
#include <lcd.c>

float frekans; // Frekans değeri
int16 hesaplanan;

#int_timer1
void timer1_isr(void)
{
    set_timer1(hesaplanan);
    output_toggle(pin_c0); // C0 pinini her kesmede toggle yaparak kare dalga üret
}

void main()
{
    setup_psp(PSP_DISABLED);
    setup_spi(SPI_SS_DISABLED);
    setup_timer_2(T2_DISABLED, 0, 1);
    setup_adc_ports(NO_ANALOGS);
    setup_adc(ADC_OFF);
    setup_CCP1(CCP_OFF);
    setup_CCP2(CCP_OFF);
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
    enable_interrupts(INT_TIMER1);
    enable_interrupts(GLOBAL);

    set_tris_b(0x00);
    set_tris_c(0x00);
    hesaplanan = 60000;
    set_timer1(hesaplanan);
    lcd_init();
    delay_ms(500);

    frekans = 502.0; // Başlangıç frekansını belirle
    while (1)
    {
        if (input(pin_a0) == 1) // A0 pinine bağlı buton kontrolü
        {
            delay_ms(50);
            // Buton basıldığında frekansı arttır
            hesaplanan += 100;
            while (input(pin_a0) == 1)
                ; // Buton bırakılana kadar bekle
        }

        if (input(pin_a1) == 1) // A1 pinine bağlı buton kontrolü
        {
            delay_ms(50);
            // Buton basıldığında frekansı azalt
            hesaplanan -= 100;
            while (input(pin_a1) == 1)
                ; // Buton bırakılana kadar bekle
        }
        frekans = 1.0/((65536 - hesaplanan)*0.000001)/2.0;
        lcd_putc("\f");
        lcd_gotoxy(1, 1);
        printf(lcd_putc, "%f Hz", frekans); // Frekansı LCD'ye yazdır
        lcd_gotoxy(1, 2);
        printf(lcd_putc, "%lu", hesaplanan); // Frekansı LCD'ye yazdır


        // TIMER1 ayarlarını güncelle
        //set_timer1(65536 - (int)((1000000.0 / (4.0 * frekans))));

        delay_ms(500); // 500 ms bekle
    }
}
