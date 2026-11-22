# BLP205-2026-GUZ-FINAL-PROJESI-GRUP-01

## Kampus Kutuphanesi ve Ogrenci Hizmetleri Otomasyonu

Dogus Universitesi Bilgisayar Programciligi **BLP 205 - Veri Yapilari** dersi 2026-2027 Guz Donemi Final Projesi.

---

## Projenin Amaci

Bu proje; bir kampus kutuphanesinin kitap katalogunu, duyuru panosunu, odunc kitap bekleme sirasini, islem gecmisini ve kampus birimleri arasindaki rota bilgilerini C++ veri yapilari kullanarak konsol tabanli tek bir otomasyon altinda yonetmeyi amaclar.

## Kullanilan Veri Yapilari ve Moduller

| Modul | Veri Yapilari / Algoritmalar | Sorumlu Ogrenci |
| :--- | :--- | :--- |
| **Modul 1** | Cift Yonlu Dogrusal Bagli Liste (Kitap Katalogu), Tek Yonlu Dairesel Bagli Liste (Duyuru Panosu), Dosya Islemleri (`ofstream` / `ifstream`) | Bahadir Karasu |
| **Modul 2** | Bagli Liste Tabanli Yigin (Stack - Islem Gecmisi / Undo) ve Kuyruk (Queue - Odunc Bekleme Sirasi) | Umut Gumus |
| **Modul 3** | Dizi Uzerinde Siralama ve Arama (Bubble Sort, Insertion Sort, Quick Sort, Binary Search) | Adnan Alperen Ustun |
| **Modul 4** | Graf (2B Komsuluk Matrisi), BFS, DFS ve Dijkstra En Kisa Kampus Rotasi | Doruk Ulas Yildiz |

## Derleme ve Calistirma

Program C++11 veya uzeri standartlarla derlenmelidir (tum kod ve konsol ciktilari ASCII karakterler ile yazilacaktir):

```bash
g++ -std=c++11 main.cpp modul1.cpp modul2.cpp modul3.cpp modul4.cpp -o kutuphane
./kutuphane
```

Windows (MinGW) ortaminda:

```bash
g++ -std=c++11 main.cpp modul1.cpp modul2.cpp modul3.cpp modul4.cpp -o kutuphane.exe
kutuphane.exe
```

## Menu Ozeti

Program baslatildiginda ana menu acilir ve kullanici ilgili module gecis yapar:
1. **Modul 1:** Bagli Listeler ve Dosya Islemleri (Basa/Sona/Araya Ekle, ID ile Sil, Ileri/Geri Listele, Analiz, Duyuru Panosu, Dosya Yaz/Oku)
2. **Modul 2:** Yigin (Stack) ve Kuyruk (Queue) Islemleri (Enqueue, Dequeue, FIFO Listele, Push, Pop/Undo, Peek/Top, LIFO Listele)
3. **Modul 3:** Siralama ve Arama Algoritmalari (Bubble vs Insertion Sort sayfa sayisina gore, Quick Sort & Binary Search ID'ye gore)
4. **Modul 4:** Graf ve Kampus Rota Analizi (Komsuluk Matrisi, BFS, DFS, Dijkstra En Kisa Rota)
5. **Hizli Tam Demo:** Tum modullerin ornek verilerle sirayla calistirilmasi *(istege bagli)*
0. **Cikis:** `new` ile ayrilan dinamik bellegin `delete` ile temizlenmesi ve cikis

## Ornek Kullanim ve Bilinen Sinirliliklar

- Program baslangicta test amacli ornek kitap, duyuru, ogrenci ve 6 birimli kampus verisi yukler.
- *(Gelistirme ilerledikce ornek kullanim ekran goruntuleri ve bilinen sinirliliklar bu bolume eklenecektir.)*
