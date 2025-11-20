#pragma once
#include <type_traits>

namespace ffv
{
    /*! Represents an Amplitude of a signal at a specific point.

    It gets to be a type is for type-safe coding, as there exists SignalTime whose
    underlying value type is also double.
    */
    class SignalAmplitude final
    {
    public:
        constexpr auto getValue() const noexcept -> double { return m_value; }

    private:
        double m_value;
    };

    // This type should be trivial, otherwise the compiler wouldn't be able to
    // optimize construction, destr, copies, moves, etc.
    static_assert(std::is_trivial_v<SignalAmplitude>);

} // namespace ffv