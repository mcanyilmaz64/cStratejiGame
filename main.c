#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oyun.h"

// Basit bir anahtar-değer çifti yapısı
struct KeyValuePair {
    char key[256];
    char value[256];
};

// JSON dosyasını okuyan fonksiyon
char* read_file(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya açılamadı: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *content = malloc(length + 1);
    if (content) {
        fread(content, 1, length, file);
        content[length] = '\0';  // Null sonlandırıcı ekle
    }
    
    fclose(file);
    return content;
}

// JSON'dan anahtar-değer çiftlerini ayrıştıran fonksiyon
void parse_json(const char *json_str) {
    const char *pos = json_str;

    while (*pos) {
        // Anahtarı bulmak için ilk tırnağı ara
        pos = strchr(pos, '"');
        if (!pos) break;

        const char *key_start = ++pos;  // Anahtar tırnaktan sonra başlar
        pos = strchr(pos, '"');
        if (!pos) break;
        const char *key_end = pos;

        // Anahtar uzunluğunu al
        int key_length = key_end - key_start;
        char key[256];
        strncpy(key, key_start, key_length);
        key[key_length] = '\0';  // Null sonlandırıcı ekle

        // ':' karakterini bul (anahtar-değer ayırıcı)
        pos = strchr(pos, ':');
        if (!pos) break;
        pos++;  // ':' karakterini atla

        // Değeri bulmak için ilk tırnağı ara
        while (*pos == ' ' || *pos == '"') pos++;  // Boşlukları ve tırnakları atla
        const char *value_start = pos;

        // Değer sonunu bul
        while (*pos && *pos != ',' && *pos != '}' && *pos != '"') pos++;
        const char *value_end = pos;

        // Değer uzunluğunu al
        int value_length = value_end - value_start;
        char value[256];
        strncpy(value, value_start, value_length);
        value[value_length] = '\0';  // Null sonlandırıcı ekle

        // Anahtar ve değeri yazdır
        printf("Anahtar: %s, Değer: %s\n", key, value);

        pos++;  // Sonraki anahtar-değer çiftine geç
    }
}

int main() {
    //örnek kullanım. #include "oyun.h" unutulmamalı
    OyunDurumu oyun;
    oyun.insan_imparatorlugu.birimler.piyadeler = 1;

    const char *filename = "Files\\1.json";  // JSON dosyasının adı
    char *json_content = read_file(filename);

    if (json_content == NULL) {
        printf("Dosya okunamadı: %s\n", filename);
        return 1;
    }

    // JSON dosyasını ayrıştır
    parse_json(json_content);

    // Belleği serbest bırak
    free(json_content);

    return 0;
}
