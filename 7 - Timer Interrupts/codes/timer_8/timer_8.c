#include <16f877.h>
#FUSES XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#USE delay(clock = 4000000)
#USE fast_io(b)
//****** Dis Kesme Fonksiyonu *****************
#INT_TIMER0
void timerO_kesme()
{
    set_Timer0(56);
    output_toggle(PIN_B0);
}
//********* ANA PROGRAM FONKSIYONU********
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

    set_tris_b(0x0);
    output_b(0x00);

    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_8);
    set_Timer0(56);

    enable_interrupts(INT_TIMER0);
    enable_interrupts(GLOBAL);
    while (1)
    {
    }
}
