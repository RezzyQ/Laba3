#include "modAlphaCipher.h"
#include <stdexcept>
#include <algorithm>

std::string modAlphaCipher::removeSpaces(const std::string& s) const
{
    std::string result;
    for (char c : s) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}

void modAlphaCipher::validateKey(const std::vector<int>& key) const
{
    if (key.empty()) {
        throw cipher_error("Empty key provided");
    }
    
    for (int k : key) {
        if (k < 0 || k >= static_cast<int>(numAlpha.size() / 2)) {
            throw cipher_error("Invalid key value - out of alphabet range");
        }
    }
}

void modAlphaCipher::validateText(const std::string& text) const
{
    if (text.empty()) {
        throw cipher_error("Empty text provided");
    }
    
    if (text.length() % 2 != 0) {
        throw cipher_error("Invalid text length - must be even for UTF-8 Russian characters");
    }
}

std::vector<int> modAlphaCipher::textToIndices(const std::string& text) const
{
    validateText(text);
    
    std::vector<int> indices;
    size_t i = 0;
    while (i < text.size()) {
        if (i + 1 >= text.size()) {
            throw cipher_error("Incomplete character at the end of text");
        }
        
        std::string letter = text.substr(i, 2);

        bool found = false;
        for (size_t pos = 0; pos < numAlpha.size(); pos += 2) {
            if (numAlpha.substr(pos, 2) == letter) {
                indices.push_back(static_cast<int>(pos / 2));
                found = true;
                break;
            }
        }

        if (!found) {
            throw cipher_error("Invalid character in input: '" + letter + "' (not a Russian uppercase letter)");
        }

        i += 2;
    }

    if (indices.empty()) {
        throw cipher_error("Empty text after processing");
    }

    return indices;
}

std::string modAlphaCipher::indicesToText(const std::vector<int>& indices) const
{
    if (indices.empty()) {
        throw cipher_error("Cannot convert empty indices to text");
    }
    
    std::string result;
    for (int idx : indices) {
        if (idx < 0 || idx >= static_cast<int>(numAlpha.size() / 2)) {
            throw cipher_error("Index out of range in indicesToText: " + std::to_string(idx));
        }
        result += numAlpha.substr(idx * 2, 2);
    }
    return result;
}

modAlphaCipher::modAlphaCipher(const std::string& skey)
{
    if (skey.empty()) {
        throw cipher_error("Key cannot be empty");
    }
    
    std::string cleanKey = removeSpaces(skey);
    if (cleanKey.empty()) {
        throw cipher_error("Key contains only spaces");
    }
    
    key = textToIndices(cleanKey);
    validateKey(key);
}

std::string modAlphaCipher::encrypt(const std::string& open_text)
{
    if (open_text.empty()) {
        throw cipher_error("Cannot encrypt empty text");
    }
    
    std::string cleanText = removeSpaces(open_text);
    if (cleanText.empty()) {
        throw cipher_error("Text contains only spaces");
    }
    
    std::vector<int> work = textToIndices(cleanText);
    int alphabetSize = static_cast<int>(numAlpha.size() / 2);

    for (size_t i = 0; i < work.size(); ++i) {
        work[i] = (work[i] + key[i % key.size()]) % alphabetSize;
    }
    return indicesToText(work);
}

std::string modAlphaCipher::decrypt(const std::string& cipher_text)
{
    if (cipher_text.empty()) {
        throw cipher_error("Cannot decrypt empty text");
    }
    
    std::string cleanText = removeSpaces(cipher_text);
    if (cleanText.empty()) {
        throw cipher_error("Cipher text contains only spaces");
    }
    
    std::vector<int> work = textToIndices(cleanText);
    int alphabetSize = static_cast<int>(numAlpha.size() / 2);

    for (size_t i = 0; i < work.size(); ++i) {
        work[i] = (work[i] - key[i % key.size()] + alphabetSize) % alphabetSize;
    }
    return indicesToText(work);
}
