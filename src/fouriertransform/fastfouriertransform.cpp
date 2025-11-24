#include "fastfouriertransform.h"

#include "../datamodel/signalcapture.h"
#include "../datamodel/signalfouriertransform.h"

#include <complex>
#include <ranges>
#include <numbers>
#include <vector>
#include <iterator>

// This implementation is lifted from https://www.sanfoundry.com/cpp-program-compute-discrete-fourier-transform-using-fast-fourier-transform-approach/

using complex = std::complex<double>;

namespace FASTFOURIERIMPL
{
    size_t bitReverse(size_t x, size_t log2n)
    {
        size_t n = 0;
        for (size_t i = 0; i < log2n; i++)
        {
            n <<= 1;
            n |= (x & 1);
            x >>= 1;
        }
        return n;
    }

    template <class Iter_T>
        requires std::same_as<complex, typename std::iterator_traits<Iter_T>::value_type>
    void fft(Iter_T a, Iter_T b, size_t log2n)
    {
        const complex J(0, 1);

        size_t n = 1 << log2n;
        for (size_t i = 0; i < n; ++i)
        {
            b[bitReverse(i, log2n)] = a[i];
        }

        for (size_t s = 1; s <= log2n; ++s)
        {
            size_t m = 1 << s;
            size_t m2 = m >> 1;
            complex w(1, 0);
            complex wm = exp(-J * (std::numbers::pi / static_cast<double>(m2)));

            for (size_t j = 0; j < m2; ++j)
            {
                for (size_t k = j; k < n; k += m)
                {
                    complex t = w * b[k + m2];
                    complex u = b[k];

                    b[k] = u + t;
                    b[k + m2] = u - t;
                }

                w *= wm;
            }
        }
    }
}

namespace ffv
{
    auto fft(const SignalCapture &signalCapture) -> SignalFourierTransform
    {
        auto input = std::vector<complex>{std::from_range, signalCapture.getAmplitudes() | std::views::transform([](double d)
                                                                                                                 { return complex{d}; })};
        auto result = std::vector<complex>(signalCapture.getAmplitudes().size());

        FASTFOURIERIMPL::fft(input.data(), result.data(), static_cast<size_t>(std::log2(input.size())));

        auto resultAbs = std::move(result) | std::views::transform([](complex d)
                                                                   { return std::abs(d); }) |
                         std::ranges::to<std::vector<double>>();
        return SignalFourierTransform{resultAbs, 1.0 / signalCapture.getSamplePeriod().count()};
    }

}