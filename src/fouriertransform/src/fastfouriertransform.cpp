#include "../fastfouriertransform.h"

#include "../../datamodel/signalcapture.h"
#include "../../datamodel/signalfouriertransform.h"

#include <complex>
#include <ranges>
#include <numbers>
#include <vector>
#include <iterator>
#include <valarray>

// This implementation is lifted from https://tfetimes.com/c-fast-fourier-transform/

using complex = std::complex<double>;

namespace FASTFOURIERIMPL
{
    typedef std::valarray<complex> CArray;

    // Cooley–Tukey FFT (in-place)
    void fft(CArray &x)
    {
        using namespace std::complex_literals;
        const size_t N = x.size();
        if (N <= 1)
            return;

        // divide
        CArray even = x[std::slice(0, N / 2, 2)];
        CArray odd = x[std::slice(1, N / 2, 2)];

        // conquer
        fft(even);
        fft(odd);

        // combine
        for (size_t k = 0; k < N / 2; ++k)
        {
            auto t = std::exp(-2i * std::numbers::pi * static_cast<double>(k) / static_cast<double>(N)) * odd[k];
            x[k] = even[k] + t;
            x[k + N / 2] = even[k] - t;
        }
    }

}

namespace ffv
{
    auto fft(const SignalCapture &signalCapture) -> SignalFourierTransform
    {
        auto input = std::vector<complex>{std::from_range, signalCapture.getAmplitudes() | std::views::transform([](double d)
                                                                                                                 { return complex{d}; })};

        auto valarray = std::valarray<complex>{input.data(), input.size()};

        FASTFOURIERIMPL::fft(valarray);

        return SignalFourierTransform{{std::from_range, valarray | std::views::transform([](complex d)
                                                                                         { return std::abs(d); })},
                                      1.0 / signalCapture.getSamplePeriod().count()};
    }

}