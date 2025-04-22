#include <iostream>
#include <tiledarray.h>

int main(int argc, char **argv) {
  // Initialize the parallel runtime
  std::cout << "TA::initialize call." << std::endl;
  TA::World &world = TA::initialize(argc, argv);
  std::cout << "TA initialized." << std::endl;

  // Construct a 2D tiled range structure that defines
  // the tiling of an array. Each dimension contains
  // 10 tiles.
  auto trange = TA::TiledRange{
      TA::TiledRange1{0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100},
      TA::TiledRange1{0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100}};

  // Construct and fill the argument arrays with data
  TA::TArrayD A(world, trange);
  TA::TArrayD B(world, trange);
  A.fill_local(3.0);
  B.fill_local(2.0);
  std::cout << "A and B filled." << std::endl;

  // Construct the (empty) result array.
  TA::TArrayD C;

  // Perform a distributed matrix multiplication
  C("i,j") = A("i,k") * B("k,j");
  std::cout << "Distributed Matrix multiplication is complete." << std::endl;

  // Tear down the parallel runtime.
  std::cout << "TA::finalize call." << std::endl;
  TA::finalize();
  std::cout << "Finalized." << std::endl;
  return 0;
}
