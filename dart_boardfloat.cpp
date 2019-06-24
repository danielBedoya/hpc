#include <bits/stdc++.h>
using namespace std;

float dart_board(int t){
    float ac = 0.0;
    srand((unsigned long)clock);
    const float fac = 1.0/RAND_MAX;
    for(int i = 0; i < t; i++){
        float x = rand()*fac;
        float y = rand()*fac;
        if(x*x + y*y <= 1)
            ac += 1.0;
    }
    return (4.0*ac)/float(t);    
}

int main(int argc, char *argv[]){
    int t;
    t = argc > 1 ? atoi(argv[1]) : 100000;
    clock_t time = clock();
    float pi = dart_board(t);
    float ans = (float)(clock() - time) / CLOCKS_PER_SEC;
    cout << t <<";"<< fixed << setprecision(10) << pi << ";" << ans << endl;
    return 0;
}