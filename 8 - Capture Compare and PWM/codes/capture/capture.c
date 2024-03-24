#include <16f877.h>
#fuses XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay(clock = 4000000)
#use fast_io(b)
#use fast_io(c)

#int_ccp1
void ccp1_kesme() // CCP1 kesmesi fonksiyonu
{
    set_Timer1(0); // Timer1'i sıfırla

    // CCP1 modül tarafından yakalanan değeri kontrol et
    if (CCP_1 < 10000)
        output_b(0x01); // CCP1 tarafından yakalanan değer 10000'den küçükse kırmızı LED'i yak
    else
        output_b(0x02); // CCP1 tarafından yakalanan değer 10000'den büyükse yeşil LED'i yak
}

//********* ANA PROGRAM FONKSIYONU********
void main()
{
    setup_psp(PSP_DISABLED);          // PSP devre dışı
    setup_spi(SPI_SS_DISABLED);       // SPI devre dışı
    setup_timer_2(T2_DISABLED, 0, 1); // T2 devre dışı
    setup_adc_ports(NO_ANALOGS);      // analog giriş yok
    setup_adc(ADC_OFF);               // ADC kapalı
    setup_CCP2(CCP_OFF);              // CCP2 devre dışı

    set_tris_b(0x0); // B portunu çıkış olarak ayarla
    set_tris_c(0x4); // C portunun C2 pini (CCP1 modülü girişi) giriş olarak ayarla
    output_b(0x00);  // B portunu temizle

    setup_timer_1(T1_INTERNAL | T1_DIV_BY_1); // Timer1'i içsel osilatör ile ve bölme oranı 1 olarak ayarla
    set_Timer1(0); // Timer1'i sıfırla

    setup_ccp1(CCP_CAPTURE_RE); // CCP1 modülünü yükselen kenar yakalama modunda ayarla

    enable_interrupts(INT_CCP1); // CCP1 kesmelerini etkinleştir
    enable_interrupts(GLOBAL);   // Genel kesmeleri etkinleştir

    CCP_1 = 0x00; // CCP1 sıfırla

    while (1)
    {
    }
}
