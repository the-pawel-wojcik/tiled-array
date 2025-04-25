#include <complex>
#include <tiledarray.h>

using cmplx = std::complex<double>;

int main(int argc, char **argv) {
  auto &world = TA::initialize(argc, argv);

  using ArrayType = TA::TArray<cmplx>;
  ArrayType::numeric_type test{0.71, 0.71};
  std::cout << "Test:    " << test << std::endl;
  std::cout << "Test**2: " << test*test << std::endl;

  TA::finalize();
  return 0;
}
