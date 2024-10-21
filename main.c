#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oyun.h"  // heroesParse.h başlık dosyasını dahil ediyoruz

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
void parseHero(char* json, const char* heroName, HeroBonus* heroBonus) {
    char *hero = strstr(json, heroName);
    if (hero != NULL) {
        char *bonus_turu = strstr(hero, "\"bonus_turu\"");
        if (bonus_turu != NULL) {
            sscanf(bonus_turu, "\"bonus_turu\": \"%[^\"]\"", heroBonus->bonus_turu);
        } else {
            strcpy(heroBonus->bonus_turu, "N/A");
        }

        char *bonus_degeri = strstr(hero, "\"bonus_degeri\"");
        if (bonus_degeri != NULL) {
            sscanf(bonus_degeri, "\"bonus_degeri\": \"%[^\"]\"", heroBonus->bonus_degeri);
        } else {
            strcpy(heroBonus->bonus_degeri, "0");
        }

        char *aciklama = strstr(hero, "\"aciklama\"");
        if (aciklama != NULL) {
            sscanf(aciklama, "\"aciklama\": \"%[^\"]\"", heroBonus->aciklama);
        } else {
            strcpy(heroBonus->aciklama, "Açıklama yok");
        }
    } else {
        strcpy(heroBonus->bonus_turu, "N/A");
        strcpy(heroBonus->bonus_degeri, "0");
        strcpy(heroBonus->aciklama, "Açıklama yok");
    }
}

void parseHeroesJSON(char* json, InsanImparatorluguHeroes* insanHeroes, OrkLegiHeroes* orkHeroes) {
    // İnsan İmparatorluğu liderleri
    parseHero(json, "\"Alparslan\"", &insanHeroes->Alparslan);
    parseHero(json, "\"Fatih_Sultan_Mehmet\"", &insanHeroes->Fatih_Sultan_Mehmet);
    parseHero(json, "\"Mete_Han\"", &insanHeroes->Mete_Han);
    parseHero(json, "\"Yavuz_Sultan_Selim\"", &insanHeroes->Yavuz_Sultan_Selim);
    parseHero(json, "\"Tugrul_Bey\"", &insanHeroes->Tugrul_Bey);

    // Ork Lejyonu liderleri
    parseHero(json, "\"Goruk_Vahsi\"", &orkHeroes->Goruk_Vahsi);
    parseHero(json, "\"Thruk_Kemikkiran\"", &orkHeroes->Thruk_Kemikkiran);
    parseHero(json, "\"Vrog_Kafakiran\"", &orkHeroes->Vrog_Kafakiran);
    parseHero(json, "\"Ugar_Zalim\"", &orkHeroes->Ugar_Zalim);
}
void parseCreature(char* json, const char* creatureName, CreatureEffect* creatureEffect) {
    char *creature = strstr(json, creatureName);
    if (creature != NULL) {
        char *etki_turu = strstr(creature, "\"etki_turu\"");
        if (etki_turu != NULL) {
            sscanf(etki_turu, "\"etki_turu\": \"%[^\"]\"", creatureEffect->etki_turu);
        } else {
            strcpy(creatureEffect->etki_turu, "N/A");
        }

        char *etki_degeri = strstr(creature, "\"etki_degeri\"");
        if (etki_degeri != NULL) {
            sscanf(etki_degeri, "\"etki_degeri\": \"%d\"", &creatureEffect->etki_degeri);
        } else {
            creatureEffect->etki_degeri = 0;
        }

        char *aciklama = strstr(creature, "\"aciklama\"");
        if (aciklama != NULL) {
            sscanf(aciklama, "\"aciklama\": \"%[^\"]\"", creatureEffect->aciklama);
        } else {
            strcpy(creatureEffect->aciklama, "Açıklama yok");
        }
    } else {
        strcpy(creatureEffect->etki_turu, "N/A");
        creatureEffect->etki_degeri = 0;
        strcpy(creatureEffect->aciklama, "Açıklama yok");
    }
}

