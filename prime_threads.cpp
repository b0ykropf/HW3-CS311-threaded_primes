#define _POSIX_SOURCE

#include <iostream>
#include <cmath>
#include <pthread.h>


#define MAX_VALUE 80  //4294967296
#define NUM_THREADS 2

using namespace std;

void *set_multiples(void *arg){

    for(int i = 2; i < MAX_VALUE; i = i + 2){
        if((i % 2)==0){
            cout << "I woud set bit # : " << i << endl;    
        }
    }
    pthread_exit(NULL);    
}


int main(){

    cout << "I'm Here! \n";

    int num_nums = MAX_VALUE;
    int rc;
    int t;
    int num_comp = 0; 

    pthread_t threads[NUM_THREADS];

    unsigned char bitmap[10];
    unsigned char bitmask[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

    for(t = 0; t < NUM_THREADS; ++t){
        cout << "Stringing thread: " << t << endl;
        rc = pthread_create(&threads[t], NULL, set_multiples, (void*) t);
    }
    for(t = 0; t < NUM_THREADS; ++t){
        pthread_join(threads[t], NULL);
        cout << "Thread " << t << " has been rejoined. RIP" << endl;
    }



return 0;
}
