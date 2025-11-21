#pragma once
#include <type_traits>

namespace ffv
{
    /*! Represents an Amplitude of a signal at a specific point.

    It gets to be a type is for type-safe coding, as there exists SignalTime whose
    underlying value type is also double.
    */
    struct SignalAmplitude
    {
        const double m_value;
    };

    // This type should be trivial, otherwise the compiler wouldn't be able to
    // optimize construction, destr, copies, moves, etc.
    static_assert(std::is_trivial_v<SignalAmplitude>);

    inline auto asDouble(SignalAmplitude signalAmplitude) -> double
    {
        return signalAmplitude.m_value;
    }
}