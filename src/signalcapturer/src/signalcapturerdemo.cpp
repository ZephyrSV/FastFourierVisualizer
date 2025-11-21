#include "signalcapturerdemo.h"

#include "../../datamodel/signalcapture.h"

#include <ranges>

using namespace ffv;

namespace
{
    constexpr auto toSignalAmplitude = std::views::transform([](double v) noexcept
                                                             { return SignalAmplitude{v}; });
    constexpr auto toTimePoint = std::views::transform([](double v) noexcept
                                                       { return TimePoint{v}; });
}

auto SignalCapturerDemo::createCapture() -> std::expected<SignalCapture, std::string>
{
    static constexpr auto ampl = {0., 1., 2.5, 3., 4., 2.};
    static constexpr auto timepnts = {0., 2., 1.5, 3.5, 2., -0.5};

    return SignalCapture::create(std::vector<SignalAmplitude>{std::from_range, ampl | toSignalAmplitude},
                                 std::vector<TimePoint>{std::from_range, timepnts | toTimePoint});
}