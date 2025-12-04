#include <iostream>
#include <string>
#include <locale>
#include "RouteCipher.h"

using namespace std;

void DebugTests() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    wcout << L"=== ОТЛАДОЧНЫЕ ТЕСТЫ ===" << endl << endl;
    
    // Тест 1: Проверка конструктора
    wcout << L"1. Тестирование конструктора:" << endl;
    try {
        RouteCipher c1(3);
        wcout << L"   ✅ Конструктор с ключом 3 работает" << endl;
    } catch(...) {
        wcout << L"   ❌ Конструктор с ключом 3 не работает" << endl;
    }
    
    try {
        RouteCipher c2(0);
        wcout << L"   ❌ Конструктор с ключом 0 не должен работать" << endl;
    } catch(...) {
        wcout << L"   ✅ Конструктор с ключом 0 выбросил исключение" << endl;
    }
    
    // Тест 2: Простое шифрование
    wcout << endl << L"2. Простое шифрование:" << endl;
    try {
        RouteCipher cipher(3);
        wstring original = L"АБВГД";
        wstring encrypted = cipher.Encrypt(original);
        wstring decrypted = cipher.Decrypt(encrypted);
        
        wcout << L"   Исходный текст: " << original << endl;
        wcout << L"   Зашифрованный: " << encrypted << endl;
        wcout << L"   Расшифрованный: " << decrypted << endl;
        
        if (original == decrypted) {
            wcout << L"   ✅ Шифрование/расшифрование работает" << endl;
        } else {
            wcout << L"   ❌ Тексты не совпадают" << endl;
        }
    } catch(const CipherError& e) {
        wcout << L"   ❌ Исключение: " << e.what() << endl;
    }
    
    // Тест 3: Проблемный тест 2.9
    wcout << endl << L"3. Тест 2.9 (АБВГД с ключом 4):" << endl;
    try {
        RouteCipher cipher(4);
        wstring original = L"АБВГД";
        wstring encrypted = cipher.Encrypt(original);
        
        wcout << L"   Исходный: " << original << endl;
        wcout << L"   Получено: " << encrypted << endl;
        wcout << L"   Ожидается: ГВБАД" << endl;
        
        // Проверим также расшифрование
        wstring decrypted = cipher.Decrypt(encrypted);
        wcout << L"   Расшифровано: " << decrypted << endl;
        
        if (decrypted == original) {
            wcout << L"   ✅ Расшифрование корректное" << endl;
        }
    } catch(const CipherError& e) {
        wcout << L"   ❌ Исключение: " << e.what() << endl;
    }
    
    // Тест 4: Проверка обработки строчных букв
    wcout << endl << L"4. Проверка строчных букв:" << endl;
    try {
        RouteCipher cipher(3);
        wstring encrypted = cipher.Encrypt(L"привет");
        wcout << L"   'привет' -> '" << encrypted << L"'" << endl;
        
        // Попробуем расшифровать строчные
        try {
            wstring decrypted = cipher.Decrypt(L"итереи");
            wcout << L"   Расшифровано строчными: " << decrypted << endl;
        } catch(...) {
            wcout << L"   ✅ Исключение при расшифровании строчных (как и ожидалось)" << endl;
        }
    } catch(...) {
        wcout << L"   ❌ Исключение при шифровании строчных" << endl;
    }
    
    // Тест 5: Проверка удаления не-букв
    wcout << endl << L"5. Проверка удаления не-букв:" << endl;
    try {
        RouteCipher cipher(3);
        wstring encrypted1 = cipher.Encrypt(L"ПРИВЕТ МИР");
        wstring encrypted2 = cipher.Encrypt(L"ПРИВЕТМИР");
        
        wcout << L"   'ПРИВЕТ МИР' -> '" << encrypted1 << L"'" << endl;
        wcout << L"   'ПРИВЕТМИР'  -> '" << encrypted2 << L"'" << endl;
        
        if (encrypted1 == encrypted2) {
            wcout << L"   ✅ Пробелы корректно удаляются" << endl;
        } else {
            wcout << L"   ❌ Пробелы обрабатываются некорректно" << endl;
        }
    } catch(...) {
        wcout << L"   ❌ Исключение" << endl;
    }
}

int main() {
    DebugTests();
    return 0;
}
