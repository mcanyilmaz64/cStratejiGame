#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct {
    char etki_turu[20];
    int etki_degeri;
    char aciklama[256];
} CreatureEffect;

typedef struct {
    CreatureEffect ejderha;
    CreatureEffect agri_dagi_devleri;
    CreatureEffect tepegoz;
    CreatureEffect karakurt;
    CreatureEffect samur;
} InsanImparatorluguCreatures;

typedef struct {
    CreatureEffect kara_troll;
    CreatureEffect golge_kurtlari;
    CreatureEffect camur_devleri;
    CreatureEffect ates_iblisi;
    CreatureEffect makrog_savas_beyi;
    CreatureEffect buz_devleri;
} OrkLegiCreatures;

////////////////////////////////////////////////////////////////////////

typedef struct {
    char bonus_turu[20];  
    char bonus_degeri[10];    
    char aciklama[256];   
} HeroBonus;

typedef struct {
    HeroBonus Alparslan;
    HeroBonus Fatih_Sultan_Mehmet;
    HeroBonus Mete_Han;
    HeroBonus Yavuz_Sultan_Selim;
    HeroBonus Tugrul_Bey;
} InsanImparatorluguHeroes;

typedef struct {
    HeroBonus Goruk_Vahsi;
    HeroBonus Thruk_Kemikkiran;
    HeroBonus Vrog_Kafakiran;
    HeroBonus Ugar_Zalim;
} OrkLegiHeroes;

////////////////////////////////////////////////////////////////////////

typedef struct {
    int saldiri;
    int savunma;
    int saglik;
    int kritik_sans;
    int miktar;
} UnitStats;

typedef struct {
    UnitStats piyadeler;
    UnitStats okcular;
    UnitStats suvariler;
    UnitStats kusatma_makineleri;
} InsanImparatorluguUnits;

typedef struct {
    UnitStats ork_dovusculeri;
    UnitStats mizrakcilar;
    UnitStats varg_binicileri;
    UnitStats troller;
} OrkLegiUnits;

//////////////////////////////////////////////////////////////////////////

typedef struct {
    int deger;         
    char aciklama[256]; 
} ResearchLevel;

typedef struct {
    ResearchLevel seviye_1;
    ResearchLevel seviye_2;
    ResearchLevel seviye_3;
} Research;

typedef struct {
    Research savunma_ustaligi;
    Research saldiri_gelistirmesi;
    Research elit_egitim;
    Research kusatma_ustaligi;
} ResearchStats;

typedef struct {
    HeroBonus kahraman;
    InsanImparatorluguUnits birimler;
    CreatureEffect canavar;
    ResearchStats arastirma;
} InsanTaraf;

typedef struct {
    HeroBonus kahraman;
    OrkLegiUnits birimler;
    CreatureEffect canavar;
    ResearchStats arastirma;
} OrkTaraf;

//////////////////////////////////////////////////////////////////////////

// Ana yapılar
/*typedef struct {
    InsanImparatorluguHeroes insan_imparatorlugu;
    OrkLegiHeroes ork_legi;
    InsanImparatorluguCreatures insan_imparatorlugu_c;
    OrkLegiCreatures ork_legi_c;
    
} Imparatorluk;*/

char* readFile(const char* filename);
void parseHero(char* json, const char* heroName, HeroBonus* heroBonus);
void parseHeroesJSON(char* json, InsanImparatorluguHeroes* insanHeroes, OrkLegiHeroes* orkHeroes);
void parseCreature(char* json, const char* creatureName, CreatureEffect* creatureEffect);
void parseCreaturesJSON(char* json, InsanImparatorluguCreatures* insanCreatures, OrkLegiCreatures* orkCreatures);
void parseUnit(char* json, const char* unitName, UnitStats* unitStats);
void parseUnitsJSON(char* json, InsanImparatorluguUnits* insanUnits, OrkLegiUnits* orkUnits);
void parseResearchLevel(char* json, const char* levelName, ResearchLevel* researchLevel);
void parseResearch(char* json, const char* researchName, Research* research);
void parseResearchJSON(char* json, ResearchStats* researchStats);
void parseSenaryoJSON(char* json, InsanTaraf* insanTaraf, OrkTaraf* orkTaraf);



#endif 