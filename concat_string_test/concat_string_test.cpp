#include <concat_string/concat_string.hpp>

#include <catch/single_include/catch.hpp>

#include <initializer_list>
#include <string>

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

TEST_CASE("concatenate long string with u8 literals")
{
    auto const s = zpp::concat_string(u8"The", u8' ', u8"quick", u8' ', u8"brown", u8' ', u8"fox", u8' ', u8"jumps", u8' ', u8"over", u8' ', u8"the", u8' ', u8"fence", u8'.');

    CHECK(s == u8"The quick brown fox jumps over the fence.");
}

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
