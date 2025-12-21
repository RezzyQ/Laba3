#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("ЁУСФОФЦ",modAlphaCipher("ГЕНИЙ").encrypt("ГОДЛЕСС")); 
    }
    TEST(LongKey) {
        CHECK_EQUAL("ТЯТЭЧАЭ",modAlphaCipher("ПРОСТОЛУЧШИЙ").encrypt("ГОДЛЕСС"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("ЁУСФОФЦ",modAlphaCipher("гений").encrypt("ГОДЛЕСС"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("ГЕНИЙ1"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("ГОДЛЕСС,ГЕНИЙ"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("КАК ЖЕ УМЕН"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"),cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("Б");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("НБЛТЙНБМЭОЬКВБММДПЕМЁТТФ", p->encrypt("МАКСИМАЛЬНЫЙБАЛЛГОДЛЕССУ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("НБЛТЙНБМЭОЬКВБММДПЕМЁТТФ", p->encrypt("максимальныйбаллгодлессу"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("НБЛТЙНБМЭОЬКВБММДПЕМЁТТФ", p->encrypt("МАКСИМАЛЬНЫЙ БАЛЛ ГОДЛЕССУ!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("ВБММПГДПЕМЁТТФ", p->encrypt("999 БАЛЛОВ ГОДЛЕССУ"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("2+2*2=5000?"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ЛЯЙРЗЛЯКЫМЪИАЯККВНГКДРРТ", modAlphaCipher("Я").encrypt("МАКСИМАЛЬНЫЙБАЛЛГОДЛЕССУ"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("МАКСИМАЛЬНЫЙБАЛЛГОДЛЕССУ", p->decrypt("НБЛТЙНБМЭОЬКВБММДПЕМЁТТФ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("нБЛТЙНБМЭОЬКВБММДПЕМЁТТФ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("НБЛТЙН БМЭОЬКВБММ ДПЕМЁТТФ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("11ВБММПГДПЕМЁТТФ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("НБЛТЙНБМЭОЬКВБММДПЕМЁТТФ?"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("МАКСИМАЛЬНЫЙБАЛЛГОДЛЕССУ", modAlphaCipher("Я").decrypt("ЛЯЙРЗЛЯКЫМЪИАЯККВНГКДРРТ"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
