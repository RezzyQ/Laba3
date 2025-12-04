// RouteCipher.h
#ifndef ROUTECIPHER_H
#define ROUTECIPHER_H

#include <string>
#include <stdexcept>
#include <locale>
#include <vector>
#include <codecvt>

class CipherError : public std::invalid_argument {
public:
    explicit CipherError(const std::string& what_arg) 
        : std::invalid_argument(what_arg) {}
};

class RouteCipher {
private:
    int key;
    
    // Преобразование строки: удаление не-букв, преобразование в верхний регистр
    std::wstring prepareText(const std::wstring& text) const {
        std::wstring result;
        std::locale loc("ru_RU.UTF-8");
        
        for (wchar_t c : text) {
            if (std::isalpha(c, loc)) {
                result += std::toupper(c, loc);
            }
        }
        
        return result;
    }
    
    // Проверка текста для расшифрования
    void validateCipherText(const std::wstring& text) const {
        if (text.empty()) {
            throw CipherError("Текст не может быть пустым");
        }
        
        std::locale loc("ru_RU.UTF-8");
        for (wchar_t c : text) {
            if (!std::isalpha(c, loc)) {
                throw CipherError("Шифртекст должен содержать только буквы");
            }
        }
    }

public:
    RouteCipher(int k) {
        if (k <= 0) {
            throw CipherError("Ключ должен быть положительным числом");
        }
        key = k;
    }
    
    std::wstring Encrypt(const std::wstring& text) {
        std::wstring prepared = prepareText(text);
        if (prepared.empty()) {
            throw CipherError("Текст не содержит букв");
        }
        
        int len = prepared.length();
        int rows = (len + key - 1) / key;
        
        // Создаем таблицу
        std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(key, ' '));
        
        // Заполняем таблицу по строкам
        int idx = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < key; j++) {
                if (idx < len) {
                    table[i][j] = prepared[idx++];
                }
            }
        }
        
        // Читаем по столбцам
        std::wstring result;
        for (int j = 0; j < key; j++) {
            for (int i = 0; i < rows; i++) {
                if (table[i][j] != ' ') {
                    result += table[i][j];
                }
            }
        }
        
        return result;
    }
    
    std::wstring Decrypt(const std::wstring& text) {
        validateCipherText(text);
        
        int len = text.length();
        int rows = (len + key - 1) / key;
        
        // Создаем таблицу
        std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(key, ' '));
        
        // Заполняем таблицу по столбцам
        int idx = 0;
        for (int j = 0; j < key; j++) {
            for (int i = 0; i < rows; i++) {
                if (idx < len) {
                    table[i][j] = text[idx++];
                }
            }
        }
        
        // Читаем таблицу по строкам
        std::wstring result;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < key; j++) {
                if (table[i][j] != ' ') {
                    result += table[i][j];
                }
            }
        }
        
        return result;
    }
};

#endif
