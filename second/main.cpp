#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include "Cipher.h"
#include <locale>
#include <codecvt>


using namespace std;
string wst (int k, wstring s1)
{
    Cipher w(k);
    wstring s=w.Coder(w, s1);
    const string s2 (s.begin(), s.end() );
    return s2;
}
string wst1 (int k, wstring s1)
{
    Cipher w(k);
    wstring s=w.Decoder(k, s1);
    const string s2 (s.begin(), s.end() );
    return s2;
}
    wstring test = L"HELLOPARNIDAROVA";
    int k;
    SUITE (ERRORS)
{
    TEST(EmptyKey) {
        CHECK_THROW(wst(k=0,test), cipher_error);
    }
    TEST(NegativeKey) {
        CHECK_THROW(wst(k=-5,test), cipher_error);
    }
    TEST(LargeKey) {
        CHECK_THROW(wst(k=55,test), cipher_error);
    }
    TEST(EmptyText) {
        CHECK_THROW(wst(8,L" "),cipher_error);
    }
    TEST(ValiDTextWithoutletters) {
        CHECK_THROW(wst(8,L"/,.123"),cipher_error);
    }
    TEST(EmptyTEXT) {
        CHECK_THROW(wst1(8,L" "),cipher_error);
    }
}
SUITE (PROVERKI)
{
    TEST(ValidText) {
        CHECK_EQUAL(wst(8,L"HELLOPARNIDAROVA"),"HNEILDLAORPOAVRA");
    }
    TEST(LowText) {
        CHECK_EQUAL(wst(8,L"HELLOparniDAROVA"),"HNEILDLAORPOAVRA");
    }
    TEST(SpaceText) {
        CHECK_EQUAL(wst(8,L"HELLO PARNI DAROVA"),"HNEILDLAORPOAVRA");
    }
    TEST(TextWithNumber) {
        CHECK_EQUAL(wst(8,L"HELLOPARNID123123AROVA"),"HNEILDLAORPOAVRA");
    }
    TEST(ValidTEXTo) {
        CHECK_EQUAL(wst1(8,L"HNEILDLAORPOAVRA"),"HELLOPARNIDAROVA");
    }
    TEST(LowTEXTo) {
        CHECK_EQUAL(wst1(8,L"HNEILDlaorPOAVRA"),"HELLOPARNIDAROVA");
    }
    TEST(SpaceTEXTo) {
        CHECK_EQUAL(wst1(8,L"HNEILDL AORPOAVRA"),"HELLOPARNIDAROVA");
    }
    TEST(TextNumberTexto) {
        CHECK_EQUAL(wst1(8,L"HNEILDLA123ORPOAVRA"),"HELLOPARNIDAROVA");
    }
    TEST(TextSymbolTexto) {
        CHECK_EQUAL(wst1(8,L"HNEILDLAOR..POAVRA"),"HELLOPARNIDAROVA");
    }
}
int main(int argc, char **argv)
{ 
    return UnitTest::RunAllTests();
}
