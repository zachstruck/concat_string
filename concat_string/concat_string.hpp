#ifndef ZPP_CONCAT_STRING_HPP
#define ZPP_CONCAT_STRING_HPP

#include <string>
#include <utility>

namespace zpp
{
    namespace detail
    {
        inline void concat_string_impl(std::string&)
        {
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
        detail::concat_string_impl(base_str, args...);
        return base_str;
    }
}

#endif
