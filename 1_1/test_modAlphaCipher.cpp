#include <iostream>
#include <cassert>
#include <clocale>
#include "modAlphaCipher.h"

using namespace std;

// Вспомогательная функция для удаления пробелов
void removeSpaces(string& str) {
    string result;
    for (char c : str) {
        if (c != ' ') {
            result += c;
        }
    }
    str = result;
}

void testConstructor() {
    cout << "Тестирование конструктора..." << endl;
    
    // Тест 1: Корректный ключ
    try {
        modAlphaCipher cipher("ПАРОЛЬ");
        cout << "✅ Конструктор с корректным ключом работает" << endl;
    } catch (...) {
        cout << "❌ Ошибка в конструкторе с корректным ключом" << endl;
    }
    
    // Тест 2: Пустой ключ
    try {
        modAlphaCipher cipher("");
        cout << "❌ Конструктор принял пустой ключ" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ Пустой ключ отловлен: " << e.what() << endl;
    }
    
    // Тест 3: Ключ с пробелами
    try {
        modAlphaCipher cipher("   ");
        cout << "❌ Конструктор принял ключ из пробелов" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ Ключ из пробелов отловлен: " << e.what() << endl;
    }
    
    // Тест 4: Ключ с английскими буквами
    try {
        modAlphaCipher cipher("KEY");
        cout << "❌ Конструктор принял английский ключ" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ Английский ключ отловлен: " << e.what() << endl;
    }
}

void testEncryptionDecryption() {
    cout << "\nТестирование шифрования и дешифрования..." << endl;
    
    // Тест 1: Простое шифрование/дешифрование
    try {
        modAlphaCipher cipher("КЛЮЧ");
        string original = "ПРИВЕТ";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        
        if (original == decrypted) {
            cout << "✅ Простое шифрование/дешифрование работает" << endl;
        } else {
            cout << "❌ Ошибка: тексты не совпадают" << endl;
            cout << "   Оригинал: " << original << endl;
            cout << "   После дешифровки: " << decrypted << endl;
        }
    } catch (const cipher_error& e) {
        cout << "❌ Ошибка при шифровании: " << e.what() << endl;
    }
    
    // Тест 2: Текст с пробелами
    try {
        modAlphaCipher cipher("СЕКРЕТ");
        string original = "СЕКРЕТНОЕ СООБЩЕНИЕ";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        
        // Удаляем пробелы для сравнения
        string originalNoSpaces = original;
        removeSpaces(originalNoSpaces);
        
        if (originalNoSpaces == decrypted) {
            cout << "✅ Шифрование текста с пробелами работает" << endl;
        } else {
            cout << "❌ Ошибка при работе с пробелами" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "❌ Ошибка: " << e.what() << endl;
    }
    
    // Тест 3: Длинный текст
    try {
        modAlphaCipher cipher("А");
        string original = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        
        if (original == decrypted) {
            cout << "✅ Работа с полным алфавитом" << endl;
        } else {
            cout << "❌ Ошибка с полным алфавитом" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "❌ Ошибка: " << e.what() << endl;
    }
    
    // Тест 4: Текст длиннее ключа
    try {
        modAlphaCipher cipher("КОРОТКИЙ");
        string original = "ОЧЕНЬДЛИННЫЙТЕКСТДЛЯПРОВЕРКИЦИКЛИЧЕСКОГОИСПОЛЬЗОВАНИЯКЛЮЧА";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        
        if (original == decrypted) {
            cout << "✅ Циклическое использование ключа работает" << endl;
        } else {
            cout << "❌ Ошибка при циклическом использовании ключа" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "❌ Ошибка: " << e.what() << endl;
    }
}

void testEdgeCases() {
    cout << "\nТестирование граничных случаев..." << endl;
    
    // Тест 1: Пустой текст для шифрования
    try {
        modAlphaCipher cipher("КЛЮЧ");
        cipher.encrypt("");
        cout << "❌ Шифрование пустого текста не вызвало исключения" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ Пустой текст для шифрования отловлен: " << e.what() << endl;
    }
    
    // Тест 2: Пустой текст для дешифрования
    try {
        modAlphaCipher cipher("КЛЮЧ");
        cipher.decrypt("");
        cout << "❌ Дешифрование пустого текста не вызвало исключения" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ Пустой текст для дешифрования отловлен: " << e.what() << endl;
    }
    
    // Тест 3: Текст только из пробелов
    try {
        modAlphaCipher cipher("КЛЮЧ");
        cipher.encrypt("   ");
        cout << "❌ Текст из пробелов не вызвал исключения" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ Текст из пробелов отловлен: " << e.what() << endl;
    }
    
    // Тест 4: Текст с неверными символами
    try {
        modAlphaCipher cipher("КЛЮЧ");
        cipher.encrypt("Hello123");
        cout << "❌ Английский текст не вызвал исключения" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ Английский текст отловлен: " << e.what() << endl;
    }
    
    // Тест 5: Текст с русскими строчными буквами
    try {
        modAlphaCipher cipher("КЛЮЧ");
        cipher.encrypt("привет");
        cout << "❌ Текст со строчными буквами не вызвал исключения" << endl;
    } catch (const cipher_error& e) {
        cout << "✅ Текст со строчными буквами отловлен: " << e.what() << endl;
    }
}

void testSpecificCases() {
    cout << "\nТестирование конкретных случаев..." << endl;
    
    // Известный тестовый случай
    try {
        modAlphaCipher cipher("ЛЕМОН");
        string original = "АТАКА";
        string encrypted = cipher.encrypt(original);
        
        cout << "Тест 'АТАКА' с ключом 'ЛЕМОН':" << endl;
        cout << "   Оригинал: " << original << endl;
        cout << "   Зашифровано: " << encrypted << endl;
        
        // Проверяем дешифрование
        string decrypted = cipher.decrypt(encrypted);
        if (decrypted == original) {
            cout << "✅ Дешифрование работает" << endl;
        } else {
            cout << "❌ Ошибка дешифрования" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "❌ Ошибка: " << e.what() << endl;
    }
    
    // Другой тестовый случай
    try {
        modAlphaCipher cipher("А");
        string original = "Я";
        string encrypted = cipher.encrypt(original);
        string expected = "А"; // А + 0 = А, Я + 1 = А (так как алфавит зациклен)
        
        cout << "\nТест 'Я' с ключом 'А':" << endl;
        cout << "   Оригинал: " << original << endl;
        cout << "   Зашифровано: " << encrypted << endl;
        cout << "   Ожидалось: " << expected << endl;
        
        if (encrypted == expected) {
            cout << "✅ Зацикливание алфавита работает" << endl;
        } else {
            cout << "❌ Ошибка зацикливания алфавита" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "❌ Ошибка: " << e.what() << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    cout << "=== МОДУЛЬНОЕ ТЕСТИРОВАНИЕ ШИФРА ГРОНСВЕЛЬДА ===" << endl;
    
    testConstructor();
    testEncryptionDecryption();
    testEdgeCases();
    testSpecificCases();
    
    cout << "\n=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===" << endl;
    
    return 0;
}
