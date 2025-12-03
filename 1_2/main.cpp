#include <iostream>
#include <string>
#include <locale>
#include "RouteCipher.h"

using namespace std;

void ShowMenu() {
    wcout << L"\n=== Шифр Маршрутной Перестановки ===" << endl;
    wcout << L"1. Зашифровать текст" << endl;
    wcout << L"2. Расшифровать текст" << endl;
    wcout << L"3. Выйти" << endl;
    wcout << L"Выберите операцию: ";
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    wcout << L"=== Система Шифрования Маршрутной Перестановки ===" << endl;
    wcout << L"Автоматически удаляются: пробелы, знаки препинания, цифры" << endl;
    
    
    try {
        int Key;
        wcout << L"\nВведите ключ (количество столбцов): ";
        wcin >> Key;
        wcin.ignore();
        
        RouteCipher Cipher(Key);
        wcout << L"Шифр инициализирован с ключом: " << Key << endl;
        
        int Choice;
        wstring Text;
        
        do {
            ShowMenu();
            wcin >> Choice;
            wcin.ignore();
            
            switch (Choice) {
                case 1: {
                    wcout << L"Введите текст для шифрования: ";
                    getline(wcin, Text);
                    
                    try {
                        wstring Encrypted = Cipher.Encrypt(Text);
                        wcout << L"Зашифрованный текст: " << Encrypted << endl;
                    } catch (const CipherError& e) {
                        wcout << L"Ошибка при шифровании: " << e.what() << endl;
                    }
                    break;
                }
                case 2: {
                    wcout << L"Введите текст для расшифрования: ";
                    getline(wcin, Text);
                    
                    try {
                        wstring Decrypted = Cipher.Decrypt(Text);
                        wcout << L"Расшифрованный текст: " << Decrypted << endl;
                    } catch (const CipherError& e) {
                        wcout << L"Ошибка при расшифровании: " << e.what() << endl;
                    }
                    break;
                }
                case 3:
                    wcout << L"Выход из программы." << endl;
                    break;
                default:
                    wcout << L"Неверный выбор. Попробуйте снова." << endl;
            }
        } while (Choice != 3);
        
    } catch (const CipherError& e) {
        wcout << L"Ошибка инициализации шифра: " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        wcout << L"Неожиданная ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
