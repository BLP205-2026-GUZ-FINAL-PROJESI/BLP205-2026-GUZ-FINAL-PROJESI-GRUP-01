#ifndef MODUL2_H
#define MODUL2_H

#include <string>

// Bagli liste tabanli Yigin (Stack) dugumu - Islem Gecmisi / Undo
struct YiginDugum {
    std::string islemAciklamasi;
    YiginDugum* next;
};

// Bagli liste tabanli Kuyruk (Queue) dugumu - Odunc Kitap Bekleme Sirasi
struct KuyrukDugum {
    std::string ogrenciNo;
    std::string adSoyad;
    std::string talepEdilenKitap;
    KuyrukDugum* next;
};

// Kuyruk yonetim yapisi (front ve rear)
struct Kuyruk {
    KuyrukDugum* front;
    KuyrukDugum* rear;
};

// Yigin (Stack) islemleri
void yiginBaslat(YiginDugum*& top);
void yiginPush(YiginDugum*& top, const std::string& aciklama);
bool yiginPop(YiginDugum*& top, std::string& cikarilan);
void yiginPeek(const YiginDugum* top);
void yiginListele(const YiginDugum* top);
void yiginTemizle(YiginDugum*& top);

// Kuyruk (Queue) islemleri
void kuyrukBaslat(Kuyruk& q);
void kuyrukEnqueue(Kuyruk& q, const std::string& ogrenciNo, const std::string& adSoyad, const std::string& kitapAdi);
bool kuyrukDequeue(Kuyruk& q, std::string& cikarilanBilgi);
void kuyrukListele(const Kuyruk& q);
void kuyrukTemizle(Kuyruk& q);

#endif
