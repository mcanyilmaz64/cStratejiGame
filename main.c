#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    // Dosyanın boyutunu öğrenip bellekte yer açma
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *content = malloc(length + 1);
    if (content) {
        fread(content, 1, length, file);
        content[length] = '\0';  // Sonuna null karakter ekleyelim
    }
    
    fclose(file);
    return content;
}

// JSON'dan anahtar-değer çiftlerini ayrıştıran fonksiyon
int parse_json(const char *json_str, struct KeyValuePair *pairs, int max_pairs) {
    const char *pos = json_str;
    int count = 0;

    while (*pos && count < max_pairs) {
        // Anahtarı bulmak için ilk tırnağı ara
        pos = strchr(pos, '"');
        if (!pos) break;  // Eğer tırnak yoksa çık

        const char *key_start = ++pos;  // Anahtar tırnaktan sonra başlar
        pos = strchr(pos, '"');
        if (!pos) break;
        const char *key_end = pos;

        // Anahtar uzunluğunu kopyala
        int key_length = key_end - key_start;
        strncpy(pairs[count].key, key_start, key_length);
        pairs[count].key[key_length] = '\0';  // Null sonlandırıcı ekle

        // ':' karakterini bul (anahtar-değer ayırıcı)
        pos = strchr(pos, ':');
        if (!pos) break;
        pos++;  // ':' karakterini atla

        // Değeri bulmak için ilk tırnağı ara
        while (*pos == ' ' || *pos == '"') pos++;  // Boşlukları atla
        const char *value_start = pos;

        // Değer sonunu belirlemek için virgül veya kapanış karakterini bul
        while (*pos && *pos != ',' && *pos != '}' && *pos != '"') pos++;
        const char *value_end = pos;

        // Değer uzunluğunu kopyala
        int value_length = value_end - value_start;
        strncpy(pairs[count].value, value_start, value_length);
        pairs[count].value[value_length] = '\0';  // Null sonlandırıcı ekle

        count++;
        pos++;  // Sonraki anahtar-değer çiftine geç
    }

    return count;
}

int main() {
    // JSON dosyasının yolu
    const char *filename = "1.json";  // Örnek olarak bir JSON dosyası
    char *json_content = read_file(filename);

    if (json_content == NULL) {
        printf("Dosya okunamadı: %s\n", filename);
        return 1;
    }

    // Anahtar-değer çiftlerini saklayacak alan
    struct KeyValuePair pairs[10];
    int num_pairs = parse_json(json_content, pairs, 10);

    // Bulunan anahtar-değer çiftlerini yazdırma
    for (int i = 0; i < num_pairs; i++) {
        printf("Anahtar: %s, Değer: %s\n", pairs[i].key, pairs[i].value);
    }

    free(json_content);  // Bellekteki dosya içeriğini serbest bırak

   return 0;
}
