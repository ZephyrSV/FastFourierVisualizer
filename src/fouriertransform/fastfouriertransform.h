#pragma once

namespace ffv
{
    class SignalCapture;
    class SignalFourierTransform;
}

// This implementation is lifted from https://tfetimes.com/c-fast-fourier-transform/
namespace ffv
{
    /*! Computes the Discrete Fourier Transform using the Fast Fourier Transform. This method is O(n log n).
     */
    auto fft(const SignalCapture &signalCapture) -> SignalFourierTransform;
}