#ifndef READHEROES_H
#define READHEROES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oyun.h"


// Dosya okuma fonksiyonu
char* readFile(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya açılamadı: %s\n", filename);
        return NULL;
    }

    // Dosya boyutunu al
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // Dosya boyutuna göre bir buffer oluştur
    char *buffer = (char*)malloc((fileSize + 1) * sizeof(char));
    if (buffer == NULL) {
        printf("Bellek ayrımı başarısız.\n");
        fclose(file);
        return NULL;
    }

    // Dosyayı buffer'a oku
    fread(buffer, sizeof(char), fileSize, file);
    buffer[fileSize] = '\0'; // Null ile sonlandır

    fclose(file);
    return buffer;
}

// Liderlerin bilgilerini ayrıştıran fonksiyon
void parseLeader(char* json, const char* leaderName, HeroBonus* leaderBonus) {
    char *leader = strstr(json, leaderName);
    if (leader != NULL) {
        char *bonus_turu = strstr(leader, "\"bonus_turu\"");
        if (bonus_turu != NULL) {
            sscanf(bonus_turu, "\"bonus_turu\": \"%[^\"]\"", leaderBonus->bonus_turu);
        } else {
            strcpy(leaderBonus->bonus_turu, "N/A");
        }

        char *bonus_degeri = strstr(leader, "\"bonus_degeri\"");
        if (bonus_degeri != NULL) {
            sscanf(bonus_degeri, "\"bonus_degeri\": \"%[^\"]\"", leaderBonus->bonus_degeri);
        } else {
            strcpy(leaderBonus->bonus_degeri, "0");
        }

        char *aciklama = strstr(leader, "\"aciklama\"");
        if (aciklama != NULL) {
            sscanf(aciklama, "\"aciklama\": \"%[^\"]\"", leaderBonus->aciklama);
        } else {
            strcpy(leaderBonus->aciklama, "Açıklama yok");
        }
    } else {
        strcpy(leaderBonus->bonus_turu, "N/A");
        strcpy(leaderBonus->bonus_degeri, "0");
        strcpy(leaderBonus->aciklama, "Açıklama yok");
    }
}

// Ana JSON ayrıştırma fonksiyonu
void parseJSON(char* json, Imparatorluk* imparatorluk) {
    parseLeader(json, "\"Alparslan\"", &imparatorluk->insan_imparatorlugu.Alparslan);
    parseLeader(json, "\"Fatih_Sultan_Mehmet\"", &imparatorluk->insan_imparatorlugu.Fatih_Sultan_Mehmet);
    parseLeader(json, "\"Mete_Han\"", &imparatorluk->insan_imparatorlugu.Mete_Han);
    parseLeader(json, "\"Yavuz_Sultan_Selim\"", &imparatorluk->insan_imparatorlugu.Yavuz_Sultan_Selim);
    parseLeader(json, "\"Tugrul_Bey\"", &imparatorluk->insan_imparatorlugu.Tugrul_Bey);
    
    parseLeader(json, "\"Goruk_Vahsi\"", &imparatorluk->ork_legi.Goruk_Vahsi);
    parseLeader(json, "\"Thruk_Kemikkiran\"", &imparatorluk->ork_legi.Thruk_Kemikkiran);
    parseLeader(json, "\"Vrog_Kafakiran\"", &imparatorluk->ork_legi.Vrog_Kafakiran);
    parseLeader(json, "\"Ugar_Zalim\"", &imparatorluk->ork_legi.Ugar_Zalim);
}
#endif