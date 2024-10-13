#ifndef OYUN_H
#define OYUN_H

// Kahraman bilgilerini tutan struct
typedef struct {
    char isim[50];            // Kahramanın ismi
    char bonus_turu[20];       // Bonus türü (saldiri, savunma, vb.)
    int bonus_degeri;          // Bonus değeri (örneğin %20)
    char aciklama[100];        // Kahramanın açıklaması
} Kahraman;

// Canavar bilgilerini tutan struct
typedef struct {
    char isim[50];            // Canavarın ismi
    char etki_turu[20];       // Etki türü (saldiri, savunma, vb.)
    int etki_degeri;          // Etki değeri (örneğin %20)
    char aciklama[100];       // Canavarın açıklaması
} Canavar;

// Birimlerin sayısını tutan struct (insan ve ork için)
typedef struct {
    int piyadeler;
    int okcular;
    int suvariler;
    int kusatma_makineleri;
    int ork_dovusculeri;
    int mizrakcilar;
    int varg_binicileri;
    int troller;
} Birimler;

// Araştırma seviyelerini tutan struct (insan ve ork için)
typedef struct {
    int savunma_ustaligi;
    int saldiri_gelistirmesi;
    int kusatma_ustaligi;  // Orklar bu alanı kullanmazsa 0 olur
    int elit_egitim;       // İnsanlar bu alanı kullanmazsa 0 olur
} ArastirmaSeviyesi;

// İnsan İmparatorluğu ve Ork Legi için ana struct
typedef struct {
    Birimler birimler;                    // Birimler
    Kahraman kahramanlar[10];             // Kahramanlar (maksimum 10)
    Canavar canavarlar[10];               // Canavarlar (maksimum 10)
    ArastirmaSeviyesi arastirma;          // Araştırma seviyeleri
} Taraf;

// Oyunun genel durumu için struct
typedef struct {
    Taraf insan_imparatorlugu;
    Taraf ork_legi;
} OyunDurumu;

#endif // OYUN_H
