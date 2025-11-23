#pragma once

#include <memory>
#include <vector>
#include <string>

namespace ffv
{
    class IGraphVisualizerImpl;
}

namespace ffv
{

    /*! Given a graph, can be used to show it to the user through a GUI.

    Handles dependencies to the external library through the G.O.F. Design Pattern "Bridge", aka PIMPL
     */
    class GraphVisualizer final
    {
    public:
        explicit GraphVisualizer() noexcept;
        ~GraphVisualizer() noexcept;

        auto plot(std::vector<double> xData, std::vector<double> yData) -> void;
        auto setXAxisLabel(std::string xAxisLabel) -> void;
        auto setYAxisLabel(std::string yAxisLabel) -> void;
        auto show() const -> void;

    private:
        std::unique_ptr<IGraphVisualizerImpl> m_pimpl;
    };
}