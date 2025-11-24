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
        auto N = toVisualize.getDftBins().size();
        auto fs = toVisualize.getSampleRate();

        constexpr auto makeFrequencyBins = [](size_t N, double fs)
        {
            auto frequencies = std::vector<double>(N / 2);
            std::ranges::generate(frequencies, [&, d = 0.0] mutable noexcept -> double
                                  {d+=fs/static_cast<double>(N); 
                                    return d; });
            return frequencies;
        };

        auto normalize = [N](double d)
        { return d / static_cast<double>(N / 2); };

        graphVisualizer.plot(makeFrequencyBins(N, fs), {std::from_range, toVisualize.getDftBins() | std::views::transform(normalize)});
        graphVisualizer.setXAxisLabel("frequency (Hz)");
        graphVisualizer.setYAxisLabel("Amplitude");
    }
}
