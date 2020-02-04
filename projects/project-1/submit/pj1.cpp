/*
Algorithm (for P_i)
sum = add local N / P numbers
for j = 0 to d-1 {
  if ((rank AND 2^j)!= 0) {
    send sum to (rank XOR 2^j);
    exit;
  }
  else {
    receive sum' from (rank XOR 2^j);
    sum = sum + sum';
  }
}
if (rank == 0)
print sum;
*/

#include <mpi.h>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
  // set up MPI
  MPI_Init(&argc, &argv);

  // get communicator size and my rank
  MPI_Comm comm = MPI_COMM_WORLD;
  int proc_id, num_procs;
  MPI_Comm_size(comm, &num_procs);
  MPI_Comm_rank(comm, &proc_id);

  //broadcast
  int buff[2];
  buff[0] = atoi(argv[1]);
  buff[1] = atoi(argv[2]);
  MPI_Bcast(&buff, 2, MPI_INT, 0, MPI_COMM_WORLD);
  int n = buff[0];
  long int seed = buff[1];

  //start a timer
  double time_start = MPI_Wtime();
  //get the amount of numbers for the current processor
  int local_nums = n / num_procs;
  if ( proc_id < n % num_procs) local_nums++;

  // add local sum
  double local_sum = 0;
  srand48(proc_id + seed);
  //printf(" seed:%li \n",proc_id + seed);
  for (int i = 0; i < local_nums; i++){
    double temnp = drand48();
    local_sum += temnp;
    //printf("%f\n",temnp);
  }

  //send or receive
  double recNum;
  MPI_Status stat;

  for (int j = 0; j < log2(num_procs); j++){

      int dest = proc_id^(int)pow(2, j);

      if ((proc_id & (int)pow(2, j)) != 0){
        MPI_Send(&local_sum, 1, MPI_DOUBLE, dest, 1, comm);

        //printf(" %i/%i send %f to %i.\n", proc_id, num_procs, local_sum, dest);
        MPI_Finalize();
        return 0;
      }else{
        MPI_Recv( &recNum, 1, MPI_DOUBLE, dest, 1, comm, &stat);
        local_sum += recNum;
      }

  }

  // check if it is master process
  double time_end = MPI_Wtime();
  if (proc_id == 0){
    printf("The total sum is %f and running time is %f.\n", local_sum, time_end - time_start);
  }

  // finalize MPI
  MPI_Finalize();
  return 0;
}
