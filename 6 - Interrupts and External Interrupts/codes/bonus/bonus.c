//Write a program that counts on a 7-segment display with a 1-second interval, 
//while switching between counting upwards when the button is pressed down 
//and counting downwards when it's released up.
//Hint: For bonus, while the counting operation is performed in the main program, 
//the up-down control can be implemented with the help of interrupts.

#include <16f877.h>
#fuses XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay(clock = 4000000)
#use fast_io(b)

// *** Sayilar ve Kesme Fonksiyonu ***
boolean kontrol = false;
int i = 0;
const int digit[10] = {
   0x7E, // 0
   0xC,  // 1
   0xB6, // 2
   0x9E, // 3
   0xCC, // 4
   0xDA, // 5
   0xF8, // 6
   0xE,  // 7
   0xFE, // 8
   0xDE  // 9
};

#int_ext         // Dis (External) RB0/INT kesmesi
void ext_kesmesi() // Sayilar ve Kesme Fonksiyonu
{
   kontrol = !kontrol;
}

// ********* ANA PROGRAM FONKSIYONU********
void main()
{
   setup_psp(PSP_DISABLED);        // PSP devre disi
   setup_spi(SPI_SS_DISABLED);        // SPI devre disi
   setup_timer_1(T1_DISABLED);        // T1 devre disi
   setup_timer_2(T2_DISABLED, 0, 1); // T2 devre disi
   setup_adc_ports(NO_ANALOGS);     // analog giris yok
   setup_adc(ADC_OFF);              // ADC kapali
   setup_CCP1(CCP_OFF);           // CCP1 devre disi
   setup_CCP2(CCP_OFF);           // CCP2 devredisi

   set_tris_b(0x01); // RB0 portu giris diger bütün pinler cikis
   output_b(0x7E);

   ext_int_edge(L_TO_H); // INT_EXT kesmesi yükselen kenarda aktif

   enable_interrupts(INT_EXT); // INT_EXT (RB0) kesmesi aktif
   enable_interrupts(GLOBAL);   // Aktif edilen sekmelere izin ver

   while (1)
   {
      output_b(digit[i]); // RB0 pin cikisi lojik-1
      delay_ms(500);      // 500 ms gecikme
      if (kontrol)
      {
         i--;
         if (i == -1)
            i = 9;
      }
      else
      {
         i++;
         if (i == 10)
            i = 0;
      }
   }
}
