#pragma once
#include <string_view>
#include <algorithm>
#include <bits/localefwd.h>

namespace ffv
{
    auto caseInsensitiveEquals(std::string_view lhs, std::string_view rhs) -> bool
    {
        static constexpr auto toLower = [](char a)
        { return std::tolower(a); };

        return std::ranges::equal(lhs, rhs, {}, toLower, toLower);
    }
}
