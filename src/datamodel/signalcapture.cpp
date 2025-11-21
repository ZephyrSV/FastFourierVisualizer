#include "signalcapture.h"

using namespace ffv;

auto SignalCapture::create(std::vector<SignalAmplitude> amplitudes,
                           std::vector<TimePoint> timepoints) -> std::expected<SignalCapture, std::string>
{
    if (amplitudes.size() != timepoints.size())
        return std::unexpected(
            std::format("Cannot create a SignalCapture with amplitudes and timepoints vectors of different lengths (amplitudes: {}, timepoints: {})",
                        amplitudes.size(), timepoints.size()));

    return SignalCapture(std::move(amplitudes), std::move(timepoints));
}

SignalCapture::SignalCapture(std::vector<SignalAmplitude> amplitudes,
                             std::vector<TimePoint> timepoints)
    : m_amplitudes{std::move(amplitudes)}, m_timepoints{std::move(timepoints)}
{
}
