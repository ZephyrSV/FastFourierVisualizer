#pragma once

#include "igraphvisualizerimpl.h"

namespace ffv
{
    class MatPlotLibGraphVisualizer final : public IGraphVisualizerImpl
    {
    public:
        explicit MatPlotLibGraphVisualizer() noexcept = default;

        auto setXYdata(std::vector<double> xData, std::vector<double> yData) -> void final;
        auto setXAxisLabel(std::string xAxisLabel) -> void final;
        auto setYAxisLabel(std::string yAxisLabel) -> void final;
        auto show() const -> void final;

    private:
        std::vector<double> m_xData;
        std::vector<double> m_yData;
        std::string m_xAxisLabel;
        std::string m_yAxisLabel;
    };
}