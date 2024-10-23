namespace Menu {
enum class Option {
    Option1,
    Option2,
    Option3,
};

void start();
void inputProcessing(Option option);
}  // namespace Menu

namespace Result {
struct FunctionResult {
    double x;
    int iterationsCount;
};
void printResult(double x, int iterationsCount);
}  // namespace Result

namespace Run {
void RunIterationMethod();
void RunNewtonsMethod();
void RunHalfCoefficientMethod();
}  // namespace Run

namespace Calculation {
[[nodiscard]] Result::FunctionResult CalculateIterationMethod(double epsilon, double coefficient);
[[nodiscard]] Result::FunctionResult CalculateNewtonsMethod(double initialApproximation, double epsilon, double coefficient);
[[nodiscard]] Result::FunctionResult CalculateHalfCoefficientMethod(double leftRangeLimit, double rightRangeLimit, double epsilon,
                                                                    double coefficient);
}  // namespace Calculation
