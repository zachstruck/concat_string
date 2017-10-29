#include <concat_string/concat_string.hpp>

#include <catch/single_include/catch.hpp>

TEST_CASE("zero arguments string")
{
    auto const s = zpp::concat_string();

    CHECK(s.empty());
}
