#ifndef ZPP_CONCAT_STRING_HPP
#define ZPP_CONCAT_STRING_HPP

#include <cstddef>
#include <string>
#include <utility>

namespace zpp
{
    namespace detail
    {
        inline std::size_t string_size_impl()
        {
            return 0;
        }

        inline std::size_t string_size_impl(char)
        {
            return 1;
        }

        inline std::size_t string_size_impl(wchar_t)
        {
            return 1;
        }

        inline std::size_t string_size_impl(char16_t)
        {
            return 1;
        }

        inline std::size_t string_size_impl(char32_t)
        {
            return 1;
        }

        template <typename CharT>
        std::size_t string_size_impl(CharT const* p_str)
        {
            return std::char_traits<CharT>::length(p_str);
        }

        template <typename T>
        typename T::size_type string_size_impl(T const& str)
        {
            return str.size();
        }

        template <typename T, typename... Ts>
        std::size_t string_size_impl(T const& str, Ts const&... args)
        {
            return string_size_impl(str) + string_size_impl(args...);
        }

        template <typename CharT, typename Traits, typename Alloc>
        void concat_string_impl(std::basic_string<CharT, Traits, Alloc> const&)
        {
        }

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

    template <typename... Ts>
    std::string concat_string(Ts const&... args)
    {
        std::string base_str;
        base_str.reserve(detail::string_size_impl(args...));
        detail::concat_string_impl(base_str, args...);
        return base_str;
    }

    template <typename... Ts>
    std::wstring concat_wstring(Ts const&... args)
    {
        std::wstring base_str;
        base_str.reserve(detail::string_size_impl(args...));
        detail::concat_string_impl(base_str, args...);
        return base_str;
    }

    template <typename... Ts>
    std::u16string concat_u16string(Ts const&... args)
    {
        std::u16string base_str;
        base_str.reserve(detail::string_size_impl(args...));
        detail::concat_string_impl(base_str, args...);
        return base_str;
    }

    template <typename... Ts>
    std::u32string concat_u32string(Ts const&... args)
    {
        std::u32string base_str;
        base_str.reserve(detail::string_size_impl(args...));
        detail::concat_string_impl(base_str, args...);
        return base_str;
    }
}

#endif
