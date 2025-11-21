#pragma once

#include "../isignalcapturer.h"
#include "../../datamodel/signalcapture.h"

#include <iostream>

namespace ffv
{
    class SignalCapturerStdin final : public ISignalCapturer
    {
    public:
        ~SignalCapturerStdin() final = default;

    private:
        auto createCapture() -> std::expected<SignalCapture, std::string> final
        {
            auto amplitudes = std::vector<SignalAmplitude>{};
            auto timepoints = std::vector<TimePoint>{};

            double amplitude, timepoint;
            while (std::cin >> amplitude >> timepoint)
            {
                amplitudes.emplace_back(amplitude);
                timepoints.emplace_back(timepoint);
            }

            return SignalCapture::create(std::move(amplitudes), std::move(timepoints));
        }
    };
}