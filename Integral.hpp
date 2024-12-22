#pragma once

namespace IntegralSolution {

struct FunctionData {
    char* nameFunction{};

    double resultValue{};
    int iterationCount{};

    double exactValue{};
};

void CalculateRectangleIntegration(double (*function)(double), FunctionData& functionData, double& leftBoundary, double& rightBoundary, double accuracy);
void CalculateTrapezoidIntegration(double (*function)(double), FunctionData& functionData, double& leftBoundary, double& rightBoundary, double accuracy);
void RunIntegralSolution();
void LaunchApp();
} // namespace IntegralSolution

namespace TableStatistic {
void PrintTable(IntegralSolution::FunctionData functionData[], int functionsAmount, int precision);
} // namespace TableStatistic
