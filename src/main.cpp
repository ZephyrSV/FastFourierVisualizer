#include <vector>
#include <ranges>
#include <expected>
#include <iostream>

#include "datamodel/signalcapture.h"
#include "configuration/cliargumentparser.h"
#include "signalcapturer/isignalcapturer.h"
#include "signalcapturer/signalcapturerfactory.h"
#include "graphvisualizer/graphvisualizer.h"
#include "graphvisualizer/setupvisualizer.h"
#include "fouriertransform/discretefouriertransform.h"

int main(int argc, char **argv)
{
    using namespace ffv;

    auto graphVisualizer = GraphVisualizer{};

    auto exp = CLIArgumentParser{}
                   .parse(argc, argv)
                   .transform([](const CLIArguments &cliArgs)
                              { return SignalCapturerFactory{}.create(cliArgs.m_inputType); })
                   .and_then([](std::unique_ptr<ISignalCapturer> signalCapturer)
                             { return signalCapturer->createCapture(); })

                   .transform([&graphVisualizer](SignalCapture signalCapture)
                              { 
                                setUpVisualizer(graphVisualizer, signalCapture); 
                                graphVisualizer.show();
                                return signalCapture; })
                   .transform([&graphVisualizer](SignalCapture signalCapture)
                              {
                                setUpVisualizer(graphVisualizer, dft(signalCapture)); 
                                graphVisualizer.show(); });

    if (!exp.has_value())
    {
        std::cerr << "An error has occurred.\n"
                  << exp.error();
        return -1;
    }

    return 0;
}
