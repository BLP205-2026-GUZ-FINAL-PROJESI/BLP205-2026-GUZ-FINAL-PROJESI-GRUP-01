#ifndef MODUL1_H
#define MODUL1_H

#include "veri_yapilari.h"
#include <string>

// Cift yonlu dogrusal bagli liste dugumu (Kitap Katalogu)
struct KitapDugum {
    Kitap veri;
    KitapDugum* prev;
    KitapDugum* next;
};

// Tek yonlu dairesel bagli liste dugumu (Duyuru Panosu)
struct DuyuruDugum {
    std::string mesaj;
    DuyuruDugum* next;
};

// Katalog listesi yonetim yapisi
struct KitapKatalog {
    KitapDugum* head;
    KitapDugum* tail;
};

// Baslatma fonksiyonlari
void katalogBaslat(KitapKatalog& katalog);

// Yardimci kontroller
bool kitapIdVarMi(const KitapKatalog& katalog, int id);
int katalogSayisi(const KitapKatalog& katalog);

// Cift yonlu bagli liste islemleri
bool kitapBasaEkle(KitapKatalog& katalog, const Kitap& kitap);
bool kitapSonaEkle(KitapKatalog& katalog, const Kitap& kitap);
bool kitapArayaEkle(KitapKatalog& katalog, int hedefId, const Kitap& kitap);
bool kitapSil(KitapKatalog& katalog, int id);
void ileriListele(const KitapKatalog& katalog);
void geriListele(const KitapKatalog& katalog);
void katalogAnaliz(const KitapKatalog& katalog, int sayfaEsigi);

// Tek yonlu dairesel bagli liste islemleri (Duyuru Panosu)
void duyuruEkle(DuyuruDugum*& duyuruHead, const std::string& mesaj);
void duyuruListele(const DuyuruDugum* duyuruHead);

// Dosya islemleri (ofstream / ifstream)
bool katalogDosyayaYaz(const KitapKatalog& katalog, const std::string& dosyaAdi);
bool katalogDosyadanOkuVeGoster(const std::string& dosyaAdi);

// Modul 3 icin bagli listeden dinamik diziye aktarma
Kitap* katalogDiziyeAktar(const KitapKatalog& katalog, int& boyut);

// Bellek temizleme (delete)
void kitapListesiTemizle(KitapKatalog& katalog);
void duyuruListesiTemizle(DuyuruDugum*& duyuruHead);

#endif
