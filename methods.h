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
struct MethodResult {
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
[[nodiscard]] Result::MethodResult CalculateIterationMethod(double epsilon, double coefficient);
[[nodiscard]] Result::MethodResult CalculateNewtonsMethod(double initialApproximation, double epsilon, double coefficient);
[[nodiscard]] Result::MethodResult CalculateHalfCoefficientMethod(double leftRangeLimit, double rightRangeLimit, double epsilon,
                                                                    double coefficient);
}  // namespace Calculation
