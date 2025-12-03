#include <iostream>
#include <clocale>
#include <limits>
#include <cassert>
#include "modAlphaCipher.h"

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMenu() {
    cout << "\n=== Шифр Гронсвельда ===" << endl;
    cout << "1. Зашифровать текст" << endl;
    cout << "2. Расшифровать текст" << endl;
    cout << "3. Запустить модульные тесты" << endl;
    cout << "4. Выход" << endl;
    cout << "Выберите действие: ";
}

void encryptText() {
    string key, text;
    
    cout << "\n--- Шифрование ---" << endl;
    
    // Ввод ключа
    while (true) {
        cout << "Введите ключ (русские буквы): ";
        getline(cin, key);
        
        try {
            modAlphaCipher cipher(key);
            break;
        } catch (const cipher_error& e) {
            cout << "❌ Ошибка в ключе: " << e.what() << endl;
            cout << "Пожалуйста, введите ключ снова." << endl;
        }
    }
    
    // Ввод текста для шифрования
    while (true) {
        cout << "Введите текст для шифрования: ";
        getline(cin, text);
        
        try {
            modAlphaCipher cipher(key);
            string cipher_text = cipher.encrypt(text);
            cout << "✅ Зашифрованный текст: " << cipher_text << endl;
            break;
        } catch (const cipher_error& e) {
            cout << "❌ Ошибка в тексте: " << e.what() << endl;
            cout << "Пожалуйста, введите текст снова." << endl;
        }
    }
}

void decryptText() {
    string key, text;
    
    cout << "\n--- Дешифрование ---" << endl;
    
    // Ввод ключа
    while (true) {
        cout << "Введите ключ (русские буквы): ";
        getline(cin, key);
        
        try {
            modAlphaCipher cipher(key);
            break;
        } catch (const cipher_error& e) {
            cout << "❌ Ошибка в ключе: " << e.what() << endl;
            cout << "Пожалуйста, введите ключ снова." << endl;
        }
    }
    
    // Ввод текста для дешифрования
    while (true) {
        cout << "Введите текст для дешифрования: ";
        getline(cin, text);
        
        try {
            modAlphaCipher cipher(key);
            string decrypted_text = cipher.decrypt(text);
            cout << "✅ Расшифрованный текст: " << decrypted_text << endl;
            break;
        } catch (const cipher_error& e) {
            cout << "❌ Ошибка в тексте: " << e.what() << endl;
            cout << "Пожалуйста, введите текст снова." << endl;
        }
    }
}

