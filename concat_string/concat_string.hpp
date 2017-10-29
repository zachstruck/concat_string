#ifndef ZPP_CONCAT_STRING_HPP
#define ZPP_CONCAT_STRING_HPP

#include <cstddef>
#include <cstring>
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

        inline std::size_t string_size_impl(char const* p_str)
        {
            return std::strlen(p_str);
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

        inline void concat_string_impl(std::string const&)
        {
        }

        template <typename... Ts>
        void concat_string_impl(std::string& base_str, char ch, Ts const&... args)
        {
            base_str.push_back(ch);

            concat_string_impl(base_str, args...);
        }

        template <typename T, typename... Ts>
        void concat_string_impl(std::string& base_str, T const& str, Ts const&... args)
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
}

#endif
