#pragma once

namespace Integration {
struct IntegrationSegment {
    double integrationLowerBoundary{};
    double integrationUpperBoundary{};
};

struct Function {
    char* name{};
    double (*function)(double);
    double preciseIntegralValue{};
    double rectangleIntegralSumValue{};
    double trapezoidIntegralSumValue{};
    int rectangleIterationNumber{};
    int trapezoidIterationNumber{};
};

void RectangleIntegration(Function& functionData, IntegrationSegment integrationSegment, double epsilon);
void TrapezoidIntegration(Function& functionData, IntegrationSegment integrationSegment, double epsilon);
void RunIntegration();
void StartApp();
}  // namespace Integration
