#include <16f877.h>
#fuses XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay(clock = 4000000)
#use fast_io(b)
#use fast_io(d)

const int digit[16] = {0x3f, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F,
                       0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
#define sut1 pin_d0
#define sut2 pin_d1
#define sut3 pin_d2
#define sat1 pin_d4
#define sat2 pin_d5
#define sat3 pin_d6
#define sat4 pin_d7

char tus = 0;
char keypad_oku()
{
    output_d(0x00); // D port'u çikisi sifirlaniyor
    output_high(sat1); // 1. satir lojik-l yapiliyor
    if (input(sut1)) tus = 1; // 1. sütun okunuyor
    if (input(sut2)) tus = 2; // 2. sütun okunuyor
    if (input(sut3)) tus = 3; // 3. sütun okunuyor
    output_low(sat1); // 1. satir lojik-O yapiliyor
    output_high(sat2); // 2. satir lojik-l yapiliyor
    if (input(sut1)) tus = 4; // 4. sütun okunuyor
    if (input(sut2)) tus = 5; // 5. sütun okunuyor
    if (input(sut3)) tus = 6; // 6. sütun okunuyor
    output_low(sat2); // 2. satir lojik-O yapiliyor
    output_high(sat3); // 3. satir lojik-l yapiliyor
    if (input(sut1)) tus = 7; // 7. sütun okunuyor
    if (input(sut2)) tus = 8; // 8. sütun okunuyor
    if (input(sut3)) tus = 9; // 9. sütun okunuyor
    output_low(sat3); // 3. satir lojik-O yapiliyor
    output_high(sat4); // 4. satir lojik-l yapiliyor
    if (input(sut1)) tus = 0xA; // 10. sütun okunuyor
    if (input(sut2)) tus = 0;  // 11. sütun okunuyor
    if (input(sut3)) tus = 0XB; // 12. sütun okunuyor
    output_low(sat4); // 4. satir lojik-O yapiliyor
    return tus;
}

void main()
{
    int x = 0;
    setup_psp(PSP_DISABLED);     // PSP devre disi
    setup_spi(SPI_SS_DISABLED);  // SPI devre disi
    setup_timer_1(T1_DISABLED);  // T1 devre disi
    setup_adc_ports(NO_ANALOGS); // analog giris yok
    setup_adc(ADC_OFF);          // ADC kapali
    setup_CCP2(CCP_OFF);         // CCP2 devredisi

    set_tris_b(0x00);
    set_tris_d(0x0f);
    output_b(0x00);
    while (1)
    {
        x = keypad_oku();
        output_b(digit[x]);
    }
}
