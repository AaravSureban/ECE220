#include <stdlib.h>
#include <stdio.h>

/*
 * This program identifies and prints all semiprimes within a given range [a, b]. A semiprime is a number where
 *  its product is exactly two prime numbers.
 * 
 * There were three errors in the original code for this file:
 * 1. is_prime would return 0 when it exited its for loop, which only happened if the number was actually prime.
 *      This led to the function to return the wrong value if the number was prime, which was fixed by changing the 
 *      return value from 0 to 1. 
 * 2. In print_semiprimes, `k = i % j;` should have been `k = i / j' to find the other factor of i. The modulus operation
 *      led the function to check if the remainder between i and j was prime instead of the other factor of i. 
 * 3. After finding a valid semiprime number, the function would continue to check if the same number was semiprime
 *      as it never broke out of the loop, causing duplicate values to be printed for some numbers. This waas fixed by 
 *      adding a break statement as soon as a semiprime number was found.
*/

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1 || number == 0) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
                        ret = 1;
                        break;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
