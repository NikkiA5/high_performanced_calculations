#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
 
    MPI_Group group;
    MPI_Comm_group(MPI_COMM_WORLD, &group);
    
    MPI_Group_rank(group, &rank);
    MPI_Group_size(group, &size);
 
    std::cout <<"Group: " << group << "Process: " << rank << " out of "<< size << "\n";
 
    MPI_Finalize();
    return 0;
}

