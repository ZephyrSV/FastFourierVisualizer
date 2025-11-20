#pragma once

namespace ffv
{

    struct CLIArguments
    {
        enum class InputType
        {
            DEMO,
            STDIN
        };

        InputType m_inputType;
    };
}