#pragma once

#include "../configuration/cliarguments.h"

#include <memory>

namespace ffv
{
    class ISignalCapturer;
}

namespace ffv
{
    /*! Creates a ISignalCapturer, capable of creating a Signal.
     */
    class SignalCapturerFactory
    {
    public:
        auto create(CLIArguments::InputType inputType) const noexcept -> std::unique_ptr<ISignalCapturer>;
    };
}