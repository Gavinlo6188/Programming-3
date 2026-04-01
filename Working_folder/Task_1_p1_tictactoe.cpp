// Task 2 — Linear Regression in C++
// - Generate synthetic dataset from y = kx + m, with noise on both x and y
// - Fit using (A) Normal Equation (closed form)
// - Fit using (B) Gradient Descent
// - Save dataset + fitted lines to CSV for plotting in Python
//
// Matches the Task 2 requirements in the assignment. :contentReference[oaicite:0]{index=0}

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

struct DataPoint {
    double x;
    double y;
};

// Generate dataset:
// x_true uniform in [x_min, x_max]
// y_true = k*x_true + m_true
// x = x_true + noise_x, y = y_true + noise_y
std::vector<DataPoint> generate_dataset(
    int n,
    double k_true,
    double m_true,
    double x_min,
    double x_max,
    double noise_x_std,
    double noise_y_std,
    unsigned int seed = 0
) {
    if (n <= 1) throw std::invalid_argument("n must be > 1");

    std::mt19937 rng;
    if (seed == 0) {
        std::random_device rd;
        rng.seed(rd());
    } else {
        rng.seed(seed);
    }

    std::uniform_real_distribution<double> dist_x(x_min, x_max);
    std::normal_distribution<double> noise_x(0.0, noise_x_std);
    std::normal_distribution<double> noise_y(0.0, noise_y_std);

    std::vector<DataPoint> data;
    data.reserve(n);

    for (int i = 0; i < n; ++i) {
        double x_true = dist_x(rng);
        double y_true = k_true * x_true + m_true;

        double x = x_true + noise_x(rng);
        double y = y_true + noise_y(rng);

        data.push_back({x, y});
    }

    return data;
}

// Normal Equation (simple linear regression):
// w = ( n*sum(xy) - sum(x)sum(y) ) / ( n*sum(x^2) - (sum(x))^2 )
// b = y_bar - w*x_bar
std::pair<double, double> fit_normal_equation(const std::vector<DataPoint>& data) {
    const int n = static_cast<int>(data.size());
    if (n <= 1) throw std::invalid_argument("Need at least 2 points.");

    long double sum_x = 0.0L, sum_y = 0.0L, sum_xy = 0.0L, sum_x2 = 0.0L;

    for (const auto& p : data) {
        sum_x  += p.x;
        sum_y  += p.y;
        sum_xy += p.x * p.y;
        sum_x2 += p.x * p.x;
    }

    long double denom = (static_cast<long double>(n) * sum_x2) - (sum_x * sum_x);
    if (std::fabs(denom) < 1e-18L) {
        throw std::runtime_error("Normal equation failed: denominator ~ 0 (x values may be identical).");
    }

    long double w = (static_cast<long double>(n) * sum_xy - sum_x * sum_y) / denom;
    long double x_bar = sum_x / n;
    long double y_bar = sum_y / n;
    long double b = y_bar - w * x_bar;

    return {static_cast<double>(w), static_cast<double>(b)};
}

// Gradient Descent for MSE loss:
// L(w,b) = (1/2n) * sum ( (w x + b - y)^2 )
//
// dL/dw = (1/n) * sum ( (w x + b - y) * x )
// dL/db = (1/n) * sum ( (w x + b - y) )
std::pair<double, double> fit_gradient_descent(
    const std::vector<DataPoint>& data,
    double learning_rate,
    int iterations,
    double w_init = 0.0,
    double b_init = 0.0,
    double* final_loss_out = nullptr
) {
    const int n = static_cast<int>(data.size());
    if (n <= 1) throw std::invalid_argument("Need at least 2 points.");
    if (iterations <= 0) throw std::invalid_argument("iterations must be > 0.");
    if (learning_rate <= 0.0) throw std::invalid_argument("learning_rate must be > 0.");

    double w = w_init;
    double b = b_init;

    auto compute_loss = [&](double ww, double bb) {
        long double s = 0.0L;
        for (const auto& p : data) {
            long double yhat = ww * p.x + bb;
            long double e = yhat - p.y;
            s += e * e;
        }
        return static_cast<double>(0.5L * s / n);
    };

    for (int it = 0; it < iterations; ++it) {
        long double grad_w = 0.0L;
        long double grad_b = 0.0L;

        for (const auto& p : data) {
            long double yhat = w * p.x + b;
            long double e = yhat - p.y;
            grad_w += e * p.x;
            grad_b += e;
        }

        grad_w /= n;
        grad_b /= n;

        // Update
        w -= learning_rate * static_cast<double>(grad_w);
        b -= learning_rate * static_cast<double>(grad_b);

        // Optional: simple safety against NaN divergence
        if (!std::isfinite(w) || !std::isfinite(b)) {
            throw std::runtime_error("Gradient descent diverged (w/b became non-finite). Try smaller learning_rate.");
        }
    }

    if (final_loss_out) {
        *final_loss_out = compute_loss(w, b);
    }

    return {w, b};
}

void write_csv_with_predictions(
    const std::string& filename,
    const std::vector<DataPoint>& data,
    double k_true,
    double m_true,
    double w_ne,
    double b_ne,
    double w_gd,
    double b_gd
) {
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Failed to open output file: " + filename);

    out << "x,y,y_true,y_pred_ne,y_pred_gd\n";
    out << std::setprecision(10);

    for (const auto& p : data) {
        double y_true = k_true * p.x + m_true;
        double y_pred_ne = w_ne * p.x + b_ne;
        double y_pred_gd = w_gd * p.x + b_gd;
        out << p.x << "," << p.y << "," << y_true << "," << y_pred_ne << "," << y_pred_gd << "\n";
    }
}

int main() {
    try {
        // ===== You can tweak these values =====
        const int    N = 120;
        const double k_true = 3.0;     // "k" in assignment statement y = kx + m
        const double m_true = 4.0;     // "m" in assignment statement y = kx + m
        const double x_min = 0.0;
        const double x_max = 10.0;

        // Noise levels (keep moderate so it doesn't look "wild")
        const double noise_x_std = 0.15;
        const double noise_y_std = 0.60;

        // Gradient descent settings
        const double eta = 0.01;
        const int    iters = 8000;
        // =====================================

        // 1) Generate dataset
        auto data = generate_dataset(N, k_true, m_true, x_min, x_max, noise_x_std, noise_y_std);

        // 2) Fit by Normal Equation
        auto [w_ne, b_ne] = fit_normal_equation(data);

        // 3) Fit by Gradient Descent
        double final_loss = 0.0;
        auto [w_gd, b_gd] = fit_gradient_descent(data, eta, iters, 0.0, 0.0, &final_loss);

        // 4) Print comparison
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "True model:\n";
        std::cout << "  k_true = " << k_true << ", m_true = " << m_true << "\n\n";

        std::cout << "Normal Equation result:\n";
        std::cout << "  w = " << w_ne << ", b = " << b_ne << "\n\n";

        std::cout << "Gradient Descent result:\n";
        std::cout << "  w = " << w_gd << ", b = " << b_gd << "\n";
        std::cout << "  final loss (0.5*MSE) = " << final_loss << "\n\n";

        // 5) Save CSV for plotting in Python
        const std::string csv_name = "data.csv";
        write_csv_with_predictions(csv_name, data, k_true, m_true, w_ne, b_ne, w_gd, b_gd);

        std::cout << "Wrote dataset + predictions to: " << csv_name << "\n";
        std::cout << "Plot it using the Python snippet below.\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}