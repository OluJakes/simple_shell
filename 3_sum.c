#include <stdio.h>

/**
 * main - Entry point of the program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	/* Declare and initialize three integers */
	int num1 = 22;
	int num2 = 28;
	int num3 = 33;

	/* Calculate the sum of the three numbers */
	int sum = (num1 + num2 + num3);

	/* Print the sum of the numbers */
	printf("The sum of %i, %i and %i is %i\n", num1, num2, num3, sum);

	return (0); /* Exit with success status */
}

