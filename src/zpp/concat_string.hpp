#ifndef ZPP_CONCAT_STRING_HPP
#define ZPP_CONCAT_STRING_HPP

#include <cstddef>
#include <string>
#include <utility>

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

// FIXME
// Update C++ number
// after C++2a is released
#if ZPP_TARGET_COMPILER(CLANG)
#  if __clang_major__ >= 7 && __cplusplus > 201703L
#    define ZPP_CXX17_PRIV_DEF_CHAR8_T() 1
#  else
#    define ZPP_CXX17_PRIV_DEF_CHAR8_T() 0
#  endif
#elif ZPP_TARGET_COMPILER(GCC)
#  if __GNUC__  >= 7 && __cplusplus > 201703L
#    define ZPP_CXX17_PRIV_DEF_CHAR8_T() 1
#  else
#    define ZPP_CXX17_PRIV_DEF_CHAR8_T() 0
#  endif
#elif ZPP_TARGET_COMPILER(MSVC)
#  if _MSC_VER >= 1922 && _MSVC_LANG > 201703L
#    define ZPP_CXX17_PRIV_DEF_CHAR8_T() 1
#  else
#    define ZPP_CXX17_PRIV_DEF_CHAR8_T() 0
#  endif
#elif ZPP_TARGET_COMPILER(UNKNOWN)
#  define ZPP_CHAR8_T() 0
#endif

namespace zpp
{
    namespace detail
    {
        template <typename CharT>
        constexpr std::size_t string_size_impl() noexcept
        {
            return 0;
        }

        template <typename CharT>
        constexpr std::size_t string_size_impl(CharT) noexcept
        {
            return 1;
        }

        template <typename CharT, typename T>
        constexpr std::size_t string_size_impl(T const* p_str)
        {
            return std::char_traits<CharT>::length(p_str);
        }

        template <typename CharT, typename T>
        constexpr typename T::size_type string_size_impl(T const& str) noexcept(noexcept(str.size()))
        {
            return str.size();
        }

        template <typename CharT, typename T, typename... Ts>
        constexpr std::size_t string_size_impl(T const& str, Ts const&... args)
        {
            return string_size_impl<CharT>(str) + string_size_impl<CharT>(args...);
        }

        template <typename CharT, typename Traits, typename Alloc>
        void concat_string_impl(std::basic_string<CharT, Traits, Alloc> const&) noexcept
        {
        }

        template <typename CharT, typename Traits, typename Alloc, typename T, typename... Ts>
        void concat_string_impl(std::basic_string<CharT, Traits, Alloc>& base_str, T const& str, Ts const&... args);

        template <typename CharT, typename Traits, typename Alloc, typename... Ts>
        void concat_string_impl(std::basic_string<CharT, Traits, Alloc>& base_str, CharT ch, Ts const&... args)
        {
            base_str.push_back(ch);

            concat_string_impl(base_str, args...);
        }

        template <typename CharT, typename Traits, typename Alloc, typename T, typename... Ts>
        void concat_string_impl(std::basic_string<CharT, Traits, Alloc>& base_str, T const& str, Ts const&... args)
        {
            base_str.append(str);

            concat_string_impl(base_str, args...);
        }
    }

    template <typename CharT, typename Traits, typename Alloc, typename... Ts>
    std::basic_string<CharT, Traits, Alloc> concat_basic_string(Ts const&... args)
    {
        std::basic_string<CharT, Traits, Alloc> base_str;
        base_str.reserve(detail::string_size_impl<CharT>(args...));
        detail::concat_string_impl(base_str, args...);
        return base_str;
    }

    template <typename CharT, typename Traits, typename... Ts>
    std::basic_string<CharT, Traits> concat_basic_string(Ts const&... args)
    {
        return concat_basic_string<CharT, Traits, typename std::basic_string<CharT, Traits>::allocator_type>(args...);
    }

    template <typename CharT, typename... Ts>
    std::basic_string<CharT> concat_basic_string(Ts const&... args)
    {
        return concat_basic_string<CharT, typename std::basic_string<CharT>::traits_type, typename std::basic_string<CharT>::allocator_type>(args...);
    }

    template <typename... Ts>
    std::string concat_string(Ts const&... args)
    {
        return concat_basic_string<std::string::value_type>(args...);
    }

    template <typename... Ts>
    std::wstring concat_wstring(Ts const&... args)
    {
        return concat_basic_string<std::wstring::value_type>(args...);
    }

#if ZPP_CXX17(CHAR8_T)
    template <typename... Ts>
    std::u8string concat_u8string(Ts const& ... args)
    {
        return concat_basic_string<std::u8string::value_type>(args...);
    }
#endif

    template <typename... Ts>
    std::u16string concat_u16string(Ts const&... args)
    {
        return concat_basic_string<std::u16string::value_type>(args...);
    }

    template <typename... Ts>
    std::u32string concat_u32string(Ts const&... args)
    {
        return concat_basic_string<std::u32string::value_type>(args...);
    }
}

#endif
