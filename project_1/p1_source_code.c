#include <stdio.h>
#include <string.h>
#include <time.h>
#define LEN 30
clock_t start, stop; /* record the start time and stop time of the function */
double total; /* records the run time (seconds) of a function */
double simple_compute(double x, int power); /* Algorithm 1 */
double recursive_compute(double x, int power); /* Algorithm 2: recursive vision */
double iterative_compute(double x, int power); /* Algorithm 2: iterative vision */
int main()
{

	int i, iteration, power, quit = 0; /*quit marks whether the program should end*/
	double x;
	double(*compute)(double x, int power); /* record the selected algorithm */
	char next_move[20];
	printf("Hello! This is a program to compute power functions.\n==================\n");
	while (!quit) {
		printf("Choose the algorithm you want to use:\n1)Algorithm 1\n2)Algorithm 2:recursive vision\n3)Algorithm 2:interative vision\n");
		gets(next_move); /* get order from the user*/
		if (strcmp(next_move, "quit")) { /* check whether 'quit' is entered */
			if (next_move[0] >= '1'&&next_move[0] <= '3') { /* check whether the input is valid */
				printf("Algorithm selected!\n");
				while (1){
					x = iteration = power = 0; /* parameters initialize */
					printf("Enter parameters in format:X POWER(N) LITERATION(K)\n");
					scanf("%lf %d %d", &x, &power, &iteration);
					getchar();
					if (x && iteration && power) { /* check whether the input is valid */
						break;
					}
					else {
						printf("Invalid input! Please try again \n"); 
					}
				}
				printf("Calculating...\n");
				if (next_move[0] == '1') {
					compute = &simple_compute;
				}
				else if (next_move[0] == '2') {
					compute = &recursive_compute;
				}
				else {
					compute = &iterative_compute;
				}
				start = clock(); /* records the ticks at the beginning of the function call */
				for (i = 0;i < iteration;i++) {
					(*compute)(x, power);
				}
				stop = clock(); /* records the ticks at the end of the function call */
				total = ((double)(stop - start)) / CLK_TCK; /* CLK_TCK is a built-in constant = ticks per second */
				printf("Completed! iteration = %d, ticks = %d, total time = %lfsec, duration = %lfsec\n",iteration,stop - start,total,total/iteration);
				

			}
			else {
				printf("Invalid input! Please try again \n");
			}
		}
		else {
			quit = 1;
		}
		printf("==================\n");
	}
	return 1;
}


double simple_compute(double x, int power) {
	int i;
	double result = 1;
	for (i = 0;i < power;i++) {
		result *= x;
	}
	return result;
}


double recursive_compute(double x, int power) {
	double temp;
	if (power) {
		temp = recursive_compute(x, power / 2);
		if (power % 2) {
			return x * temp * temp;
		}
		else {
			return temp * temp;
		}
	}
	else {
		return 1;
	}
}
double iterative_compute(double x, int power) {
	double result = x;
	int i = 0, a[LEN]; /* this array records the remainder in each divison */
	/* continuously divide power to get the remainders */
	while (power > 1) {
		a[i] = power % 2;
		power /= 2;
		i++;
	}
	/* get the final result according to the remainders in each step */
	while (i > 0) {
		i--;
		if (a[i]) {
			result *= result * x;
		}
		else {
			result *= result;
		}
	}
	return result;
}
