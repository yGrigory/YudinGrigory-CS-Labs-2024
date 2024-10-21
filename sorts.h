enum class Option {
    Option1 = 1,
    Option2 = 2
};

namespace Run {
    void RunSelectionSort();
    void RunBubbleSort();
}

namespace Calculation {
    [[nodiscard]] double CalculateSelectionSort();
    [[nodiscard]] double CalculateBubbleSort();
}
