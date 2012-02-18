#define _POSIX_SOURCE

#include <iostream>
#include <cmath>
#include <pthread.h>


#define MAX_VALUE 80  //4294967296
#define NUM_THREADS 4

using namespace std;

struct thread_data{
    int prime;
    int thread_name;
};

struct thread_data thread_data_array[NUM_THREADS];

void *thread_prime(void *thread_args){

    int my_name;
    int my_number;

    struct thread_data *cur_data;
    cur_data = (struct thread_data *) thread_args;
    my_name = cur_data->thread_name;
    my_number = cur_data->prime;

    cout << "I am thread #" << my_name << endl;
    cout << "My number is #" << my_number << endl;

    for(int i = my_number; i < MAX_VALUE; ++i){
        if((i % my_number)==0){
            cout << "I woud set bit # : " << i << endl;    
        }
    }
    pthread_exit(NULL);    
}


int main(){

    cout << "I'm Here! \n";

    int num_nums = MAX_VALUE;
    int rc;
    int t = 0;
    int num_comp = 0;
    int next_num = 2; //first number to start checking 

    int live_threads = 0;

    pthread_t threads[NUM_THREADS];

    unsigned char bitmap[10];
    unsigned char bitmask[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
    while(next_num < 20){
       
        for(t = 0; t < NUM_THREADS; ++t){
            cout << "Stringing thread: " << t << endl;
            thread_data_array[t].thread_name = t;
            thread_data_array[t].prime = next_num;
            next_num++;
            rc = pthread_create(&threads[t],NULL,thread_prime,(void *) &thread_data_array[t]);
            live_threads++;
            sleep(1);
        }
	for(t = 0;t < NUM_THREADS; ++t){
            pthread_join(threads[t], NULL);
            --live_threads;
            cout << "Thread " << t << " has been rejoined. RIP" << endl;
        }
 
    }

return 0;
}
