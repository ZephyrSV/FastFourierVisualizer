#pragma once

namespace ffv
{
    class SignalCapture;
    class SignalFourierTransform;
}

namespace ffv
{
    /*! Computes the Discrete Fourier Transform using it's definition. This method is O(n2).
     */
    auto dft(const SignalCapture &signalCapture) -> SignalFourierTransform;
}