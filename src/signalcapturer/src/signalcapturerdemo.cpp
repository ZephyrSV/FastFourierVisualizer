#include "signalcapturerdemo.h"

#include "../../datamodel/signalcapture.h"

#include <ranges>
#include <algorithm>
#include <cmath>

using namespace ffv;

namespace
{
    constexpr auto DEMO_SIGNAL_LENGTH = 1000;
    constexpr auto DEMO_SIGNAL_TIME_INCREMENTS = 0.02;

    consteval auto makeTimePoints()
    {
        auto timepoints = std::array<double, DEMO_SIGNAL_LENGTH>{};
        std::ranges::generate(timepoints, [d = 0.0] mutable noexcept -> double
                              {d+=DEMO_SIGNAL_TIME_INCREMENTS; return d; });
        return timepoints;
    }

    consteval auto make3SinSignalAmplitudes(const std::array<double, DEMO_SIGNAL_LENGTH> &timepoints)
    {
        return timepoints | std::views::transform([](double t) -> double
                                                  { return 3.0 * std::sin(1.0 * t) + 1.0 * std::sin(3.0 * t) + 0.5 * std::sin(5.0 * t); });
    }

    constexpr auto toSignalAmplitude = std::views::transform([](double v) noexcept
                                                             { return SignalAmplitude{v}; });
    constexpr auto toTimePoint = std::views::transform([](double v) noexcept
                                                       { return TimePoint{v}; });
}

auto SignalCapturerDemo::createCapture() -> std::expected<SignalCapture, std::string>
{
    static constexpr auto timepoints = makeTimePoints();
    static constexpr auto ampl = make3SinSignalAmplitudes(timepoints);

    return SignalCapture::create({std::from_range, ampl | toSignalAmplitude},
                                 {std::from_range, timepoints | toTimePoint});
}