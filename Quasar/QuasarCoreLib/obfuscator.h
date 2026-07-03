#pragma once
#include <string>

// Генерируем случайный ключ на этапе компиляции
#define OBF_KEY 0x54DA1251423A

// Макрос для обфускации символов
template <int N>
struct ObfuscatedString {
    char data[N];

    constexpr ObfuscatedString(const char(&str)[N]) : data{} {
        for (int i = 0; i < N; i++) {
            data[i] = str[i] ^ OBF_KEY;
        }
    }
};

// Функция расшифровки во время выполнения (runtime)
inline std::string Decrypt(const char* data, int size) {
    std::string str;
    for (int i = 0; i < size; i++) {
        str += (char)(data[i] ^ OBF_KEY);
    }
    return str;
}

// Макрос для удобного использования: OBF("твоя строка")
#define OBF(str) Decrypt(ObfuscatedString<sizeof(str)>(str).data, sizeof(str))