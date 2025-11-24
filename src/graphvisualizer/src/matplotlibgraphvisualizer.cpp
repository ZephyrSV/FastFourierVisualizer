#include "matplotlibgraphvisualizer.h"

#include <matplot/matplot.h>

using namespace ffv;

auto MatPlotLibGraphVisualizer::plot(std::vector<double> xData, std::vector<double> yData) -> void
{
    m_xData = std::move(xData);
    m_yData = std::move(yData);
}

auto MatPlotLibGraphVisualizer::setXAxisLabel(std::string xAxisLabel) -> void
{
    m_xAxisLabel = std::move(xAxisLabel);
}

auto MatPlotLibGraphVisualizer::setYAxisLabel(std::string yAxisLabel) -> void
{
    m_yAxisLabel = std::move(yAxisLabel);
}

auto MatPlotLibGraphVisualizer::show() const -> void
{
    matplot::plot(m_xData, m_yData);
    matplot::xlabel(m_xAxisLabel);
    matplot::ylabel(m_yAxisLabel);
    matplot::grid(true);

    matplot::show(); // Opens a window with the plot
}