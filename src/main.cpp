#include <matplot/matplot.h>
#include <vector>
#include <ranges>
#include <expected>

#include "datamodel/signalcapture.h"
#include "configuration/cliargumentparser.h"
#include "signalcapturer/isignalcapturer.h"
#include "signalcapturer/signalcapturerfactory.h"

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

                                   matplot::scatter(signalCapture.getAmplitudes() | asDoubles, signalCapture.getTimePoints() | asDoubles);
                                   matplot::title("Example 2D Points");
                                   matplot::xlabel("x");
                                   matplot::ylabel("y");
                                   matplot::grid(true);
                                   matplot::axis(matplot::equal);
                                   matplot::show(); // Opens a window with the plot
                               });

    if (!expSignalCapture.has_value())
    {
        std::cerr << "An error has occurred.\n"
                  << expSignalCapture.error();
        return -1;
    }

    return 0;
}
