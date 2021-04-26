#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {

    int rank, size, buffer;
    buffer = rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Request request[size];
    MPI_Status status[size];

    for(int i = 0; i < size; i++) {
        if(i != rank) {
            MPI_Isend(&buffer, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &request[i]);
            std::cout<< "Process " << rank << "send number " << buffer << "to process " << i << "\n";
        }
    }
    MPI_Waitall(size-1, request, status);

    for(int i = 0; i < size; i++) {
        if(i != rank) {
            MPI_Irecv(&buffer, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &request[i]);
            std::cout<< "Process " << rank << "send number " << buffer << "to process " << i << "\n";
        }
    }
    MPI_Waitall(size-1, request, status);

    MPI_Finalize();
    return 0;
}