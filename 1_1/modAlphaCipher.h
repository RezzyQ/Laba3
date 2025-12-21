#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;

class modAlphaCipher {
    private:
        wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        map <char,int> alphaNum;
        vector <int> key;
        vector<int> convert(const string& s);
        string convert(const vector<int>& v);
        string getValidKey(const string & s);
        string getValidOpenText(const string & s);
        string getValidCipherText(const string & s);
    public:
        modAlphaCipher()=delete;
        modAlphaCipher(const string& skey);
        string encrypt(const string& open_text);
        string decrypt(const string& cipher_text);
};

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};
