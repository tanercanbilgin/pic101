// Write a program with a microcontroller that performs counting on a 7-segment display. 
// Each time the button connected to RB0 pin is pressed, 
// the number displayed on the segment is increased by 1. 
// It is mandatory to implement this using interrupts. 
// (Since RB0 pin is used as an input, you should use RB1-RB7 pins 
// for the display and hence you need to change the numbers in the array accordingly.)

#include <16f877.h>
#fuses XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay(clock = 4000000)
#use fast_io(b)

// *** Sayilar ve Kesme Fonksiyonu ***
int i = 1;
const int digit[10] = {
	0x7E, // 0
	0xC, // 1
	0xB6, // 2
	0x9E, // 3
	0xCC, // 4
	0xDA, // 5
	0xF8, // 6
	0xE, // 7
	0xFE, // 8
	0xDE  // 9
};

#int_ext		   // Dis (External) RB0/INT kesmesi
void ext_kesmesi() // Sayilar ve Kesme Fonksiyonu
{
	output_b(digit[i]); // RB0 pin cikisi lojik-1
	i++;
	if (i == 10)
		i = 0;
}

// ********* ANA PROGRAM FONKSIYONU********
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
	output_b(0x7E);

	ext_int_edge(L_TO_H); // INT_EXT kesmesi yükselen kenarda aktif

	enable_interrupts(INT_EXT); // INT_EXT (RB0) kesmesi aktif
	enable_interrupts(GLOBAL);	// Aktif edilen sekmelere izin ver

	while (1)
	{
	}
}
