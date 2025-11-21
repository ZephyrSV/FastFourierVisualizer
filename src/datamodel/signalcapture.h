#pragma once

#include <vector>
#include <expected>

#include "signalamplitude.h"
#include "timepoint.h"

namespace ffv
{
    class SignalCapture final
    {
    public:
        static auto create(std::vector<SignalAmplitude> amplitudes,
                           std::vector<TimePoint> timepoints) -> std::expected<SignalCapture, std::string>;

        auto getAmplitudes() const noexcept -> const std::vector<SignalAmplitude> &
        {
            return m_amplitudes;
        }

        auto getTimePoints() const noexcept -> const std::vector<TimePoint> &
        {
            return m_timepoints;
        }

    private:
        explicit SignalCapture(std::vector<SignalAmplitude> amplitudes,
                               std::vector<TimePoint> timepoints);
        std::vector<SignalAmplitude> m_amplitudes;
        std::vector<TimePoint> m_timepoints;
    };
}