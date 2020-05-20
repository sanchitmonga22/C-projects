/* prime-number finding program
Originally by Norman Matloff, UC Davis
http://wwwcsif.cs.ucdavis.edu/~davis/40/gdb_Tutorial.htm
Modified by Mark Ardis, RIT, 11/1/2006

Will report a list of all primes which are less than
or equal to the user-supplied upper bound.
WARNING: There are bugs in this program! */

#include <stdio.h>

int Prime[15];  /* Prime[i] will be 1 if i is prime, 0 otherwise */
int UpperBound; /* check all numbers up through this one for primeness */

void CheckPrime(int upper_bound, int Prime[]) {
  int prime_number;// starting from the smallest prime number

  /* the plan:  see if prime numbers starting from 2 divides the given upperbound, for all values prime_number which are
  themselves prime (no need to try prim_number if it is nonprime), and
  less than or equal to sqrt(upperbound) (if  has a divisor larger
  than this square root, it must also have a smaller one,
  so no need to check for larger ones) */
  prime_number = 2;// starting from the smallest prime number that is 2
  while (prime_number*prime_number<=upper_bound) {
    if (Prime[prime_number] == 1){
      if (upper_bound % prime_number == 0)  {
        Prime[upper_bound] = 0;
        return;
      } /* if (K % J == 0) */
    } /* if (Prime[J] == 1) */
    prime_number++;
  } /* while (1) */
  
  /* if we get here, then there were no divisors of K, so it is prime */
  Prime[upper_bound] = 1;
  
}  /* CheckPrime() */

int main() {
  int i;// pointer for the array of integers
  printf("Enter upper bound:\n");// Asking user for the upperbound
  scanf("%d",&UpperBound);// taking the user input in the UpperBound
  Prime[1] = 1;// number 1 is prime
  Prime[2] = 1;// number 2 is prime
  printf("2 is a prime\n");// prints 2 is a prime number
  for (i = 3; i <= UpperBound; i += 2) {
    CheckPrime(i, Prime);// invoking the CheckPrime function to check whether it is prime 
    if (Prime[i]) {
      printf("%d is a prime\n", i);// prints prime numbers starting from 3
    } /* if (Prime[i]) */
  } /* for (i = 3; i <= UpperBound; i += 2) */
  return 0;
} /* main() */
