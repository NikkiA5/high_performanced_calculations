#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size, buf;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_n(MPI_COMM_WORLD, &size);
    
    if(rank == 0) {
        for(int i = 1; i < size; i++) {
            MPI_Recv(&buf, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Master recieved: "<< buf <<  "\n";
        }
    } else {
        buf = rank;
        MPI_Send(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}