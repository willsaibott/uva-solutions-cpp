#include <bits/stdc++.h>

static const double error{ 0.0000001 };

class Solution {
public:

  static double
  equation(double p,
           double q,
           double r,
           double s,
           double t,
           double u,
           double x)
  {
    return p * std::exp(-x) + q * std::sin(x) + r * std::cos(x) +
           s * std::tan(x) + t * x * x + u;
  }

  static double
  solve(double p,
        double q,
        double r,
        double s,
        double t,
        double u)
  {
    double last_x = std::numeric_limits<double>::max();
    double result = std::numeric_limits<double>::max();
    double x_min = 0, x_max = 1;
    double x = 0;
    auto result1 = equation(p, q, r, s, t, u, x_min);
    auto result2 = equation(p, q, r, s, t, u, x_max);
    bool decrescent = result2 < result1;

    if (result1 * result2 <= 0.0) {
      while (last_x != x && (std::abs(result) > error)) {
        result = equation(p, q, r, s, t, u, x);
        last_x = x;

        if (result > 0) {
          if (decrescent) {
            x_min = x;
          }
          else {
            x_max = x;
          }
        }
        else {
          if (decrescent) {
            x_max = x;
          }
          else {
            x_min = x;
          }
        }
        x = (x_max + x_min) / 2;
      }
    }

    return std::abs(result) > error ?
           std::numeric_limits<double>::max() :
           last_x;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  double p, q, r, s, t, u, x;
  Solution solution;
  while (std::cin >> p >> q >> r >> s >> t >> u) {
    x = solution.solve(p, q, r, s, t, u);
    if (x >= 0.0 && x <= 1.0) {
      std::cout << std::setprecision(4) << std::fixed << x << "\n";
    }
    else {
      std::cout << "No solution\n";
    }
  }
}

