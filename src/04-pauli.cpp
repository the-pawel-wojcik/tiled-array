/* Test matrix operations on small matrices */

#include <TiledArray/initialize.h>
#include <TiledArray/tensor/tensor.h>
#include <TiledArray/tiled_range1.h>
#include <tiledarray.h>
#include <complex>

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
  tile[2] = cmplx{0.0,  1.0};
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

  // Construct array objects.
  TA::TArrayZ pauli_x(world, trange);
  TA::TArrayZ pauli_y(world, trange);
  TA::TArrayZ pauli_z(world, trange);

  init_pauli_x(pauli_x);
  init_pauli_y(pauli_y);
  init_pauli_z(pauli_z);

  TA::TArrayZ general(world, trange);
  init_array(general, 0.0);

  // Print the content of input tensors, a and b.
  std::cout << "σˣ = \n" << pauli_x << "\n";
  std::cout << "σʸ = \n" << pauli_y << "\n";
  std::cout << "σᶻ = \n" << pauli_z << "\n";

  general("m,n") = pauli_x("m,k") * pauli_y("k,n");
  std::cout << "σˣ * σʸ = \n" << general << "\n";
  world.gop.fence();

  general("m,n") = pauli_z("m,k") * pauli_z("k,n");
  std::cout << "σᶻ * σᶻ = \n" << general << "\n";
  world.gop.fence();

  TA::finalize();
  return 0;
}
