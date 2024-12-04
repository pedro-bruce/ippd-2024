#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MIN3(a, b, c) (MIN(a, MIN(b, c)))


int levenshteinRecursive(char* str1, char* str2, int m, int n) {
    // str1 is empty
    if (m == 0) {
        return n;
    }
    // str2 is empty
    if (n == 0) {
        return m;
    }
 
    if (str1[m - 1] == str2[n - 1]) {
        return levenshteinRecursive(str1, str2, m - 1, n - 1);
    }
    
    int insert, remove, replace;
    #pragma omp task shared(insert) if (m > 5 && n > 5)
    insert = levenshteinRecursive(str1, str2, m, n - 1);
    
    #pragma omp task shared(remove) if (m > 5 && n > 5)
    remove = levenshteinRecursive(str1, str2, m - 1, n);

    #pragma omp task shared(replace) if (m > 5 && n > 5)
    replace = levenshteinRecursive(str1, str2, m - 1, n - 1);

    #pragma omp taskwait
    return 1 + MIN3(insert, remove, replace);
}
 
int solve(char* str1, char* str2, int m, int n)
{
    int distance;
    #pragma omp parallel
        #pragma omp single
            distance = levenshteinRecursive(str1, str2, strlen(str1), strlen(str2));
    
    return distance;
}

int main() {
    // char* str1 = "chicken 123456";
    // char* str2 = "kicking 223420";
    char* str1 = "chicken 1234";
    char* str2 = "kicking 223";

    int distance;
    struct timeval start, stop;

    gettimeofday(&start, NULL);

    distance = solve(str1, str2, strlen(str1), strlen(str2));
    
    gettimeofday(&stop, NULL);
    
    double t = (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000000.0;

    printf("Levenshtein distance: %d\n", distance);
    printf("Time: %fs\n", t);

    return 0;
}
