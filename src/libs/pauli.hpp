#include <complex>
#include <tiledarray.h>

namespace Pauli {
using cmplx = std::complex<double>;

TA::TArrayZ get_empty_2x2(TA::World &);
TA::TArrayZ get_x(TA::World &);
TA::TArrayZ get_y(TA::World &);
TA::TArrayZ get_z(TA::World &);

} // namespace Pauli
