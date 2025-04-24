/* Test matrix operations on small matrices */

#include <TiledArray/fwd.h>
#include <TiledArray/initialize.h>
#include <TiledArray/tensor/tensor.h>
#include <TiledArray/tiled_range1.h>
#include <complex>
#include <tiledarray.h>

using cmplx = std::complex<double>;

void init_array(TA::TArrayZ &x, const cmplx z) {
  for (auto it = begin(x); it != end(x); ++it) {
    TA::Tensor<cmplx> tile(x.trange().make_tile_range(it.index()));
    std::fill(tile.begin(), tile.end(), z);
    *it = tile;
  }
}

void init_pauli_x(TA::TArrayZ &pauli) {
  // There is only one tile in ths array.
  auto it = begin(pauli);
  TA::Tensor<cmplx> tile(pauli.trange().make_tile_range(it.index()));
  tile[0] = cmplx{0.0, 0.0};
  tile[1] = cmplx{1.0, 0.0};
  tile[2] = cmplx{1.0, 0.0};
  tile[3] = cmplx{0.0, 0.0};
  *it = tile;
}

void init_pauli_y(TA::TArrayZ &pauli) {
  auto it = begin(pauli);
  TA::Tensor<cmplx> tile(pauli.trange().make_tile_range(it.index()));
  tile[0] = cmplx{0.0, 0.0};
  tile[1] = cmplx{0.0, -1.0};
  tile[2] = cmplx{0.0, 1.0};
  tile[3] = cmplx{0.0, 0.0};
  *it = tile;
}

void init_pauli_z(TA::TArrayZ &pauli) {
  auto it = begin(pauli);
  TA::Tensor<cmplx> tile(pauli.trange().make_tile_range(it.index()));
  tile[0] = cmplx{1.0, 0.0};
  tile[1] = cmplx{0.0, 0.0};
  tile[2] = cmplx{0.0, 0.0};
  tile[3] = cmplx{-1.0, 0.0};
  *it = tile;
}

int main(int argc, char **argv) {
  auto &world = TA::initialize(argc, argv);

  // Construct the 2D TiledRange
  TA::TiledRange trange{
      TA::TiledRange1{
          0,
          2,
      },
      TA::TiledRange1{
          0,
          2,
      },
  };

  std::vector<TA::TArrayZ> paulis{
      TA::TArrayZ{world, trange},
      TA::TArrayZ{world, trange},
      TA::TArrayZ{world, trange},
  };

  init_pauli_x(paulis[0]);
  init_pauli_y(paulis[1]);
  init_pauli_z(paulis[2]);

  // Print the content of input tensors, a and b.
  std::cout << "σˣ = \n" << paulis[0] << "\n";
  std::cout << "σʸ = \n" << paulis[1] << "\n";
  std::cout << "σᶻ = \n" << paulis[2] << "\n";

  // Construct a 1D vector
  TA::TiledRange trange1d{
      TA::TiledRange1{
          0,
          2,
      },
  };

  std::vector<TA::TArrayZ> basis{
      TA::TArrayZ{world, trange1d},
      TA::TArrayZ{world, trange1d},
  };

  for (auto &left : paulis) {
    for (auto &right : paulis) {
      cmplx left_times_right = TiledArray::dot(left("m,k"), right("k,m"));
      std::cout << "Tr(σleft * σright) = " << std::real(left_times_right)
                << "\n";
    }
  }

  // An extra test
  cmplx prod =
      TiledArray::dot(paulis[0]("m,l") * paulis[1]("l,k"), paulis[2]("k,m"));
  std::cout << "Tr(σˣ * σʸ * σᶻ) = " << std::real(prod) << " + "
            << std::imag(prod) << "i" << "\n";

  TA::finalize();
  return 0;
}
