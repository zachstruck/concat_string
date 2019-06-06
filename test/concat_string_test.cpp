#include <zpp/concat_string.hpp>

#include <catch2/catch.hpp>

#include <initializer_list>
#include <string>

#define ZPP_TARGET_COMPILER(X) ZPP_TARGET_COMPILER_PRIV_DEF_##X()
#if defined(__clang__)
#  define ZPP_TARGET_COMPILER_PRIV_DEF_CLANG() 1
#  define ZPP_TARGET_COMPILER_PRIV_DEF_GCC() 0
#  define ZPP_TARGET_COMPILER_PRIV_DEF_MSVC() 0
#  define ZPP_TARGET_COMPILER_PRIV_DEF_UNKNOWN() 0
#elif defined(__GNUC__)
#  define ZPP_TARGET_COMPILER_PRIV_DEF_CLANG() 0
#  define ZPP_TARGET_COMPILER_PRIV_DEF_GCC() 1
#  define ZPP_TARGET_COMPILER_PRIV_DEF_MSVC() 0
#  define ZPP_TARGET_COMPILER_PRIV_DEF_UNKNOWN() 0
#elif defined(_MSC_VER)
#  define ZPP_TARGET_COMPILER_PRIV_DEF_CLANG() 0
#  define ZPP_TARGET_COMPILER_PRIV_DEF_GCC() 0
#  define ZPP_TARGET_COMPILER_PRIV_DEF_MSVC() 1
#  define ZPP_TARGET_COMPILER_PRIV_DEF_UNKNOWN() 0
#else
#  define ZPP_TARGET_COMPILER_PRIV_DEF_CLANG() 0
#  define ZPP_TARGET_COMPILER_PRIV_DEF_GCC() 0
#  define ZPP_TARGET_COMPILER_PRIV_DEF_MSVC() 0
#  define ZPP_TARGET_COMPILER_PRIV_DEF_UNKNOWN() 1
#endif

#define ZPP_CXX03(X) ZPP_CXX03_PRIV_DEF_##X()
#define ZPP_CXX11(X) ZPP_CXX11_PRIV_DEF_##X()
#define ZPP_CXX14(X) ZPP_CXX14_PRIV_DEF_##X()
#define ZPP_CXX17(X) ZPP_CXX17_PRIV_DEF_##X()

#if ZPP_TARGET_COMPILER(CLANG)
#  if (__clang_major__ >= 4 || __clang_major__ == 3 && __clang_minor__ >= 6) && __cplusplus >= 201703L
#    define ZPP_CXX17_PRIV_DEF_U8_CHAR_LIT() 1
#  else
#    define ZPP_CXX17_PRIV_DEF_U8_CHAR_LIT() 0
#  endif
#elif ZPP_TARGET_COMPILER(GCC)
#  if __GNUC__  >= 6 && __cplusplus >= 201703L
#    define ZPP_CXX17_PRIV_DEF_U8_CHAR_LIT() 1
#  else
#    define ZPP_CXX17_PRIV_DEF_U8_CHAR_LIT() 0
#  endif
#elif ZPP_TARGET_COMPILER(MSVC)
#  if _MSC_VER >= 1900 && _MSVC_LANG >= 201703L
#    define ZPP_CXX17_PRIV_DEF_U8_CHAR_LIT() 1
#  else
#    define ZPP_CXX17_PRIV_DEF_U8_CHAR_LIT() 0
#  endif
#elif ZPP_TARGET_COMPILER(UNKNOWN)
#  define ZPP_U8_CHAR_LIT() 0
#endif

TEST_CASE("zero arguments")
{
    auto const s = zpp::concat_string();

    CHECK(s.empty());
}

TEST_CASE("one argument string")
{
    auto const s = zpp::concat_string(std::string("Hello"));

    CHECK(s == "Hello");
}

TEST_CASE("one argument literal")
{
    auto const s = zpp::concat_string("Hello");

    CHECK(s == "Hello");
}

TEST_CASE("two argument strings")
{
    auto const s = zpp::concat_string(std::string("Hello"), std::string("!"));

    CHECK(s == "Hello!");
}

TEST_CASE("two argument literal")
{
    auto const s = zpp::concat_string("Hello", "!");

    CHECK(s == "Hello!");
}

TEST_CASE("three argument strings")
{
    auto const s = zpp::concat_string(std::string("Hello"), std::string(" "), std::string("world!"));

    CHECK(s == "Hello world!");
}

TEST_CASE("three argument literals")
{
    auto const s = zpp::concat_string("Hello", " ", "world!");

    CHECK(s == "Hello world!");
}

TEST_CASE("mixed arguments")
{
    auto const s = zpp::concat_string("Hello", std::string(" "), "world!");

    CHECK(s == "Hello world!");
}

TEST_CASE("mixed arguments with initializer_list")
{
    auto const s = zpp::concat_string("Hello", ' ', std::initializer_list<char>{ 'w', 'o', 'r', 'l', 'd', '!' });

    CHECK(s == "Hello world!");
}

TEST_CASE("concatenate long string")
{
    auto const s = zpp::concat_string("The", ' ', "quick", ' ', "brown", ' ', "fox", ' ', "jumps", ' ', "over", ' ', "the", ' ', "fence", '.');

    CHECK(s == "The quick brown fox jumps over the fence.");
}

TEST_CASE("concatenate long wstring")
{
    auto const s = zpp::concat_wstring(L"The", L' ', L"quick", L' ', L"brown", L' ', L"fox", L' ', L"jumps", L' ', L"over", L' ', L"the", L' ', L"fence", L'.');

    CHECK(s == L"The quick brown fox jumps over the fence.");
}

#if ZPP_CXX17(U8_CHAR_LIT)
TEST_CASE("concatenate long string with u8 literals")
{
    auto const s = zpp::concat_string(u8"The", u8' ', u8"quick", u8' ', u8"brown", u8' ', u8"fox", u8' ', u8"jumps", u8' ', u8"over", u8' ', u8"the", u8' ', u8"fence", u8'.');

    CHECK(s == u8"The quick brown fox jumps over the fence.");
}
#endif

TEST_CASE("concatenate long u16string")
{
    auto const s = zpp::concat_u16string(u"The", u' ', u"quick", u' ', u"brown", u' ', u"fox", u' ', u"jumps", u' ', u"over", u' ', u"the", u' ', u"fence", u'.');

    CHECK(s == u"The quick brown fox jumps over the fence.");
}

TEST_CASE("concatenate long u32string")
{
    auto const s = zpp::concat_u32string(U"The", U' ', U"quick", U' ', U"brown", U' ', U"fox", U' ', U"jumps", U' ', U"over", U' ', U"the", U' ', U"fence", U'.');

    CHECK(s == U"The quick brown fox jumps over the fence.");
}