void parseCreaturesJSON(char* json, InsanImparatorluguCreatures* insanCreatures, OrkLegiCreatures* orkCreatures) {
    // İnsan İmparatorluğu yaratıklarını ayrıştır
    parseCreature(json, "\"Ejderha\"", &insanCreatures->ejderha);
    parseCreature(json, "\"Agri_Dagi_Devleri\"", &insanCreatures->agri_dagi_devleri);
    parseCreature(json, "\"Tepegoz\"", &insanCreatures->tepegoz);
    parseCreature(json, "\"Karakurt\"", &insanCreatures->karakurt);
    parseCreature(json, "\"Samur\"", &insanCreatures->samur);

    // Ork Lejyonu yaratıklarını ayrıştır
    parseCreature(json, "\"Kara_Troll\"", &orkCreatures->kara_troll);
    parseCreature(json, "\"Golge_Kurtlari\"", &orkCreatures->golge_kurtlari);
    parseCreature(json, "\"Camur_Devleri\"", &orkCreatures->camur_devleri);
    parseCreature(json, "\"Ates_Iblisi\"", &orkCreatures->ates_iblisi);
    parseCreature(json, "\"Makrog_Savas_Beyi\"", &orkCreatures->makrog_savas_beyi);
    parseCreature(json, "\"Buz_Devleri\"", &orkCreatures->buz_devleri);
}
void parseUnit(char* json, const char* unitName, UnitStats* unitStats) {
    char *unit = strstr(json, unitName);
    if (unit != NULL) {
        sscanf(strstr(unit, "\"saldiri\""), "\"saldiri\": %d,", &unitStats->saldiri);
        sscanf(strstr(unit, "\"savunma\""), "\"savunma\": %d,", &unitStats->savunma);
        sscanf(strstr(unit, "\"saglik\""), "\"saglik\": %d,", &unitStats->saglik);
        sscanf(strstr(unit, "\"kritik_sans\""), "\"kritik_sans\": %d,", &unitStats->kritik_sans);
    } else {
        unitStats->saldiri = 0;
        unitStats->savunma = 0;
        unitStats->saglik = 0;
        unitStats->kritik_sans = 0;
    }
}

void parseUnitsJSON(char* json, InsanImparatorluguUnits* insanUnits, OrkLegiUnits* orkUnits) {
    // İnsan İmparatorluğu birimleri
    parseUnit(json, "\"piyadeler\"", &insanUnits->piyadeler);
    parseUnit(json, "\"okcular\"", &insanUnits->okcular);
    parseUnit(json, "\"suvariler\"", &insanUnits->suvariler);
    parseUnit(json, "\"kusatma_makineleri\"", &insanUnits->kusatma_makineleri);

    // Ork Lejyonu birimleri
    parseUnit(json, "\"ork_dovusculeri\"", &orkUnits->ork_dovusculeri);
    parseUnit(json, "\"mizrakcilar\"", &orkUnits->mizrakcilar);
    parseUnit(json, "\"varg_binicileri\"", &orkUnits->varg_binicileri);
    parseUnit(json, "\"troller\"", &orkUnits->troller);


}
void parseResearchLevel(char* json, const char* levelName, ResearchLevel* researchLevel) {
    char *level = strstr(json, levelName);
    if (level != NULL) {
        sscanf(strstr(level, "\"deger\""), "\"deger\": \"%d\",", &researchLevel->deger);
        sscanf(strstr(level, "\"aciklama\""), "\"aciklama\": \"%[^\"]\"", researchLevel->aciklama);
    } else {
        researchLevel->deger = 0;
        strcpy(researchLevel->aciklama, "Açıklama yok");
    }
}

