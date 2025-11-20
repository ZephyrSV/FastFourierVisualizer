#include <matplot/matplot.h>
#include <vector>

#include "datamodel/signalcapture.h"
#include "configuration/cliargumentparser.h"

int main(int argc, char **argv)
{
    auto cliArgs = ffv::CLIArgumentParser::parse(argc, argv);
    if (!cliArgs.has_value())
        return cliArgs.error();

    if (cliArgs->m_inputType != ffv::CLIArguments::InputType::DEMO)
    {
        std::cerr << "This is not yet implemented sorry :(";
        return 0;
    }

    //  auto signalCapture = ffv::SignalCapture::create(std::vector<ffv::SignalAmplitude>{SignalAmplitude{0.}, 1., 2.5, 3., 4., 2.}, {0, 2, 1.5, 3.5, 2, -0.5});
    std::vector<double> xs = {0, 1, 2.5, 3, 4, 2};
    std::vector<double> ys = {0, 2, 1.5, 3.5, 2, -0.5};

    matplot::scatter(xs, ys);
    matplot::title("Example 2D Points");
    matplot::xlabel("x");
    matplot::ylabel("y");
    matplot::grid(true);
    matplot::axis(matplot::equal);
    matplot::show(); // Opens a window with the plot

    return 0;
}
