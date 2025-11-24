#pragma once

#include <expected>
#include <string>

namespace ffv
{
    class SignalCapture;
}

namespace ffv
{
    /*! A Signal Capturer creates SignalCaptures, which can then be analyzed/processed
     */
    class ISignalCapturer
    {
    public:
        //! Generates a signal capture.
        virtual auto createCapture() -> std::expected<SignalCapture, std::string> = 0;

        virtual ~ISignalCapturer() = default;
    };
}