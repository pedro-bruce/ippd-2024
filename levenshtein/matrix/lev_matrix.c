#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void printMatrix(int **dp, int m, int n)
{
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++)
			printf("%d ", dp[i][j]);
		printf("\n");
	}
}

int levenshteinFullMatrix(char* str1, char* str2) {
    int m = strlen(str1);
    int n = strlen(str2);
 
    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
    }
 
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
 
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
 
    for (int i = 1; i <= m; i++) {
       // printf("i: %d\n", i);
	   for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = 1 + MIN(
                            // Insert
                            dp[i][j - 1],
                            MIN(
                                // Remove
                                dp[i - 1][j],
                                // Replace
                                dp[i - 1][j - 1]));
            }
	       // printf("%d ", dp[i][j]);
        }
	   // printf("\n");
    }
 
    //printMatrix(dp, m+1, n+1);

    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return dp[m][n];
}

// Drivers code
int main() {
    // char *str1 = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
    // char *str2 = "zyxwvutsrqponmlkjihgfedcbaabcdefghijklmnopqrstuvwxyz";
    // char *str1 = "chicken";
    // char *str2 = "kicking";
    // char *str1 = "chicken123abcghi";
    // char *str2 = "kicking456defjkl";
    char *str1 = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqr";
    char *str2 = "zyxwvutsrqponmlkjihgfedcbaabcdefghijklmnopqr";
    
    // Strings de 10 mil caracteres (grande volume de trabalho)
    /*
    char *str1 = (char *)malloc(101);
    char *str2 = (char *)malloc(101);
    for (int i = 0; i < 100; i++)
    {
        str1[i] = 'a' + (i % 26); // "abcdefghijklmnopqrstuvwxyz..."
        str2[i] = 'z' - (i % 26); // "zyxwvutsrqponmlkjihgfedcba..."
    }
    str1[100] = '\0';
    str2[100] = '\0';
    */

    clock_t start = clock();
    int distance = levenshteinFullMatrix(str1, str2);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Levenshtein distance: %d\n", distance);
    printf("Time: %f\n", time_spent);

    return 0;
}
