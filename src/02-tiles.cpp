#include <TiledArray/fwd.h>
#include <algorithm>
#include <concepts/concepts.hpp>
#include <tiledarray.h>

// Helper for what's to come, skip for now to main
auto make_tile(const TA::Range &range, const double value = 0.0) {
  // create a tile
  TA::TArrayD::value_type tile(range);
  // zero it
  std::fill(tile.begin(), tile.end(), value);
  // send it back
  return tile;
}

int main(int argc, char **argv) {
  TA::World &world = TA::initialize(argc, argv);

  // Two tilings for the range [0, 10).
  // Both consisting of three tiles.
  TA::TiledRange1 tr0{0, 3, 8, 10};
  TA::TiledRange1 tr1{0, 4, 7, 9};

  // The above tilings are used to build a bigger tiling
  TA::TiledRange tr{
      tr0,
      tr1,
  };

  // It seems like intialization must be postponed
  TA::TArrayD dense_array(world, tr);
  for (auto it : dense_array) {
    // build a tile, again, no values assigned yet
    auto tile = decltype(dense_array)::value_type(
        dense_array.trange().make_tile_range(it.index()));

    std::fill(tile.begin(), tile.end(), 0.0);

    it = tile;
  }

  // The above is common; there is a member function which does the same thign
  TA::TArrayD dense_zeros(world, tr);
  dense_zeros.fill(0.0);

  // The first example would be parallelized over MPI
  // To get it threded in each process, watch this
  TA::TArrayD quicly_initialized(world, tr);
  for (auto it : quicly_initialized) {
    auto tile = world.taskq.add(
        &make_tile, quicly_initialized.trange().make_tile_range(it.index()),
        1.0);
    it = tile;
  }

  std::cout << "zeros = " << dense_array << "\n\n" << std::flush;

  TA::finalize();
  return 0;
}
