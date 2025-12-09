#include "fouriertransform/discretefouriertransform.h"

#include "datamodel/signalcapture.h"
#include "datamodel/signalfouriertransform.h"

#include <vector>
#include <ranges>
#include <execution>
#include <algorithm>
#include <numeric>
#include <complex>
#include <numbers>

namespace ffv
{
    using complex = std::complex<double>;

    auto dft(const SignalCapture &signalCapture) -> SignalFourierTransform
    {
        using namespace std::complex_literals;

        const auto N = signalCapture.getAmplitudes().size();
        auto result = std::vector<double>(N, 0.);

        for (size_t kIndex = 0; kIndex < N; ++kIndex)
        {
            auto tmp = complex{};
            for (size_t nIndex = 0; nIndex < N; ++nIndex)
            {
                tmp += signalCapture.getAmplitudes()[nIndex] * std::exp(-2.0i * std::numbers::pi * static_cast<double>(kIndex) / static_cast<double>(N) * static_cast<double>(nIndex));
            }
            result[kIndex] = std::abs(tmp);
        }

        return SignalFourierTransform{result, 1.0 / signalCapture.getSamplePeriod().count()};
    }
}