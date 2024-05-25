#ifndef Q1_H
#define Q1_H
namespace q1 {
    inline double gradient_descent(double initial_value, double step, std::function<double(double)> f) {
        const int max_iterator = 10000;
        const double tolerance = 1e-6;
        double gradient;
        double current_value = initial_value;
        double previous_value;
        for (int i = 0; i < max_iterator; i++) {
            gradient = (f(current_value + tolerance) - f(current_value)) / tolerance;

            previous_value = current_value;
            current_value = current_value - step * gradient;

            if (std::abs(current_value - previous_value) < tolerance) {
                break;
            }

        }
        return current_value;
    }

    template<typename T, typename Func>
    inline T gradient_descent(T initial_value, T step) {
        const int max_iterator = 10000;
        const T tolerance = 1e-6;
        T gradient;
        T current_value = initial_value;
        T previous_value;
        Func f;
        for (int i = 0; i < max_iterator; i++) {
            gradient = (f(current_value + tolerance) - f(current_value)) / tolerance;

            previous_value = current_value;
            current_value = current_value - step * gradient;

            if (std::abs(current_value - previous_value) < tolerance) {
                break;
            }

        }
        return current_value;
    }
}
#endif //Q1_H