// Модульные тесты
void runUnitTests() {
    cout << "\n=== МОДУЛЬНЫЕ ТЕСТЫ ===" << endl;
    int passed = 0;
    int total = 0;
    
    // Тест 1: Создание шифра с корректным ключом
    cout << "\n1. Создание шифра с корректным ключом: ";
    total++;
    try {
        modAlphaCipher cipher("ПАРОЛЬ");
        cout << "✅ PASS" << endl;
        passed++;
    } catch (...) {
        cout << "❌ FAIL" << endl;
    }
    
    // Тест 2: Создание шифра с пустым ключом
    cout << "2. Создание шифра с пустым ключом: ";
    total++;
    try {
        modAlphaCipher cipher("");
        cout << "❌ FAIL (ожидалось исключение)" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ PASS: " << e.what() << endl;
        passed++;
    }
    
    // Тест 3: Создание шифра с ключом из пробелов
    cout << "3. Создание шифра с ключом из пробелов: ";
    total++;
    try {
        modAlphaCipher cipher("   ");
        cout << "❌ FAIL (ожидалось исключение)" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ PASS: " << e.what() << endl;
        passed++;
    }
    
    // Тест 4: Шифрование простого текста
    cout << "4. Шифрование простого текста: ";
    total++;
    try {
        modAlphaCipher cipher("КЛЮЧ");
        string encrypted = cipher.encrypt("ПРИВЕТ");
        cout << "✅ PASS" << endl;
        passed++;
    } catch (const cipher_error& e) {
        cout << "❌ FAIL: " << e.what() << endl;
    }
    
    // Тест 5: Шифрование и дешифрование
    cout << "5. Шифрование и дешифрование: ";
    total++;
    try {
        modAlphaCipher cipher("СЕКРЕТ");
        string original = "КОДИРОВАНИЕ";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        
        if (original == decrypted) {
            cout << "✅ PASS" << endl;
            passed++;
        } else {
            cout << "❌ FAIL (тексты не совпадают)" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "❌ FAIL: " << e.what() << endl;
    }
    
    // Тест 6: Шифрование с пробелами
    cout << "6. Шифрование текста с пробелами: ";
    total++;
    try {
        modAlphaCipher cipher("КЛЮЧИК");
        string encrypted = cipher.encrypt("ПРИВЕТ МИР");
        cout << "✅ PASS" << endl;
        passed++;
    } catch (const cipher_error& e) {
        cout << "❌ FAIL: " << e.what() << endl;
    }
    
    // Тест 7: Шифрование пустого текста
    cout << "7. Шифрование пустого текста: ";
    total++;
    try {
        modAlphaCipher cipher("КЛЮЧ");
        cipher.encrypt("");
        cout << "❌ FAIL (ожидалось исключение)" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ PASS: " << e.what() << endl;
        passed++;
    }
    
    // Тест 8: Дешифрование пустого текста
    cout << "8. Дешифрование пустого текста: ";
    total++;
    try {
        modAlphaCipher cipher("КЛЮЧ");
        cipher.decrypt("");
        cout << "❌ FAIL (ожидалось исключение)" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ PASS: " << e.what() << endl;
        passed++;
    }
    
    // Тест 9: Работа с длинным ключом
    cout << "9. Работа с длинным ключом: ";
    total++;
    try {
        modAlphaCipher cipher("ОЧЕНЬДЛИННЫЙКЛЮЧДЛЯШИФРА");
        string original = "ТЕКСТ";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        
        if (original == decrypted) {
            cout << "✅ PASS" << endl;
            passed++;
        } else {
            cout << "❌ FAIL" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "❌ FAIL: " << e.what() << endl;
    }
    
    // Тест 10: Работа с текстом длиннее ключа
    cout << "10. Работа с текстом длиннее ключа: ";
    total++;
    try {
        modAlphaCipher cipher("АБ");
        string original = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        
        if (original == decrypted) {
            cout << "✅ PASS" << endl;
            passed++;
        } else {
            cout << "❌ FAIL" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "❌ FAIL: " << e.what() << endl;
    }
    
    // Тест 11: Проверка регистра (должны быть только заглавные русские буквы)
    cout << "11. Шифрование текста с английскими буквами: ";
    total++;
    try {
        modAlphaCipher cipher("КЛЮЧ");
        cipher.encrypt("HELLO");
        cout << "❌ FAIL (ожидалось исключение)" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ PASS: " << e.what() << endl;
        passed++;
    }
    
    // Тест 12: Проверка ключа с английскими буквами
    cout << "12. Создание шифра с английским ключом: ";
    total++;
    try {
        modAlphaCipher cipher("KEY");
        cout << "❌ FAIL (ожидалось исключение)" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ PASS: " << e.what() << endl;
        passed++;
    }
    
    // Вывод результатов
    cout << "\n=== РЕЗУЛЬТАТЫ ТЕСТИРОВАНИЯ ===" << endl;
    cout << "Пройдено тестов: " << passed << " из " << total << endl;
    cout << "Успешность: " << (passed * 100 / total) << "%" << endl;
    
    if (passed == total) {
        cout << "✅ ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!" << endl;
    } else {
        cout << "❌ НЕКОТОРЫЕ ТЕСТЫ НЕ ПРОЙДЕНЫ" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    cout << "=== Программа шифрования методом Гронсвельда ===" << endl;
    cout << "Поддерживаются только русские буквы в верхнем регистре." << endl;
    
    int choice;
    do {
        displayMenu();
        cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                encryptText();
                break;
            case 2:
                decryptText();
                break;
            case 3:
                runUnitTests();
                break;
            case 4:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "❌ Неверный выбор! Пожалуйста, выберите от 1 до 4." << endl;
        }
    } while (choice != 4);
    
    return 0;
}
