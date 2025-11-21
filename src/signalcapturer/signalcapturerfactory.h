#pragma once

#include "../configuration/cliarguments.h"

#include <memory>

namespace ffv
{
    class ISignalCapturer;
}

namespace ffv
{
    class SignalCapturerFactory
    {
    public:
        auto create(CLIArguments::InputType inputType) const noexcept -> std::unique_ptr<ISignalCapturer>;
    };
}