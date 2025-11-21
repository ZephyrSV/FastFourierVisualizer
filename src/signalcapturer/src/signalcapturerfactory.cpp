#include "../signalcapturerfactory.h"

#include "signalcapturerdemo.h"
#include "signalcapturerstdin.h"

using namespace ffv;

auto SignalCapturerFactory::create(CLIArguments::InputType inputType) const noexcept -> std::unique_ptr<ISignalCapturer>
{
    switch (inputType)
    {
        using enum CLIArguments::InputType;
    case STDIN:
        return std::make_unique<SignalCapturerStdin>();
    case DEMO:
        return std::make_unique<SignalCapturerDemo>();
    }
}