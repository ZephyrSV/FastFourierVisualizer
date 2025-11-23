#pragma once

#include <string>
#include <vector>

namespace ffv
{
    class IGraphVisualizerImpl
    {
    public:
        virtual ~IGraphVisualizerImpl() = default;

        virtual auto plot(std::vector<double> xData, std::vector<double> yData) -> void = 0;
        virtual auto setXAxisLabel(std::string xAxisLabel) -> void = 0;
        virtual auto setYAxisLabel(std::string yAxisLabel) -> void = 0;
        virtual auto show() const -> void = 0;
    };
}
