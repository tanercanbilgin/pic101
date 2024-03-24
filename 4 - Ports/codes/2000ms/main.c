#include <16f877.h>
#fuses XT,NOWDT, NOPROTECT, NOBROWNOUT,,NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay (clock=4000000)
#use fast_io(b)
void main()
{
 int led = 0x01;
 setup_psp(PSP_DISABLED) ; //PSP devre disi
 setup_spi(SPI_SS_DISABLED); //SPI devre disi
 setup_timer_1(T1_DISABLED);// T1 devre disi
 setup_timer_2(T2_DISABLED,0,1);// T2 devre disi
 setup_adc_ports(NO_ANALOGS); //analog giris yok
 setup_adc(ADC_OFF) ; //ADC kapali
 setup_CCP1(CCP_OFF); //CCP1 devre disi
 setup_CCP2(CCP_OFF); //CCP2 devredisi

 set_tris_b(0x00); //B portu bütün pinler cikis
 output_b (0x00); //baslangicta 1. led yanik

 while(1)
 {
 output_b(led); //RB0 pin çikisi lojik-1
 delay_ms(1000); //500 ms gecikme
 led = led << 1;

 if (led == 0x00)
 led = 0x01;
 }
}
