#pragma once

#include <vector>

namespace ffv
{
    class SignalFourierTransform final
    {
    public:
        explicit SignalFourierTransform(std::vector<double> dftBins, double sampleRate) noexcept
            : m_dftBins{std::move(dftBins)}, m_sampleRate{sampleRate} {}

        auto getDftBins() const noexcept -> const std::vector<double> &
        {
            return m_dftBins;
        }
        auto getSampleRate() const noexcept -> double
        {
            return m_sampleRate;
        }

    private:
        std::vector<double> m_dftBins;
        double m_sampleRate;
    };
}