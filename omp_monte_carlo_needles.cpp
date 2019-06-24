#include <bits/stdc++.h>
#include <random>
#include <omp.h>
using namespace std;

double pi = 3.14159265;

bool check_intersect(double x, double theta, int l, int s){
    //cout << x << endl;
    //cout << theta << endl;
    if(x + (s/2.0)*sin(theta) >= l)return true;
    if(x - (s/2.0)*sin(theta) <= 0.0)return true;
    return false;
}

double monte_carlo(int t, int l, int s){
    double total = 0.0;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    int i;
    double x0;
    double theta;
    #pragma omp parallel for private(i,x0,theta) shared(total)
    for(i = 0; i < t; i++){       
        x0 = l*dis(gen);
        theta = pi*dis(gen);
        if(check_intersect(x0,theta,l,s)){
            #pragma omp atomic update
            total += 1.0;
        }
    }
    return (2.0*s*t)/(l*total);
}

int main(int argc, char *argv[]){
    int n, t, l, s;   // number of throws, dist between lines and 
    t = (argc > 2 ? atoi(argv[2]) : 100000);
    l = (argc > 3 ? atoi(argv[3]) : 30);
    s = (argc > 4 ? atoi(argv[4]) : 10);
    clock_t time = clock();
    double pi2 = monte_carlo(t, l, s);
    double ans = (double)(clock() - time) / CLOCKS_PER_SEC;
    cout << pi2 << ";" << ans << endl;
    return 0;
}