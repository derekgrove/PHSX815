#include <iostream>
#include <cmath>


double my_function(double x) {
    return std::pow(x, 5) + 8;
}


double trapezoidal_rule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = (my_function(a) + my_function(b)) / 2.0;

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += my_function(x);
    }

    return sum * h;
}

double function(double x) {
    return std::pow(x, 5) + 8;
}

double gauss_legendre_integration(double a, double b, int n) {
    double sum = 0.0;
    double x, w;

    double *x_arr = new double[n];
    double *w_arr = new double[n];

    if (n == 2) {
        x_arr[0] = -1 / std::sqrt(3);
        x_arr[1] = 1 / std::sqrt(3);

        w_arr[0] = w_arr[1] = 1;
    } else if (n == 3) {
        x_arr[0] = -std::sqrt(3.0 / 5.0);
        x_arr[1] = 0;
        x_arr[2] = std::sqrt(3.0 / 5.0);

        w_arr[0] = w_arr[2] = 5.0 / 9.0;
        w_arr[1] = 8.0 / 9.0;
    } else if (n == 4) {
        x_arr[0] = -std::sqrt((3 + 2 * std::sqrt(6.0 / 5.0)) / 7.0);
        x_arr[1] = -std::sqrt((3 - 2 * std::sqrt(6.0 / 5.0)) / 7.0);
        x_arr[2] = std::sqrt((3 - 2 * std::sqrt(6.0 / 5.0)) / 7.0);
        x_arr[3] = std::sqrt((3 + 2 * std::sqrt(6.0 / 5.0)) / 7.0);

        w_arr[0] = w_arr[3] = (18 - std::sqrt(30)) / 36.0;
        w_arr[1] = w_arr[2] = (18 + std::sqrt(30)) / 36.0;
    } else {
        std::cerr << "Error: unsupported number of points." << std::endl;
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        x = ((b - a) * x_arr[i] + a + b) / 2.0;
        w = (b - a) * w_arr[i] / 2.0;
        sum += w * function(x);
    }

    delete[] x_arr;
    delete[] w_arr;

    return sum;
}

int main(int argc, char *argv[]) {
    int intervals = 100;
    int type = 0;
    double a = 0.0; // lower limit of integration
    double b = 2.0; // upper limit of integration
    int quadrature = 2; // number of quadrature points for integration

    for (int i = 0; i < argc; i++) {
        if (strncmp(argv[i], "-intv", 5) == 0) {
            i++;
            int interv = std::stoi(argv[i]);
            if (interv > 0)
                intervals = interv;
        }
        if (strncmp(argv[i], "-type", 5) == 0) {
            i++;
            int t = std::stoi(argv[i]);
            if (t > 0)
                type = t;
        }
        if (strncmp(argv[i], "-a", 2) == 0) {
            i++;
            int A = std::stoi(argv[i]);
            if (A > 0) {
                a = A;
            }
            }
            if (strncmp(argv[i], "-b", 2) == 0) {
                i++;
                int B = std::stoi(argv[i]);
                if (B > 0) {
                    b = B;
                }
            }
        }
    double integral = 0.0;
    //add functionality to select the type of integration here, if type = 0, trapezoid, if type = 1, gaussian, else: exit()
    if (type == 0) {
        integral = trapezoidal_rule(a, b, intervals);
    } else if (type == 1) {
        std::cout << "What quadrature order would you like? (enter only a number,  2, 3, or 4):" << std::endl;
        std::cin >> quadrature;
        integral = gauss_legendre_integration(a, b, quadrature);
    }

    double analytic_result = std::pow(b, 6)/6 + 8*b -std::pow(a, 6)/6 - 8*a;

    std::cout << "The numerical integration of y = x^5 + 8 from " << a << " to " << b << " with " << intervals << " intervals is: " << integral << std::endl;
    std::cout << "for comparison, the analytic result for the integral is x^6/6 + 8x + C, and with limits " << a << " to " << b << " we get result: " << analytic_result << " + C" << std::endl;
    return 0;
}
