# concat_str

[![CircleCI](https://circleci.com/gh/zachstruck/concat_string.svg?style=svg)](https://circleci.com/gh/zachstruck/concat_string)
[![Build status](https://ci.appveyor.com/api/projects/status/6peqx48ggt636wj7?svg=true)](https://ci.appveyor.com/project/zachstruck/concat-string)

`concat_str` is a utility function for concatenating multiple string types while minimizing potential free store allocations.

## Illustration of the problem

Potentially multiple reallocations:

```c++
using namespace std::string_literals;
// Pretend this is concatenating dynamic strings from functions
auto const s = "Hello world!"s + ' ' + "This is C++."s + ' ' + "Here is a string.";
```

Instead use a function that will calculate the total length and reserve the string memory once:

```c++
// Pretend this is concatenating dynamic strings from functions
auto const s = zpp::concat_string("Hello world!", ' ', "This is C++.", ' ', "Here is a string.");
```

## API

Main convenience functions:

* `std::string concat_string(...)`
* `std::wstring concat_wstring(...)`
* `std::u8string concat_u8string(...)` (requires C++20)
* `std::u16string concat_u16string(...)`
* `std::u32string concat_u32string(...)`

Generic template function:

* ```c++
  template <typename CharT, typename Traits, typename Alloc, typename... Ts>
  std::basic_string<CharT, Traits, Alloc> concat_basic_string(...)
  ```

## Supported types

Requires that the underlying character types are all the same.  I.e., no mixing `char` and `wchar_t`.

* Single character
  * `char`
  * `wchar_t`
  * `char8_t` (requires C++20)
  * `char16_t`
  * `char32_t`
* String literal
  * `""`
  * `L""`
  * `u8""`
  * `u""`
  * `U""`
* `std::basic_string<...>`
  * `std::string`
  * `std::wstring`
  * `std::u8string` (requires C++20)
  * `std::u16string`
  * `std::u32string`
* `std::basic_string_view<...>` (requires C++17)
  * `std::string_view` (requires C++17)
  * `std::wstring_view` (requires C++17)
  * `std::u8string_view` (requires C++20)
  * `std::u16string_view` (requires C++17)
  * `std::u32string_view` (requires C++17)
* `std::initializer_list<CharT>`

## Requirements

C++11 with variadic template support
