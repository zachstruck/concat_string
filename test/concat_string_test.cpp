#include <zpp/concat_string.hpp>

#include <catch2/catch.hpp>

#include <initializer_list>
#include <string>

#if ZPP_TARGET_COMPILER(CLANG)
#  if __clang_major__ >= 4 && __cplusplus >= 201703L
#    define ZPP_CXX17_PRIV_DEF_STRING_VIEW() 1
#  else
#    define ZPP_CXX17_PRIV_DEF_STRING_VIEW() 0
#  endif
#elif ZPP_TARGET_COMPILER(GCC)
#  if __GNUC__ >= 7 && __cplusplus >= 201703L
#    define ZPP_CXX17_PRIV_DEF_STRING_VIEW() 1
#  else
#    define ZPP_CXX17_PRIV_DEF_STRING_VIEW() 0
#  endif
#elif ZPP_TARGET_COMPILER(MSVC)
#  if _MSC_VER >= 1910 && _MSVC_LANG >= 201703L
#    define ZPP_CXX17_PRIV_DEF_STRING_VIEW() 1
#  else
#    define ZPP_CXX17_PRIV_DEF_STRING_VIEW() 0
#  endif
#elif ZPP_TARGET_COMPILER(UNKNOWN)
#  define ZPP_STRING_VIEW() 0
#endif

#if ZPP_CXX17(STRING_VIEW)
#include <string_view>
#endif

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

#if ZPP_TARGET_COMPILER(CLANG)
#  if __cplusplus >= 201703L
#    define ZPP_CXX17_PRIV_DEF_CONSTEXPR_CHAR_TRAITS_LENGTH() 1
#  else
#    define ZPP_CXX17_PRIV_DEF_CONSTEXPR_CHAR_TRAITS_LENGTH() 0
#  endif
#elif ZPP_TARGET_COMPILER(GCC)
#  if __cplusplus >= 201703L
#    define ZPP_CXX17_PRIV_DEF_CONSTEXPR_CHAR_TRAITS_LENGTH() 1
#  else
#    define ZPP_CXX17_PRIV_DEF_CONSTEXPR_CHAR_TRAITS_LENGTH() 0
#  endif
#elif ZPP_TARGET_COMPILER(MSVC)
#  if _MSC_VER >= 1900 && _MSVC_LANG >= 201703L
#    define ZPP_CXX17_PRIV_DEF_CONSTEXPR_CHAR_TRAITS_LENGTH() 1
#  else
#    define ZPP_CXX17_PRIV_DEF_CONSTEXPR_CHAR_TRAITS_LENGTH() 0
#  endif
#elif ZPP_TARGET_COMPILER(UNKNOWN)
#  define ZPP_CONSTEXPR_CHAR_TRAITS_LENGTH() 0
#endif

TEST_CASE("constexpr length")
{
    static_assert(zpp::detail::string_size_impl<char>() == 0, "");
    static_assert(zpp::detail::string_size_impl<char>('a') == 1, "");
    static_assert(zpp::detail::string_size_impl<char>('a', 'b') == 2, "");
#if ZPP_CXX17(CONSTEXPR_CHAR_TRAITS_LENGTH)
    static_assert(zpp::detail::string_size_impl<char>("hi") == 2, "");
    static_assert(zpp::detail::string_size_impl<char>("hi", "!") == 3, "");
#endif
#if ZPP_CXX17(STRING_VIEW)
    using namespace std::string_view_literals;
    static_assert(zpp::detail::string_size_impl<char>("hi"sv) == 2, "");
    static_assert(zpp::detail::string_size_impl<char>("hi"sv, "!"sv) == 3, "");
#endif
}

TEST_CASE("noexcept size")
{
    static_assert(noexcept(zpp::detail::string_size_impl<char>(std::string{})), "");
#if ZPP_CXX17(STRING_VIEW)
    static_assert(noexcept(zpp::detail::string_size_impl<char>(std::string_view{})), "");
#endif
}

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

#if ZPP_CXX17(STRING_VIEW)
TEST_CASE("mixed arguments with string_view")
{
    using namespace std::string_view_literals;
    auto const s = zpp::concat_string("Hello"sv, ' ', std::initializer_list<char>{ 'w', 'o', 'r', 'l', 'd', '!' });

    CHECK(s == "Hello world!");
}
#endif

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

#if ZPP_CXX17(CHAR8_T) && ZPP_CXX17(U8_CHAR_LIT)
TEST_CASE("concatenate long u8string with u8 literals")
{
    auto const s = zpp::concat_u8string(u8"The", u8' ', u8"quick", u8' ', u8"brown", u8' ', u8"fox", u8' ', u8"jumps", u8' ', u8"over", u8' ', u8"the", u8' ', u8"fence", u8'.');

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
