#pragma once

#include "../isignalcapturer.h"

namespace ffv
{
    class SignalCapturerDemo final : public ISignalCapturer
    {
    public:
        ~SignalCapturerDemo() final = default;

    private:
        auto createCapture() -> std::expected<SignalCapture, std::string> final;
    };
}