#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]){
    int N = atoi(argv[1]);
    int* v = new int[N];
    clock_t start, finish;

    for(long unsigned i = 0; i < N; i++)
        v[i] = rand() % 1000;

    int max_val = v[0];


    // for(long unsigned i = 0; i < N; i++)
    //     cout << v[i] << ' ';
    // 
    // cout << endl;

    // nthread - the number of threads
    for(unsigned int nthreads = 1; nthreads <= 10; nthreads++){
        start = clock();

        #pragma omp parallel for reduction(max:max_val) num_threads(nthreads)
            for (long unsigned i = 0; i < N; i++){
                max_val = max_val > v[i] ? max_val : v[i];
                //cout << "The max elem in the thread " << omp_get_thread_num() << ' ' << max_val << endl;
            }

        finish = clock();

        cout << "The number of threads: " << nthreads << endl;
        cout << "The execution time: " << (double(finish - start) / CLOCKS_PER_SEC) << endl;
    }

    cout << "Max element: " << max_val << endl;
    
    return 0;
}