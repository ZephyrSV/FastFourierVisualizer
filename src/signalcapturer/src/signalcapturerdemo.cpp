#include "signalcapturer/src/signalcapturerdemo.h"

#include "datamodel/signalcapture.h"

#include <ranges>
#include <algorithm>
#include <cmath>
#include <numbers>

using namespace ffv;

namespace
{
    constexpr auto DEMO_SIGNAL_LENGTH = 1000;
    constexpr auto DEMO_SIGNAL_SAMPLE_PERIOD = 0.02;

    consteval auto makeTimePoints()
    {
        auto timepoints = std::array<double, DEMO_SIGNAL_LENGTH>{};
        std::ranges::generate(timepoints, [d = 0.0] mutable noexcept -> double
                              {d+=DEMO_SIGNAL_SAMPLE_PERIOD; return d; });
        return timepoints;
    }

    constexpr auto sinWave(double freq, double t) -> double
    {
        return std::sin(std::numbers::pi * 2.0 * freq * t);
    };

    consteval auto make3SinWave()
    {
        return makeTimePoints() | std::views::transform([](double t) -> double
                                                        { return 1.0 * sinWave(1, t) + 1.0 * sinWave(3.0, t) + 1.0 * sinWave(5.0, t); });
    }
}

auto SignalCapturerDemo::createCapture() -> std::expected<SignalCapture, std::string>
{
    static constexpr auto amplitudes = make3SinWave();

    return SignalCapture::create({std::from_range, amplitudes},
                                 std::chrono::duration<double>{DEMO_SIGNAL_SAMPLE_PERIOD});
}