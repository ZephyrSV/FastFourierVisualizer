#include "graphvisualizer/graphvisualizer.h"
#include "graphvisualizer/src/matplotlibgraphvisualizer.h"

using namespace ffv;

GraphVisualizer::GraphVisualizer() noexcept
    : m_pimpl{std::make_unique<MatPlotLibGraphVisualizer>()}
{
}

GraphVisualizer::~GraphVisualizer() noexcept = default;

auto GraphVisualizer::plot(std::vector<double> xData, std::vector<double> yData) -> void
{
    m_pimpl->plot(std::move(xData), std::move(yData));
}

auto GraphVisualizer::setXAxisLabel(std::string xAxisLabel) -> void
{
    m_pimpl->setXAxisLabel(std::move(xAxisLabel));
}

auto GraphVisualizer::setYAxisLabel(std::string yAxisLabel) -> void
{
    m_pimpl->setYAxisLabel(std::move(yAxisLabel));
}

auto GraphVisualizer::show() const -> void
{
    m_pimpl->show();
}