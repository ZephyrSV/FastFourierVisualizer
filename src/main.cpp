#include <vector>
#include <ranges>
#include <expected>
#include <iostream>

#include "datamodel/signalcapture.h"
#include "configuration/cliargumentparser.h"
#include "signalcapturer/isignalcapturer.h"
#include "signalcapturer/signalcapturerfactory.h"
#include "graphvisualizer/graphvisualizer.h"

int main(int argc, char **argv)
{
    using namespace ffv;

    auto expCLIArgs = CLIArgumentParser{}.parse(argc, argv);

    auto expSignalCapture = expCLIArgs.transform([](const CLIArguments &cliArgs)
                                                 { return SignalCapturerFactory{}.create(cliArgs.m_inputType); })
                                .and_then([](std::unique_ptr<ISignalCapturer> signalCapturer)
                                          { return signalCapturer->createCapture(); });

    expSignalCapture.transform([](SignalCapture signalCapture)
                               {
                                   constexpr static auto asDoubles = std::views::transform([](const auto &e)
                                                                                           { return asDouble(e); }) |
                                                                     std::ranges::to<std::vector<double>>();

                                   auto graphVisualizer = GraphVisualizer{};
                                   graphVisualizer.setXYdata(signalCapture.getTimePoints() | asDoubles, signalCapture.getAmplitudes() | asDoubles);
                                   graphVisualizer.setXAxisLabel("Time (s)");
                                   graphVisualizer.setYAxisLabel("Amplitude");
                                   graphVisualizer.show(); });

    if (!expSignalCapture.has_value())
    {
        std::cerr << "An error has occurred.\n"
                  << expSignalCapture.error();
        return -1;
    }

    return 0;
}
