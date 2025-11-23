#include "../setupvisualizer.h"

#include "../graphvisualizer.h"
#include "../../datamodel/signalcapture.h"
#include "../../datamodel/signalfouriertransform.h"

#include <ranges>
#include <algorithm>
#include <vector>

namespace ffv
{
    void setUpVisualizer(GraphVisualizer &graphVisualizer, const SignalCapture &toVisualize)
    {
        constexpr auto makeTimePoints = [](size_t size, std::chrono::duration<double> samplePeriod)
        {
            auto timepoints = std::vector<double>(size);
            std::ranges::generate(timepoints, [d = 0.0, samplePeriod] mutable noexcept -> double
                                  {d+=samplePeriod.count(); return d; });
            return timepoints;
        };

        graphVisualizer.plot(makeTimePoints(toVisualize.getAmplitudes().size(), toVisualize.getSamplePeriod()), toVisualize.getAmplitudes());
        graphVisualizer.setXAxisLabel("Time (s)");
        graphVisualizer.setYAxisLabel("Amplitude");
    }

    void setUpVisualizer(GraphVisualizer &graphVisualizer, const SignalFourierTransform &toVisualize)
    {
        constexpr auto makeFrequencyBins = [](const SignalFourierTransform &signalft)
        {
            auto N = signalft.getDftBins().size();
            auto fs = signalft.getSampleRate();
            auto frequencies = std::vector<double>(N / 2);
            std::ranges::generate(frequencies, [&, d = 0.0] mutable noexcept -> double
                                  {d+=static_cast<double>(fs)/static_cast<double>(N); 
                                    return d; });
            return frequencies;
        };

        graphVisualizer.plot(makeFrequencyBins(toVisualize), toVisualize.getDftBins());
        graphVisualizer.setXAxisLabel("frequency (Hz)");
        graphVisualizer.setYAxisLabel("Amplitude");
    }
}
