#include <16f877.h>
#fuses XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay(clock = 4000000)
#use fast_io(b)
#use fast_io(c)
//****** CCP 2 kesmesi *****************
#int_ccp2
void ccp2_kesme() // kesme fonksiyonu
{
    set_Timer1(0);
    output_toggle(pin_b0);
}
//********* ANA PROGRAM FONKSIYONU********
void main()
{
    setup_psp(PSP_DISABLED);          // PSP devre disi
    setup_spi(SPI_SS_DISABLED);       // SPI devre disi
    setup_timer_2(T2_DISABLED, 0, 1); // T2 devre disi
    setup_adc_ports(NO_ANALOGS);      // analog giris yok
    setup_adc(ADC_OFF);               // ADC kapali
    setup_CCP1(CCP_OFF);              // CCP2 devredisi

    set_tris_b(0x00);
    set_tris_c(0x01);
    output_b(0x00);

    setup_timer_1(T1_EXTERNAL | T1_DIV_BY_1);
    setup_ccp2(CCP_COMPARE_INT);

    enable_interrupts(INT_CCP2);
    enable_interrupts(GLOBAL);

    CCP_2 = 0x07;

    set_Timer1(0);
    while (1)
    {
    }
}