void parseResearch(char* json, const char* researchName, Research* research) {
    char *researchData = strstr(json, researchName);
    if (researchData != NULL) {
        parseResearchLevel(researchData, "\"seviye_1\"", &research->seviye_1);
        parseResearchLevel(researchData, "\"seviye_2\"", &research->seviye_2);
        parseResearchLevel(researchData, "\"seviye_3\"", &research->seviye_3);
    }
}

void parseResearchJSON(char* json, ResearchStats* researchStats) {
    parseResearch(json, "\"savunma_ustaligi\"", &researchStats->savunma_ustaligi);
    parseResearch(json, "\"saldiri_gelistirmesi\"", &researchStats->saldiri_gelistirmesi);
    parseResearch(json, "\"elit_egitim\"", &researchStats->elit_egitim);
    parseResearch(json, "\"kusatma_ustaligi\"", &researchStats->kusatma_ustaligi);
}



int main() {
    // 1. heroes.json dosyasını oku
    char *json_heroes = readFile("Files/heroes.json");
    if (json_heroes == NULL) {
        return 1;
    }

    // Liderler için yapılar
    InsanImparatorluguHeroes insan_heroes;
    OrkLegiHeroes ork_heroes;

    // Lider verilerini ayrıştır
    parseHeroesJSON(json_heroes, &insan_heroes, &ork_heroes);
    free(json_heroes);  // heroes.json verisini temizle

    // 2. units.json dosyasını oku
    char *json_units = readFile("Files/unit_types.json");
    if (json_units == NULL) {
        return 1;
    }

    // Birimler için yapılar
    InsanImparatorluguUnits insan_units;
    OrkLegiUnits ork_units;

    // Birim verilerini ayrıştır
    parseUnitsJSON(json_units, &insan_units, &ork_units);
    free(json_units);  // units.json verisini temizle

    // 3. creatures.json dosyasını oku
    char *json_creatures = readFile("Files/creatures.json");
    if (json_creatures == NULL) {
        return 1;
    }

    // Yaratıklar için yapılar
    InsanImparatorluguCreatures insan_creatures;
    OrkLegiCreatures ork_creatures;

    // Yaratık verilerini ayrıştır
    parseCreaturesJSON(json_creatures, &insan_creatures, &ork_creatures);
    free(json_creatures);  // creatures.json verisini temizle

    // 4. research.json dosyasını oku
    char *json_research = readFile("Files/research.json");
    if (json_research == NULL) {
        return 1;
    }

    // Araştırmalar için yapılar
    ResearchStats researchStats;

    // Araştırma verilerini ayrıştır
    parseResearchJSON(json_research, &researchStats);
    free(json_research);  // research.json verisini temizle

    // 5. Verileri ekrana yazdır
    printf("Alparslan: %s, %s, %s\n", insan_heroes.Alparslan.bonus_turu,
                                      insan_heroes.Alparslan.bonus_degeri,
                                      insan_heroes.Alparslan.aciklama);

    printf("Piyadeler: Saldiri: %d, Savunma: %d, Saglik: %d, Kritik Sans: %d\n", 
           insan_units.piyadeler.saldiri, insan_units.piyadeler.savunma, 
           insan_units.piyadeler.saglik, insan_units.piyadeler.kritik_sans);

    printf("Ejderha: %s, %d, %s\n", 
           insan_creatures.ejderha.etki_turu, insan_creatures.ejderha.etki_degeri, 
           insan_creatures.ejderha.aciklama);

    // Araştırma bilgilerini ekrana yazdır
    printf("Savunma Ustaligi Seviye 1: Deger: %d, Aciklama: %s\n", 
           researchStats.savunma_ustaligi.seviye_1.deger,
           researchStats.savunma_ustaligi.seviye_1.aciklama);

    printf("Saldiri Gelistirmesi Seviye 2: Deger: %d, Aciklama: %s\n", 
           researchStats.saldiri_gelistirmesi.seviye_2.deger,
           researchStats.saldiri_gelistirmesi.seviye_2.aciklama);

    return 0;
}




