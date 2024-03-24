#include <16f877.h>
#fuses XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay(clock = 4000000)
#use fast_io(b)
//****** Dis Kesme Fonksiyonu *****************
#INT_TIMER1
void timer1_kesme()
{
    set_timer1(65535); // Timer1 değeri ayarlandı (65536 - x)
    output_toggle(PIN_B0);
}
//********* ANA PROGRAM FONKSIYONU********
void main()
{
    setup_psp(PSP_DISABLED);          // PSP devre disi
    setup_spi(SPI_SS_DISABLED);       // SPI devre disi
    setup_timer_2(T2_DISABLED, 0, 1); // T2 devre disi
    setup_adc_ports(NO_ANALOGS);      // analog giris yok
    setup_adc(ADC_OFF);               // ADC kapali
    setup_CCP1(CCP_OFF);              // CCP1 devre disi
    setup_CCP2(CCP_OFF);              // CCP2 devredisi

    set_tris_b(0x00);
    output_b(0x00);

    setup_timer_1(T1_EXTERNAL | T1_DIV_BY_4); // T1 harici sayma modu, bölme oranı 1:4
    set_timer1(65535); // Timer1 değeri ayarlandı (65536 - x)

    enable_interrupts(INT_TIMER1);
    enable_interrupts(GLOBAL);
    while (1)
    {
    }
}
