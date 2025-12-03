#include "RouteCipher.h"
#include <cwctype>
#include <algorithm>

using namespace std;

RouteCipher::RouteCipher(int Key) {
    ValidateKey(Key);
    Columns = Key;
}

void RouteCipher::ValidateKey(int Key) {
    if (Key <= 0) {
        throw CipherError("Ключ должен быть положительным числом");
    }
    if (Key > 50) {
        throw CipherError("Слишком большой ключ (максимум 50)");
    }
}

void RouteCipher::ValidateText(const wstring& Text) {
    if (Text.empty()) {
        throw CipherError("Текст не может быть пустым");
    }
    
    // Проверка на минимальную длину текста
    wstring cleaned = RemoveSpacesAndPunctuation(Text);
    if (cleaned.length() < 2) {
        throw CipherError("Текст должен содержать хотя бы 2 буквы");
    }
}

void RouteCipher::ValidateEncryptedText(const wstring& Text) {
    if (Text.empty()) {
        throw CipherError("Зашифрованный текст не может быть пустым");
    }
    
    // Проверка, что зашифрованный текст состоит только из букв
    for (wchar_t c : Text) {
        if (!iswalpha(c) && c != L'X') {
            throw CipherError("Зашифрованный текст содержит недопустимые символы");
        }
    }
}

wstring RouteCipher::RemoveSpacesAndPunctuation(const wstring& Text) {
    wstring Result;
    for (wchar_t c : Text) {
        if (!iswspace(c) && !iswpunct(c) && !iswdigit(c)) {
            Result += c;
        }
    }
    return Result;
}

wstring RouteCipher::ToUpperCase(const wstring& Text) {
    wstring Result = Text;
    for (wchar_t& c : Result) {
        c = towupper(c);
    }
    return Result;
}

wstring RouteCipher::PrepareText(const wstring& Text) {
    wstring Cleaned = RemoveSpacesAndPunctuation(Text);
    if (Cleaned.empty()) {
        throw CipherError("После удаления пробелов и знаков препинания текст пуст");
    }
    
    return ToUpperCase(Cleaned);
}

wstring RouteCipher::Encrypt(const wstring& Text) {
    ValidateText(Text);
    wstring PreparedText = PrepareText(Text);
    
    int TextLength = PreparedText.length();
    int Rows = (TextLength + Columns - 1) / Columns;
    
    // Создаем таблицу и заполняем по строкам слева направо
    vector<vector<wchar_t>> Table(Rows, vector<wchar_t>(Columns));
    
    int index = 0;
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            if (index < TextLength) {
                Table[i][j] = PreparedText[index++];
            } else {
                // Заполняем оставшиеся ячейки специальным символом
                Table[i][j] = L'X';
            }
        }
    }
    
    // Читаем по столбцам сверху вниз, справа налево
    wstring Result;
    for (int j = Columns - 1; j >= 0; j--) {
        for (int i = 0; i < Rows; i++) {
            Result += Table[i][j];
        }
    }
    
    return Result;
}

wstring RouteCipher::Decrypt(const wstring& Text) {
    ValidateText(Text);
    ValidateEncryptedText(Text);
    wstring PreparedText = PrepareText(Text);
    
    int TextLength = PreparedText.length();
    int Rows = (TextLength + Columns - 1) / Columns;
    
    // Создаем пустую таблицу
    vector<vector<wchar_t>> Table(Rows, vector<wchar_t>(Columns));
    
    // Заполняем таблицу по столбцам сверху вниз, справа налево
    int index = 0;
    for (int j = Columns - 1; j >= 0; j--) {
        for (int i = 0; i < Rows; i++) {
            if (index < TextLength) {
                Table[i][j] = PreparedText[index++];
            } else {
                Table[i][j] = L'X';
            }
        }
    }
    
    // Читаем по строкам слева направо
    wstring Result;
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            Result += Table[i][j];
        }
    }
    
    // Убираем добавленные символы 'X' в конце
    while (!Result.empty() && Result.back() == L'X') {
        Result.pop_back();
    }
    
    return Result;
}
