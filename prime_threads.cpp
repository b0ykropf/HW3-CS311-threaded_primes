#define _POSIX_SOURCE

#include <iostream>
#include <cmath>
#include <pthread.h>


#define MAX_VALUE 81  //4294967296
#define NUM_THREADS 4

using namespace std;

long bits_set = 0;
unsigned char bitmap[10];
unsigned char bitmask[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

struct thread_data{
    int prime;
    int thread_name;
};

struct thread_data thread_data_array[NUM_THREADS];

void *thread_prime(void *thread_args){

    int my_name;
    int my_number;
    int seek_byte;
    int seek_bit;
    struct thread_data *cur_data;
    cur_data = (struct thread_data *) thread_args;
    my_name = cur_data->thread_name;
    my_number = cur_data->prime;
    cout << "I am thread #" << my_name << endl;
    cout << "My number is #" << my_number << endl;

    for(int i = my_number + my_number; i < MAX_VALUE; i += my_number){
           cout << "Thread #" << my_name << " would set bit # : " << i << endl;
           seek_byte = i / 8;
           seek_bit = i % 8;
           bitmap[seek_byte] |= bitmask[seek_bit];
           ++bits_set;    
        
    }
    pthread_exit(NULL);    
}


int main(){

    cout << "I'm Here! \n";

    unsigned long num_nums = MAX_VALUE;
    int rc;
    int t = 0;
    int num_comp = 0;
    int next_num = 2; //first number to start checking 

    int live_threads = 0;

    pthread_t threads[NUM_THREADS];

    while(next_num < 6){
       
        for(t = 0; t < NUM_THREADS; ++t){
            cout << "Stringing thread: " << t << endl;
            thread_data_array[t].thread_name = t;
            thread_data_array[t].prime = next_num;
            ++next_num;
            rc = pthread_create(&threads[t],NULL,thread_prime,(void *) &thread_data_array[t]);
            ++live_threads;
        }
	for(t = 0;t < NUM_THREADS; ++t){
            pthread_join(threads[t], NULL);
            --live_threads;
            cout << "Thread " << t << " has been rejoined. RIP" << endl;
        }
 
    }

if(bitmap[1] & bitmask[4]){
    cout << "Bit # 4 has been set" << bitmap[1] << endl; 
}
cout << "bits_set " << bits_set << endl;
return 0;
}
