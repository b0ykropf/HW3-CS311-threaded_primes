#define _POSIX_SOURCE
#include <bitset> //so we have bitset operations
#include <iostream>
#include <cmath>
#include <pthread.h>


#define MAX_VALUE 51  //4294967296
#define NUM_THREADS 2

using namespace std;

void *set_multiples(){
    for(int i = 3; i < MAX_VALUE; i++){
        if((i%2)==0){
            prime_map.set(i);
        }
    }    
}


int main(){

    cout << "I'm Here! \n";

    int num_nums = MAX_VALUE;
    int rc;
    int t; 

    bitset<MAX_VALUE> prime_map;

    pthread_t threads[NUM_THREADS];

    for(t = 0; t < NUM_THREADS; t++){
        cout << "Stringing thread: " << t << endl;
        rc = pthread_create(&threads[t], NULL, set_multiples, NULL);
    }


    cout << "Prime Map : " << prime_map << endl;
    cout << "Number of disqualified integers : " << prime_map.count() << endl;
    cout << "Current Potential Primes : " << ~prime_map << endl;


















return 0;
}
