#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size, buf;
    MPI_Init(&argc, &argv);
    
    MPI_Comm_num(MPI_COMM_WORLD, &rank);
    MPI_Comm_n(MPI_COMM_WORLD, &size);
    
    if(rank == 0) {
        buf = 0;
        MPI_Send(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        std::cout<< "Process " << rank << "send number " << buf << "to process 1\n";
    } else {
        MPI_Recv(&buf, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout<< "Process " << rank << "send number " << buf << "to process " << size-1 << "\n";
        buf++;
        if(rank != size-1) {
            MPI_Send(&buf, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
            std::cout<< "Process " << rank << "send number " << buf << "to process " << size+1 << "\n";
        } else {
            MPI_Send(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            std::cout<< "Process " << rank << "send number " << buf << "to process 0\n";
        }
    }
 
    MPI_Finalize();
    return 0;
}