#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <time.h>

using namespace std;

void zero_init_matrix(int** matrix, int n){
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0 ;
}

int matmul_ijk(int size, int** a, int** b, int** c){
    int i, j, k;
    clock_t t;

    for (unsigned int nthreads = 1; nthreads <= 10; nthreads++){
        
        t = clock();
        #pragma omp parallel num_threads(nthreads) shared(size) private(i,j,k)
        {
        #pragma omp for collapse(3) schedule(static) 
            for (i = 0; i < size; i++){
                for (j = 0; j < size; j++){
                    for (k = 0; k < size; k++){
                        c[i][j] = c[i][j] + a[i][k] * b[k][j];
                        //cout << "Thread: " << omp_get_thread_num() << endl;
                    }
                }
            }
        }

        t = clock() - t;
        cout << "The number of threads: " << nthreads << " Time: " << (double)t / CLOCKS_PER_SEC << endl;
        // cout << "3: " << (double)t / CLOCKS_PER_SEC << endl;
    }
    return 0;
}

int matmul_jki(int size, int** a, int** b, int** c){
    int i, j, k;
    clock_t t;

    for (unsigned int nthreads = 1; nthreads <= 10; nthreads++){
        
        t = clock();
        #pragma omp parallel num_threads(nthreads) shared(size) private(i,j,k)
        {
        #pragma omp for collapse(3) schedule(static) 
            for (j = 0; j < size; j++){
                for (k = 0; k < size; k++){
                    for (i = 0; i < size; i++){
                        c[i][j] = c[i][j] + a[i][k] * b[k][j];
                        //cout << "Thread: " << omp_get_thread_num() << endl;
                    }
                }
            }
        }

        t = clock() - t;
        cout << "The number of threads: " << nthreads << " Time: " << (double)t / CLOCKS_PER_SEC << endl;
        // cout << "3: " << (double)t / CLOCKS_PER_SEC << endl;
    }
    return 0;
}

int matmul_ikj(int size, int** a, int** b, int** c){
    int i, j, k;
    clock_t t;

    for (unsigned int nthreads = 1; nthreads <= 10; nthreads++){
        
        t = clock();
        #pragma omp parallel num_threads(nthreads) shared(size) private(i,j,k)
        {
        #pragma omp for collapse(3) schedule(static) 
            for (i = 0; i < size; i++){
                for (k = 0; k < size; k++){
                    for (j = 0; j < size; j++){
                        c[i][j] = c[i][j] + a[i][k] * b[k][j];
                        //cout << "Thread: " << omp_get_thread_num() << endl;
                    }
                }
            }
        }

        t = clock() - t;
        cout << "The number of threads: " << nthreads << " Time: " << (double)t / CLOCKS_PER_SEC << endl;
        // cout << "3: " << (double)t / CLOCKS_PER_SEC << endl;
    }
    return 0;
}

int main(int argc, char* argv[]){
    int N = atoi(argv[1]);

    int **a = new int* [N];
    int **b = new int* [N];
    int **c = new int* [N];

    for (unsigned int i = 0; i < N; i++)
        a[i] = new int [N];

    for (unsigned int i = 0; i < N; i++)
        b[i] = new int [N];

    for (unsigned int i = 0; i < N; i++)
        c[i] = new int [N];

    for (unsigned int i = 0; i < N; i++){
        for (unsigned int j = 0; j < N; j++){
            a[i][j] = rand() % 100;
            b[i][j] = rand() % 100;
        }
    }

    cout << "IJK" << endl;
    zero_init_matrix(c, N);
    matmul_ijk(N, a, b, c);
    
    cout << "JKI" << endl;
    zero_init_matrix(c, N);
    matmul_jki(N, a, b, c);
    
    cout << "IKJ" << endl;
    zero_init_matrix(c, N);
    matmul_ikj(N, a, b, c);
  
    for (unsigned int i = 0; i < N; i++)
        delete[]a[i];
    delete [] a;

    for (unsigned int i = 0; i < N; i++)
        delete[]b[i];
    delete [] b;

    for (unsigned int i = 0; i < N; i++)
        delete[]c[i];
    delete [] c;


    return 0;
}