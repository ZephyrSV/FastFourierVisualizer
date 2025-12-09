#pragma once

#include "signalcapturer/isignalcapturer.h"
#include "datamodel/signalcapture.h"

#include <iostream>

namespace ffv
{
    /*!
    Creates a signal by reading stdin
    */
    class SignalCapturerStdin final : public ISignalCapturer
    {
    public:
        ~SignalCapturerStdin() final = default;

    private:
        auto createCapture() -> std::expected<SignalCapture, std::string> final
        {
            double samplePeriod;
            if (!(std::cin >> samplePeriod))
                return std::unexpected("No signal was provided through stdin. You must first send the sampling period then the samples.");

            auto amplitudes = std::vector<double>{};
            double amplitude;
            while (std::cin >> amplitude)
            {
                amplitudes.emplace_back(amplitude);
            }

            return SignalCapture::create(std::move(amplitudes), std::chrono::duration<double>{samplePeriod});
        }
    };
}