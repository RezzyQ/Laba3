#include <iostream>
#include <string>
#include <locale>
#include <vector>
#include "RouteCipher.h"

using namespace std;

struct TestCase {
    int testNumber;
    wstring description;
    int key;
    wstring input;
    wstring expected;
    bool shouldThrow;
};

void RunComprehensiveTests() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    wcout << L"=== ПОЛНОЕ ТЕСТИРОВАНИЕ ШИФРА МАРШРУТНОЙ ПЕРЕСТАНОВКИ ===" << endl;
    
    vector<TestCase> constructorTests = {
        {11, L"Верный ключ", 3, L"ПРИВЕТ МИР", L"Нет исключения", false},
        {12, L"Ключ длиннее сообщения", 10, L"ПРИВЕТ", L"Нет исключения", false},
        {13, L"Ключ равен длине сообщения", 9, L"ПРИВЕТМИР", L"Нет исключения", false},
        {14, L"Отрицательный ключ", -3, L"ПРИВЕТ МИР", L"Исключение", true},
        {15, L"Нулевой ключ", 0, L"ПРИВЕТ МИР", L"Исключение", true}
    };
    
    vector<TestCase> encryptTests = {
        {21, L"Строка из прописных", 3, L"ПРИВЕТМИР", L"ИТРРЕИПВМ", false},
        {22, L"Строка из строчных", 3, L"приветмир", L"ИТРРЕИПВМ", false},
        {23, L"Тест с пробелами", 3, L"ПРИВЕТ МИР", L"ИТРРЕИПВМ", false},
        {24, L"Строка с цифрами", 3, L"ПРИВЕТ2024", L"ИТРЕЛВ", false},
        {25, L"Тест без букв", 3, L"1234", L"Исключение", true},
        {26, L"Пустая строка", 3, L"", L"Исключение", true},
        {27, L"Ключ равен 1", 1, L"ПРИВЕТМИР", L"ПРИВЕТМИР", false},
        {28, L"Тест с знаками препинания", 3, L"ПРИВЕТ,МИР", L"ИТРРЕИПВМ", false},
        {29, L"Некратный ключ", 4, L"АБВГД", L"ГВБАД", false},
        {210, L"Короткий текст", 3, L"А", L"А", false}
    };
    
    vector<TestCase> decryptTests = {
        {31, L"Строка из прописных", 3, L"ИТРРЕИПВМ", L"ПРИВЕТМИР", false},
        {32, L"Строка из строчных", 3, L"итереиПВМ", L"Исключение", true},
        {33, L"Тест с пробелами", 3, L"ИТР РЕИ ПВМ", L"Исключение", true},
        {34, L"Строка с цифрами", 3, L"ИТРРЕИПВМ2024", L"Исключение", true},
        {35, L"Тест без букв", 3, L"1234", L"Исключение", true},
        {36, L"Пустая строка", 3, L"", L"Исключение", true},
        {37, L"Ключ равен 1", 1, L"ПРИВЕТМИР", L"ПРИВЕТМИР", false},
        {38, L"Тест с знаками препинания", 3, L"ПРИВЕТМИР", L"ИТРРЕИПВМ", false},
        {39, L"Некратный ключ", 4, L"ГВБАД", L"АБВГД", false},
        {310, L"Короткая строка", 3, L"А", L"А", false}
    };
    
    int totalTests = constructorTests.size() + encryptTests.size() + decryptTests.size();
    int passedTests = 0;
    
    wcout << L"\n=== ТЕСТИРОВАНИЕ КОНСТРУКТОРА ===" << endl;
    for (const auto& test : constructorTests) {
        wcout << L"Тест " << test.testNumber << L": " << test.description << L" - ";
        
        try {
            RouteCipher cipher(test.key);
            
            if (!test.shouldThrow) {
                wcout << L"✅ УСПЕХ" << endl;
                passedTests++;
            } else {
                wcout << L"❌ ОШИБКА: ожидалось исключение" << endl;
            }
        } catch (const CipherError&) {
            if (test.shouldThrow) {
                wcout << L"✅ УСПЕХ (исключение получено)" << endl;
                passedTests++;
            } else {
                wcout << L"❌ ОШИБКА: неожиданное исключение" << endl;
            }
        } catch (...) {
            if (test.shouldThrow) {
                wcout << L"✅ УСПЕХ (исключение получено)" << endl;
                passedTests++;
            } else {
                wcout << L"❌ ОШИБКА: неизвестное исключение" << endl;
            }
        }
    }
    
    wcout << L"\n=== ТЕСТИРОВАНИЕ ШИФРОВАНИЯ ===" << endl;
    for (const auto& test : encryptTests) {
        wcout << L"Тест " << test.testNumber << L": " << test.description << L" - ";
        
        try {
            RouteCipher cipher(test.key);
            wstring result = cipher.Encrypt(test.input);
            
            if (!test.shouldThrow) {
                if (result == test.expected) {
                    wcout << L"✅ УСПЕХ: " << result << endl;
                    passedTests++;
                } else {
                    wcout << L"❌ ОШИБКА: ожидалось '" << test.expected 
                          << L"', получено '" << result << L"'" << endl;
                }
            } else {
                wcout << L"❌ ОШИБКА: ожидалось исключение, получен результат: " << result << endl;
            }
        } catch (const CipherError&) {
            if (test.shouldThrow) {
                wcout << L"✅ УСПЕХ (исключение получено)" << endl;
                passedTests++;
            } else {
                wcout << L"❌ ОШИБКА: неожиданное исключение" << endl;
            }
        } catch (...) {
            if (test.shouldThrow) {
                wcout << L"✅ УСПЕХ (исключение получено)" << endl;
                passedTests++;
            } else {
                wcout << L"❌ ОШИБКА: неизвестное исключение" << endl;
            }
        }
    }
    
    wcout << L"\n=== ТЕСТИРОВАНИЕ РАСШИФРОВАНИЯ ===" << endl;
    for (const auto& test : decryptTests) {
        wcout << L"Тест " << test.testNumber << L": " << test.description << L" - ";
        
        try {
            RouteCipher cipher(test.key);
            wstring result = cipher.Decrypt(test.input);
            
            if (!test.shouldThrow) {
                if (result == test.expected) {
                    wcout << L"✅ УСПЕХ: " << result << endl;
                    passedTests++;
                } else {
                    wcout << L"❌ ОШИБКА: ожидалось '" << test.expected 
                          << L"', получено '" << result << L"'" << endl;
                }
            } else {
                wcout << L"❌ ОШИБКА: ожидалось исключение, получен результат: " << result << endl;
            }
        } catch (const CipherError&) {
            if (test.shouldThrow) {
                wcout << L"✅ УСПЕХ (исключение получено)" << endl;
                passedTests++;
            } else {
                wcout << L"❌ ОШИБКА: неожиданное исключение" << endl;
            }
        } catch (...) {
            if (test.shouldThrow) {
                wcout << L"✅ УСПЕХ (исключение получено)" << endl;
                passedTests++;
            } else {
                wcout << L"❌ ОШИБКА: неизвестное исключение" << endl;
            }
        }
    }
    
    wcout << L"\n=== ИТОГОВЫЕ РЕЗУЛЬТАТЫ ===" << endl;
    wcout << L"Всего тестов: " << totalTests << endl;
    wcout << L"Пройдено: " << passedTests << endl;
    wcout << L"Не пройдено: " << (totalTests - passedTests) << endl;
    wcout << L"Успешность: " << (passedTests * 100.0 / totalTests) << L"%" << endl;
    
    if (passedTests == totalTests) {
        wcout << L"✅ ВСЕ " << totalTests << L" ТЕСТОВ ПРОЙДЕНЫ УСПЕШНО!" << endl;
    } else {
        wcout << L"❌ НЕКОТОРЫЕ ТЕСТЫ НЕ ПРОЙДЕНЫ" << endl;
    }
}

int main() {
    RunComprehensiveTests();
    return 0;
}
