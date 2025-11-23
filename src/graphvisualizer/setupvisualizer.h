#pragma once

namespace ffv
{
    class GraphVisualizer;
    class SignalCapture;
    class SignalFourierTransform;
}

namespace ffv
{
    void setUpVisualizer(GraphVisualizer &graphVisualizer, const SignalCapture &toVisualize);
    void setUpVisualizer(GraphVisualizer &graphVisualizer, const SignalFourierTransform &toVisualize);
}
