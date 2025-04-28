#include <tiledarray.h>
#include "libs/pauli.hpp"

using cmplx = std::complex<double>;

int main(int argc, char **argv) {
  auto &world = TA::initialize(argc, argv);

  TA::TArrayZ py = Pauli::get_y(world);
  TA::TArrayZ empty = Pauli::get_empty_2x2(world);

  empty("i,k") = conj(py("i,k"));
  std::cout << "σʸ = \n" << py << "\n";
  std::cout << "conj(σʸ) = \n" << empty << "\n";

  TA::finalize();
  return 0;
}
