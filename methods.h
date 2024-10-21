struct FunctionResult {
    double x;
    int iterationsCount;
};

namespace Menu {
enum class Option {
    Option1,
    Option2,
    Option3,
    Exit,
    None
};

void start();
void inputProcessing(Option option);
}  // namespace Menu

namespace Run {
void RunIterationMethod();
void RunNewtonsMethod();
void RunHalfCoefficientMethod();
}  // namespace Run

namespace Calculation {
[[nodiscard]] FunctionResult CalculateIterationMethod(double epsilon, double coefficient);
[[nodiscard]] FunctionResult CalculateNewtonsMethod(double initialApproximation, double epsilon, double coefficient);
[[nodiscard]] FunctionResult CalculateHalfCoefficientMethod(double leftRangeLimit, double rightRangeLimit, double epsilon, double coefficient);
}  // namespace Calculation
