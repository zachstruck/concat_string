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