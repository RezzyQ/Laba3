#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <stdexcept>

locale loc("ru_RU.UTF-8");

wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;

modAlphaCipher::modAlphaCipher(const string& skey) {
    for (unsigned i = 0; i < numAlpha.size(); i++)
        alphaNum[numAlpha[i]] = i;
    key = convert(getValidKey(skey));

    // Check for weak key
    int n = 0;
    for (auto e : key) {
        if (e == 0)
            n++;
    }
    if (2 * n > key.size())
        throw cipher_error("WeakKey");
}

string modAlphaCipher::encrypt(const string& open_text) {
    vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    return convert(work);
}

string modAlphaCipher::decrypt(const string& cipher_text) {
    vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    return convert(work);
}

inline vector<int> modAlphaCipher::convert(const string& s) {
    wstring ws = codec.from_bytes(s);
    vector<int> result;
    for(auto c:ws)
        result.push_back(alphaNum[c]);
    return result;
}

inline string modAlphaCipher::convert(const vector<int>& v) {
    string result;
    wstring ws;
    for(auto i:v)
        ws.push_back(numAlpha[i]);
    result = codec.to_bytes(ws);
    return result;
}

inline string modAlphaCipher::getValidKey(const string & s) {
    wstring ws = codec.from_bytes(s);
    string mp;
    wstring tmp = codec.from_bytes(mp);
    tmp = ws;
    if (tmp.empty())
        throw cipher_error("Пустой ключ");
    int razmer = tmp.size();
    for (int i = 0; i < razmer; i++) {
        if(tmp[i] < L'А' || tmp[i] > L'я')
            throw cipher_error(string ("Неверный ключ: ") + s);
        if (tmp[i] >= L'а' && tmp[i] <= L'я')
            tmp[i] -= 32;
    }
    mp = codec.to_bytes(tmp);
    return mp;
}

inline string modAlphaCipher::getValidOpenText(const string & s) {
    string mp;
    wstring tmp = codec.from_bytes(mp);
    wstring ws = codec.from_bytes(s);
    for (auto c:ws) {
        if (c >= L'А' && c <= L'я') {
            if (c >= L'а' && c <= L'я')
                tmp.push_back(c -= 32);
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Отсутствует открытый текст!"); 
    mp = codec.to_bytes(tmp);
    return mp;
}

inline string modAlphaCipher::getValidCipherText(const string & s) {
    string mp;
    wstring tmp = codec.from_bytes(mp);
    wstring ws = codec.from_bytes(s);
    tmp = ws;
    if (tmp.empty())
        throw cipher_error("Empty cipher text");
    for (auto c:tmp) {
        if ((c < L'А' || c > L'Я') && c != L'Ё')
            throw cipher_error(string("Неправильный зашифрованный текст ")+s);
    }
    mp = codec.to_bytes(tmp);
    return mp;
}
