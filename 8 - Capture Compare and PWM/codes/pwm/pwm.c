#include <16f877.h>
#fuses XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay(clock = 4000000)
#use fast_io(b)
#use fast_io(c)
void main()
{
    setup_psp(PSP_DISABLED);     // PSP devre disi
    setup_spi(SPI_SS_DISABLED);  // SPI devre disi
    setup_timer_1(T1_DISABLED);  // T1 devre disi
    setup_adc_ports(NO_ANALOGS); // analog giris yok
    setup_adc(ADC_OFF);          // ADC kapali
    setup_CCP2(CCP_OFF);         // CCP2 devredisi

    set_tris_b(0x00);
    set_tris_c(0x00);
    output_b(0x00);

    setup_timer_2(T2_DIV_BY_16, 156, 1);
    setup_ccp1(CCP_PWM);
    set_pwm1_duty(12);

    while (1)
    {
    }
}
