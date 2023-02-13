//
// Created by Mathis Le Roux on 10/02/2023.
//
#include <stdio.h>
#include <time.h>

int pingala_iter(unsigned int a, unsigned int n){
    unsigned int p = 1;
    if (!n)
        return 1; // builtin_clz a on comportement indéfini en 0
    int nb_q = 32 - __builtin_clz(n);
    while(nb_q >= 0){
        p *= p;
        // if(n & (1 << nb_q--)) si on voit le test
        // comme "vérifier si le nb_q ème bit" est à 1
        // sinon test de parité peut-être plus lisible
        // (aucun changement de performance)
        if((n >> nb_q--) % 2)
            p *= a;
    }
    return p;
}


int main(void){
    clock_t t;
    t = clock();
    for(long long int i=0; i<100000000; i++){
        pingala_iter(3, 9);
    }
    t = clock() -t;
    printf("Delta t: %f\n", ((double)t)/CLOCKS_PER_SEC);
    return 0;
}

