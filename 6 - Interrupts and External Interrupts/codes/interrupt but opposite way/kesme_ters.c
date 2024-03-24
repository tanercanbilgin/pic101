#include <16f877.h>
#fuses XT, NOWDT, NOPROTECT, NOBROWNOUT, , NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay(clock = 4000000)
#use fast_io(b)
//****** Dis Kesme Fonksiyonu *****************
#int_ext		   // Dis (External) RBO/INT kesmesi
void ext_kesmesi() // Dis kesme fonksiyonu
{
	output_toggle(pin_b1);
}
//********* ANA PROGRAM FONKSIYONU********
void main()
{
	setup_psp(PSP_DISABLED);		  // PSP devre disi
	setup_spi(SPI_SS_DISABLED);		  // SPI devre disi
	setup_timer_1(T1_DISABLED);		  // T1 devre disi
	setup_timer_2(T2_DISABLED, 0, 1); // T2 devre disi
	setup_adc_ports(NO_ANALOGS);	  // analog giris yok
	setup_adc(ADC_OFF);				  // ADC kapali
	setup_CCP1(CCP_OFF);			  // CCP1 devre disi
	setup_CCP2(CCP_OFF);			  // CCP2 devredisi

	set_tris_b(0x01); // RB0 portu giris diger bütün pinler cikis
	output_b(0x00);

	ext_int_edge(H_TO_L); // INT_EXT kesmesi yükselen kenarda aktif

	enable_interrupts(INT_EXT); // INT_EXT (RB0) kesmesi aktif
	enable_interrupts(GLOBAL);	// Aktif edilen sekmelere izin ver

	while (1)
	{
	}
}
