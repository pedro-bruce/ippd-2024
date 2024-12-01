#include <stdio.h>
#include <string.h>
#include <sys/time.h>

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

    return 1 + MIN3(
            // Insert
            levenshteinRecursive(str1, str2, m, n - 1),
 
            // Remove
            levenshteinRecursive(str1, str2, m - 1, n),
 
            // Replace
            levenshteinRecursive(str1, str2, m - 1, n - 1));
}
 
int solve(char* str1, char* str2, int m, int n)
{
    int distance;
    distance = levenshteinRecursive(str1, str2, strlen(str1), strlen(str2));
    
    return distance;
}

// Drivers code
int main() {
    char* str1 = "chicken 123456";
    char* str2 = "kicking 223420";
    // char* str1 = "chicken";
    // char* str2 = "kicking";
 
    // Function Call
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