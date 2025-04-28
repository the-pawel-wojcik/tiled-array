#include "pauli.hpp"


namespace Pauli {

TA::TArrayZ get_empty_2x2(TA::World & world) {
  int argc = 1;
  char **argv = nullptr;
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
  return TA::TArrayZ(world, trange);
}

TA::TArrayZ get_x(TA::World &world) {
  TA::TArrayZ pauli_matrix = get_empty_2x2(world);

  auto it = begin(pauli_matrix);
  TA::Tensor<cmplx> tile(pauli_matrix.trange().make_tile_range(it.index()));
  tile[0] = cmplx{0.0, 0.0};
  tile[1] = cmplx{1.0, 0.0};
  tile[2] = cmplx{1.0, 0.0};
  tile[3] = cmplx{0.0, 0.0};
  *it = tile;

  return pauli_matrix;
}

TA::TArrayZ get_y(TA::World &world) {
  TA::TArrayZ pauli_matrix = get_empty_2x2(world);

  auto it = begin(pauli_matrix);
  TA::Tensor<cmplx> tile(pauli_matrix.trange().make_tile_range(it.index()));
  tile[0] = cmplx{0.0, 0.0};
  tile[1] = cmplx{0.0, -1.0};
  tile[2] = cmplx{0.0,  1.0};
  tile[3] = cmplx{0.0, 0.0};
  *it = tile;

  return pauli_matrix;
}


TA::TArrayZ get_z(TA::World &world) {
  TA::TArrayZ pauli_matrix = get_empty_2x2(world);

  auto it = begin(pauli_matrix);
  TA::Tensor<cmplx> tile(pauli_matrix.trange().make_tile_range(it.index()));
  tile[0] = cmplx{1.0, 0.0};
  tile[1] = cmplx{0.0, 0.0};
  tile[2] = cmplx{0.0, 0.0};
  tile[3] = cmplx{-1.0, 0.0};
  *it = tile;

  return pauli_matrix;
}
} // namespace Pauli
