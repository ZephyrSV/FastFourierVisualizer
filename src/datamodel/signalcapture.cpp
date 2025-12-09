#include "datamodel/signalcapture.h"

using namespace ffv;

auto SignalCapture::create(std::vector<double> amplitudes,
                           std::chrono::duration<double> samplePeriod) -> std::expected<SignalCapture, std::string>
{
    return SignalCapture(std::move(amplitudes), samplePeriod);
}

SignalCapture::SignalCapture(std::vector<double> amplitudes,
                             std::chrono::duration<double> samplePeriod)
    : m_amplitudes{std::move(amplitudes)}, m_samplePeriod{std::move(samplePeriod)}
{
}
