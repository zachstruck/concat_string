#ifndef ZPP_CONCAT_STRING_HPP
#define ZPP_CONCAT_STRING_HPP

#include <cstddef>
#include <string>
#include <utility>

namespace zpp
{
    namespace detail
    {
        template <typename CharT>
        std::size_t string_size_impl()
        {
            return 0;
        }

        template <typename CharT>
        std::size_t string_size_impl(CharT)
        {
            return 1;
        }

        template <typename CharT, typename T>
        std::size_t string_size_impl(T const* p_str)
        {
            return std::char_traits<CharT>::length(p_str);
        }

        template <typename CharT, typename T>
        typename T::size_type string_size_impl(T const& str)
        {
            return str.size();
        }

        template <typename CharT, typename T, typename... Ts>
        std::size_t string_size_impl(T const& str, Ts const&... args)
        {
            return string_size_impl<CharT>(str) + string_size_impl<CharT>(args...);
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
