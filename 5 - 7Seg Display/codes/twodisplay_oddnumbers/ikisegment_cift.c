#include <16f877.h>
#fuses XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay(clock = 4000000)
#use fast_io(a)
#use fast_io(b)
int sayi = 0;
int frame = 0;
int birler = 0;
int onlar = 0;
const int digit[16] = {0x3f, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F,
                       0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
void main()
{
    setup_psp(PSP_DISABLED);          // PSP devre disi
    setup_spi(SPI_SS_DISABLED);       // SPI devre disi
    setup_timer_1(T1_DISABLED);       // T1 devre disi
    setup_timer_2(T2_DISABLED, 0, 1); // T2 devre disi
    setup_adc_ports(NO_ANALOGS);      // analog giris yok
    setup_adc(ADC_OFF);               // ADC kapali
    setup_CCP1(CCP_OFF);              // CCP1 devre disi
    setup_CCP2(CCP_OFF);              // CCP2 devredisi

    set_tris_a(0x00); // A portu bütün pinler cikis
    set_tris_b(0x00); // B portu bütün pinler cikis
    output_b(0x00);   // baslangicta 1. led yanik
    output_a(0x00);

    sayi = 72;
    frame = 0;
    delay_ms(1000);

    while (1)
    {
        birler = sayi % 10;
        onlar = sayi / 10;

        output_b(digit[birler]); // RB0 pin çikisi lojik-1
        output_high(pin_a1);
        delay_ms(5);
        output_low(pin_a1); // 500 ms gecikme

        output_b(digit[onlar]); // RB0 pin çikisi lojik-1
        output_high(pin_a0);
        delay_ms(5);        // 500 ms gecikme
        output_low(pin_a0); // 500 ms gecikme

        frame++;
        if (frame == 100)
        {
            frame = 0;
            sayi++;
            if (sayi == 82)
                sayi = 72;
        }
    }
}
