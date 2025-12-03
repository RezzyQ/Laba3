#include <iostream>
#include <string>
#include <locale>
#include "RouteCipher.h"

using namespace std;

void RunQuickTests() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    wcout << L"=== БЫСТРЫЕ ТЕСТЫ ШИФРА МАРШРУТНОЙ ПЕРЕСТАНОВКИ ===" << endl;
    
    int passed = 0;
    int total = 0;
    
    // Тест 1: Конструктор с валидным ключом
    total++;
    try {
        RouteCipher cipher(4);
        wcout << L"✅ Тест 1: Конструктор работает" << endl;
        passed++;
    } catch (...) {
        wcout << L"❌ Тест 1: Конструктор не работает" << endl;
    }
    
    // Тест 2: Конструктор с невалидным ключом
    total++;
    try {
        RouteCipher cipher(0);
        wcout << L"❌ Тест 2: Конструктор принял ключ 0" << endl;
    } catch (const CipherError&) {
        wcout << L"✅ Тест 2: Конструктор отклонил ключ 0" << endl;
        passed++;
    }
    
    // Тест 3: Шифрование простого текста
    total++;
    try {
        RouteCipher cipher(3);
        wstring encrypted = cipher.Encrypt(L"ПРИВЕТ");
        wcout << L"✅ Тест 3: Шифрование работает" << endl;
        passed++;
    } catch (const CipherError& e) {
        wcout << L"❌ Тест 3: " << e.what() << endl;
    }
    
    // Тест 4: Шифрование и расшифрование
    total++;
    try {
        RouteCipher cipher(5);
        wstring original = L"ТЕСТ";
        wstring encrypted = cipher.Encrypt(original);
        wstring decrypted = cipher.Decrypt(encrypted);
        
        if (original == decrypted) {
            wcout << L"✅ Тест 4: Шифрование/расшифрование работает" << endl;
            passed++;
        } else {
            wcout << L"❌ Тест 4: Тексты не совпадают" << endl;
        }
    } catch (const CipherError& e) {
        wcout << L"❌ Тест 4: " << e.what() << endl;
    }
    
    // Вывод результатов
    wcout << L"\n=== РЕЗУЛЬТАТЫ ===" << endl;
    wcout << L"Пройдено тестов: " << passed << L" из " << total << endl;
    wcout << L"Успешность: " << (passed * 100 / total) << L"%" << endl;
    
    if (passed == total) {
        wcout << L"✅ ВСЕ ТЕСТЫ ПРОЙДЕНЫ!" << endl;
    } else {
        wcout << L"❌ НЕКОТОРЫЕ ТЕСТЫ НЕ ПРОЙДЕНЫ" << endl;
    }
}

int main() {
    RunQuickTests();
    return 0;
}
