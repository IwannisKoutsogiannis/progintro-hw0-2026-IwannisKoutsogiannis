#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LIMIT 10000000000ULL

bool is_prime(unsigned long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (unsigned long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    while (1) {
        printf("Give me a number: ");
        
        unsigned long long n;
        char buffer[256];
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("EOF detected, exiting\n");
            return 0;
        }
        
        char *endptr;
        unsigned long long parsed_n = strtoull(buffer, &endptr, 10);
        
        if (*endptr != '\n' && *endptr != '\r' && *endptr != '\0') {
            fprintf(stderr, "Invalid input: expected an integer\n");
            return 1;
        }
        if (endptr == buffer) {
            fprintf(stderr, "Invalid input: expected an integer\n");
            return 1;
        }
        
        n = parsed_n;
        
        if (n > MAX_LIMIT) {
            fprintf(stderr, "Number should be in the range [0, 10000000000]\n");
            return 1;
        }
        
        printf("Choose how to test %llu - ('p' for prime, 'g' for goldbach) ", n);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("EOF detected, exiting\n");
            return 0;
        }
        
        char opt;
        if (sscanf(buffer, " %c", &opt) != 1) {
            fprintf(stderr, "Invalid choice: expected 'p' or 'g'\n");
            return 1;
        }
        
        if (opt != 'p' && opt != 'g') {
            fprintf(stderr, "Invalid choice: expected 'p' or 'g'\n");
            return 1;
        }
        
        if (opt == 'p') {
            if (is_prime(n)) {
                printf("%llu is prime\n", n);
            } else {
                printf("%llu is not prime\n", n);
            }
        } else if (opt == 'g') {
            if (n <= 2 || n % 2 != 0) {
                printf("Goldbach's conjecture is applicable only to even numbers greater than 2!\n");
                continue;
            }
            
            for (unsigned long long p = 2; p <= n / 2; p++) {
                if (is_prime(p) && is_prime(n - p)) {
                    printf("%llu = %llu + %llu\n", n, p, n - p);
                    break;
                }
            }
        }
    }

    return 0;
}