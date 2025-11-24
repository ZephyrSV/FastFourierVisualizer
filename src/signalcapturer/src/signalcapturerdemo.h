#pragma once

#include "../isignalcapturer.h"

namespace ffv
{
    /*!
    Creates a predefined pattern and produces a SignalCapture
    */
    class SignalCapturerDemo final : public ISignalCapturer
    {
    public:
        ~SignalCapturerDemo() final = default;

    private:
        auto createCapture() -> std::expected<SignalCapture, std::string> final;
    };
}