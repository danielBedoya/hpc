#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int update(int ant, int act, int next){
	if (act==0){
		if (ant==1){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		if (next==1){
			return 1;
		}
		else{
			return 0;
		}
	}
}



int main (int argc, char *argv[]){
	int tam = atoi(argv[1]);        
  	int iterations = atoi(argv[2]);

	int value, cars=0;
    float speed;
    vector<int> vecto (tam);
    vector<int> vecto2 (tam);
    for (int i = 0; i < tam; i++)
    {
        value= rand () % (2);
		vecto[i]= value;
		cars+=value;
	}
    /* for (int i = 0; i < tam; i++)
    {
        printf("%d  ", vecto[i]);
    }
    printf("\n");*/

    std::chrono::steady_clock::time_point _start(std::chrono::steady_clock::now());
    for(int it = 1; it <= iterations; it++){
        speed = 0.0;
        for (int i = 0; i < tam; i++)
        {
            if(i == 0){
                vecto2[i]=update(vecto[tam-1],vecto[0],vecto[1]);
            }
            else if(i == tam-1){
                vecto2[i]=update(vecto[i-1],vecto[i],vecto[0]);
            }
            else{
                vecto2[i]=update(vecto[i-1],vecto[i],vecto[i+1]);
            }
            if(vecto[i]==0 && vecto2[i]==1){
                speed+=1.0;
            }
        }
        printf("%f;", speed / cars);
        /* for (int i = 0; i < tam; i++)
        {
            printf("%d  ", vecto2[i]);
        }
        printf("\n");*/
        vecto=vecto2;
    }
    std::chrono::steady_clock::time_point _end(std::chrono::steady_clock::now());
    std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(_end - _start).count()<<endl;
    return 0;
}
