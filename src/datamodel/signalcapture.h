#pragma once

#include <vector>
#include <expected>
#include <chrono>

namespace ffv
{
    class SignalCapture final
    {
    public:
        static auto create(std::vector<double> amplitudes,
                           std::chrono::duration<double> samplePeriod) -> std::expected<SignalCapture, std::string>;

        auto getAmplitudes() const noexcept -> const std::vector<double> &
        {
            return m_amplitudes;
        }

        auto getSamplePeriod() const -> std::chrono::duration<double>
        {
            return m_samplePeriod;
        }

    private:
        explicit SignalCapture(std::vector<double> amplitudes,
                               std::chrono::duration<double> samplePeriod);
        std::vector<double> m_amplitudes;
        std::chrono::duration<double> m_samplePeriod;
    };
}