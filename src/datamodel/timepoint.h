#pragma once

#include <type_traits>
#include <chrono>

namespace ffv
{
    using TimePoint = std::chrono::duration<double>;

    static_assert(std::is_trivial_v<TimePoint>);
    static_assert(sizeof(TimePoint) == sizeof(double));

    inline auto asDouble(TimePoint timePoint) -> double
    {
        return timePoint.count();
    }
}