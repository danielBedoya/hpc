#include <bits/stdc++.h>
#include <random>
#include "mpi.h"

using namespace std;

double pi = 3.14159265;

bool check_intersect(double x, double theta, int l, int s){
    //cout << x << endl;
    //cout << theta << endl;
    if(x + (s/2.0)*sin(theta) >= l)return true;
    if(x - (s/2.0)*sin(theta) <= 0.0)return true;
    return false;
}

int monte_carlo(int t, int l, int s){
    int total = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    int i;
    double x0;
    double theta;
    for(i = 0; i < t; i++){       
        x0 = l*dis(gen);
        theta = pi*dis(gen);
        if(check_intersect(x0,theta,l,s)){
            total += 1.0;
        }
    }
    return total;
}

int main(int argc, char *argv[]){
    int n, t, l, s, rank, size, pi2, pi2total=0, rc;
    double t1, t2, tf;   // number of throws, dist between lines and 
    t = (argc > 1 ? atoi(argv[1]): 100000);
    l = (argc > 2 ? atoi(argv[2]): 30);
    s = (argc > 3 ? atoi(argv[3]): 10);

    t1=MPI_Wtime();
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank==0){
        pi2 = monte_carlo(t-((t/3)*3)+(t/3), l, s);
    }else{
        pi2 = monte_carlo(t/3, l, s);
    }

    rc = MPI_Reduce(&pi2,&pi2total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    MPI_Finalize();
    t2=MPI_Wtime();

    if(rank==0){
	double pi3 = (2.0*s*t)/(l*double(pi2total));
        tf=t2-t1;
        cout << t <<";"<< fixed << setprecision(10) << pi3 << ";" << tf << endl;
    }
    return 0;
}
