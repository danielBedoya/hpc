#include <bits/stdc++.h>
#include <mpi.h>

using namespace std;

int dart_board(int t){
    int ac = 0.0;
    srand((unsigned long)clock);
    const double fac = 1.0/RAND_MAX;
    for(int i = 0; i < t; i++){
        double x = rand()*fac;
        double y = rand()*fac;
        if(x*x + y*y <= 1)
            ac += 1.0;
    }
    return ac;    
}

int main(int argc, char *argv[]){
    int t, size, rank, ac, actotal, rc;
    double t1, t2,tf;
    
    t = argc > 1 ? atoi(argv[1]) : 100000;
    t1=MPI_Wtime();
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank==0){
        ac = dart_board((t/3)+(t-(3*(t/3))))
    }else{
        ac = dart_board(t/3);
    }

    rc = MPI_Reduce(&ac, &actotal, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Finalize();
    
    if(rank==0){
        double pi = (4.0*actotal)/double(t);
        t2=MPI_Wtime();
        tf=t2-t1;
        cout << t <<";"<< fixed << setprecision(10) << pi << ";" << tf << endl;
    }
    return 0;
}