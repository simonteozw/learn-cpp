#include <cstdio>
#include <complex>

int main() {
    std::complex<double> a{0.5, 14.13};
    printf("%f %f\n", std::real(a), std::imag(a));
}