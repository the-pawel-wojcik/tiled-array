#include <tiledarray.h>

int main(int argc, char *argv[]) {
  // Initialize MPI
  int thread_level_provided;
  MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &thread_level_provided);
  assert(MPI_THREAD_MULTIPLE == thread_level_provided);

  // create a communicator spanning even ranks only
  int me;
  MPI_Comm_rank(MPI_COMM_WORLD, &me);
  MPI_Comm comm_evens;
  MPI_Comm_split(MPI_COMM_WORLD, (me % 2 ? MPI_UNDEFINED : 0), 0, &comm_evens);

  // Initialize TiledArray on even ranks only
  if (comm_evens != MPI_COMM_NULL) {
    auto &world = TA::initialize(argc, argv, comm_evens);

    // Do some work here.

    // Finalize TiledArray
    TA::finalize();
  }

  // must finalize MPI since we initialized it ourselves
  MPI_Finalize();

  return 0;
}
