#include <stdio.h>
#include <math.h>

int is_prime(int);

enum { MAX_SIZE = 2000 };

int main(void)
{
    int N, arr[MAX_SIZE];
    scanf("%d", &N);
    if (N < 2 || N > MAX_SIZE || !is_prime(N)) {
        return 1;
    }
    for (int j = 0; j < N; j++) {
        arr[1] = j;
        printf("%d ", arr[1]);
        for (int i = 2; i < N; i++) {
            arr[i] = (N - (N / i) * arr[N % i] % N) % N;
            printf("%d ", arr[i]); 
        }
        printf("\n");
    }
    return 0;
}

int
is_prime(int n)
{
    for (int i = 2; i < (int) sqrt((double) n) + 1; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}
