#include <16f877.h>
#fuses XT,NOWDT, NOPROTECT, NOBROWNOUT,,NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay (clock=4000000)
#use fast_io(b)
void main()
{
 setup_psp(PSP_DISABLED) ; //PSP devre disi
 setup_spi(SPI_SS_DISABLED); //SPI devre disi
 setup_timer_1(T1_DISABLED);// T1 devre disi
 setup_timer_2(T2_DISABLED,0,1);// T2 devre disi
 setup_adc_ports(NO_ANALOGS); //analog giris yok
 setup_adc(ADC_OFF) ; //ADC kapali
 setup_CCP1(CCP_OFF); //CCP1 devre disi
 setup_CCP2(CCP_OFF); //CCP2 devredisi

 set_tris_b(0x00); //B portu bütün pinler cikis
 output_b (0x00); //bütün pinler 0

 while(1)
 {
 // 0x01 0x04 0x10 0x40 = C
 // 0x02 0x08 0x20 0x80 = 
 output_b(0X55); //B Portu bütün pin çikisi lojik-1
 delay_ms(1000); //1000 ms gecikme
 output_b(0xAA); // B Portu bütün pin çikisi lojik-0
 delay_ms(1000); //1000 ms gecikme
 }
}
