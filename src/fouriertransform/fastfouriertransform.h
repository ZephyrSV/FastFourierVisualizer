#pragma once

namespace ffv
{
    class SignalCapture;
    class SignalFourierTransform;
}

// This implementation is entirely lifted from https://cp-algorithms.com/algebra/fft.html
namespace ffv
{
    auto fft(const SignalCapture &signalCapture) -> SignalFourierTransform;
}