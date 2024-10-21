#include <stdio.h>
#include <stdlib.h>
#include "oyun.h"  // heroesParse.h başlık dosyasını dahil ediyoruz

int main() {
    // JSON dosyasını oku
    char *json = readFile("heroes.json");
    if (json == NULL) {
        return 1;
    }

    // Imparatorluk struct'ını oluştur
    Imparatorluk imparatorluk;

    // JSON'u ayrıştır
    parseJSON(json, &imparatorluk);

    // Verileri ekrana yazdır
    printf("Alparslan: %s, %s, %s\n", imparatorluk.insan_imparatorlugu.Alparslan.bonus_turu,
                                      imparatorluk.insan_imparatorlugu.Alparslan.bonus_degeri,
                                      imparatorluk.insan_imparatorlugu.Alparslan.aciklama);

    printf("Fatih Sultan Mehmet: %s, %s, %s\n", imparatorluk.insan_imparatorlugu.Fatih_Sultan_Mehmet.bonus_turu,
                                                imparatorluk.insan_imparatorlugu.Fatih_Sultan_Mehmet.bonus_degeri,
                                                imparatorluk.insan_imparatorlugu.Fatih_Sultan_Mehmet.aciklama);

    printf("Mete Han: %s, %s, %s\n", imparatorluk.insan_imparatorlugu.Mete_Han.bonus_turu,
                                     imparatorluk.insan_imparatorlugu.Mete_Han.bonus_degeri,
                                     imparatorluk.insan_imparatorlugu.Mete_Han.aciklama);

    printf("Yavuz Sultan Selim: %s, %s, %s\n", imparatorluk.insan_imparatorlugu.Yavuz_Sultan_Selim.bonus_turu,
                                               imparatorluk.insan_imparatorlugu.Yavuz_Sultan_Selim.bonus_degeri,
                                               imparatorluk.insan_imparatorlugu.Yavuz_Sultan_Selim.aciklama);

    printf("Tugrul Bey: %s, %s, %s\n", imparatorluk.insan_imparatorlugu.Tugrul_Bey.bonus_turu,
                                       imparatorluk.insan_imparatorlugu.Tugrul_Bey.bonus_degeri,
                                       imparatorluk.insan_imparatorlugu.Tugrul_Bey.aciklama);

    printf("Goruk Vahsi: %s, %s, %s\n", imparatorluk.ork_legi.Goruk_Vahsi.bonus_turu,
                                        imparatorluk.ork_legi.Goruk_Vahsi.bonus_degeri,
                                        imparatorluk.ork_legi.Goruk_Vahsi.aciklama);

    printf("Thruk Kemikkiran: %s, %s, %s\n", imparatorluk.ork_legi.Thruk_Kemikkiran.bonus_turu,
                                             imparatorluk.ork_legi.Thruk_Kemikkiran.bonus_degeri,
                                             imparatorluk.ork_legi.Thruk_Kemikkiran.aciklama);

    printf("Vrog Kafakiran: %s, %s, %s\n", imparatorluk.ork_legi.Vrog_Kafakiran.bonus_turu,
                                           imparatorluk.ork_legi.Vrog_Kafakiran.bonus_degeri,
                                           imparatorluk.ork_legi.Vrog_Kafakiran.aciklama);

    printf("Ugar Zalim: %s, %s, %s\n", imparatorluk.ork_legi.Ugar_Zalim.bonus_turu,
                                       imparatorluk.ork_legi.Ugar_Zalim.bonus_degeri,
                                       imparatorluk.ork_legi.Ugar_Zalim.aciklama);

    // JSON için ayrılan belleği temizle
    free(json);

    return 0;
}
