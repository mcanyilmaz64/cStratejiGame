#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oyun.h"  


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
void parseSenaryoJSON(char* json, InsanTaraf* insanTaraf, OrkTaraf* orkTaraf) {
    // JSON içinde insan_imparatorlugu verisini bul
    char *insan_data = strstr(json, "\"insan_imparatorlugu\"");
    if (insan_data == NULL) {
        printf("İnsan İmparatorluğu verisi bulunamadı!\n");
        return;
    }

    // Kahramanlar verisini ayrıştır
    char *kahramanlar_data = strstr(insan_data, "\"kahramanlar\"");
    if (kahramanlar_data != NULL) {
        printf(" %s\n", kahramanlar_data);  // Veriyi ekrana yazdır
        sscanf(kahramanlar_data, "\"kahramanlar\": \"%[^\"]\"", insanTaraf->kahraman.bonus_turu);
    } else {
        printf("İnsan İmparatorluğu kahramanlar verisi bulunamadi.\n");
    }

    // Benzer şekilde Ork tarafı için de güncelleyelim
    char *ork_data = strstr(json, "\"ork_legi\"");
    if (ork_data == NULL) {
        printf("Ork Lejyonu verisi bulunamadı!\n");
        return;
    }

    char *ork_kahramanlar_data = strstr(ork_data, "\"kahramanlar\"");
    if (ork_kahramanlar_data != NULL) {
        printf("Ork Lejyonu Kahramanlar: %s\n", ork_kahramanlar_data);
        sscanf(ork_kahramanlar_data, "\"kahramanlar\": \"%[^\"]\"", orkTaraf->kahraman.bonus_turu);
    } else {
        printf("Ork Lejyonu kahramanlar verisi bulunamadı.\n");
    }
}




int main() {
    // Senaryo dosyasını oku
    char *json_scenario = readFile("Files/8.json");
    if (json_scenario == NULL) {
        printf("Senaryo dosyası okunamadı.\n");
        return 1;
    }

    // Taraf yapıları
    InsanTaraf insanTaraf;
    OrkTaraf orkTaraf;

    // JSON'u ayrıştır ve iki tarafın verilerini ayır
    parseSenaryoJSON(json_scenario, &insanTaraf, &orkTaraf);

    // Belleği serbest bırak
    free(json_scenario);

    return 0;
}











