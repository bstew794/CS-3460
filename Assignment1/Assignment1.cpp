#include <iostream>
#include <cmath>
#include <string>

// help sites: https://en.cppreference.com/w/


/*
* This function takes in an integer called series that represents the type of nbonacci it is
(Fibonacci = 2, Tribonacci = 3, etc). It also takes in the n of the nth number in the sequence. It then returns
the nth number for the given sequence.
*/
long nbonacci(unsigned int series, unsigned int n)
{
	// according to nbonacci patterns, ensures that n = 1 doesn't try to add n = 0 and n = -1 together.
	if (n < series)
	{
		return 1;
	};
	long nbonacciSum = 0; // This will be the number that the function returns

	// The function looks at the past 1, 2, or 3 numbers (depending on the value of series) and adds it to the sum
	for (int i = n; i > n - series; i--)
	{
		nbonacciSum += nbonacci(series, i - 1); // recursively calls the function on the ith minus one number
	};
	return nbonacciSum; // return the nth number of the given sequence type
};


/*
* This function computes the nbonacci ratio given the series type and title. It then prints the results to the console
*/
void computeNbonacciRatio(std::string title, unsigned int series)
{
	// series is used to kickstart the nbonacci numbers at the point that they are no longer equal to 1
	int numOfIterations = series - 1; // records how many iterations it took to reach the estimated ratio
	int nbonacciPos = series; // records the current nth number of the sequence
	float oldRatio = 1.0; // records the last ratio calculated
	float difference = 1.0; // records the difference between the current ratio and oldRatio
	float differenceMargin = 0.000001; // the margin of difference the ratios must have to end the while loop

	// recalculates the ratio until the difference is less than the differenceMargin
	while (difference > differenceMargin)
	{
		//This is calculated by dividing the nbonacci number of nbonacciPos over the previous nbonacci number
		float newRatio = static_cast<float>(nbonacci(series, nbonacciPos)) / \
			static_cast<float>(nbonacci(series, nbonacciPos - 1));

		// calculate the dfference between the current ratio and the last ratio
		difference = abs(newRatio - oldRatio);
		oldRatio = newRatio;

		nbonacciPos++; // increase postion of pointer in sequence by one
		numOfIterations++; //increase count of iterations taken
	};
	// prints out the ratio found along with how many iterations it took
	std::cout << title + " ratio approaches " + std::to_string(oldRatio) + " over " \
		+ std::to_string(numOfIterations) + " iterations\n";
};


/*
* This is the driver function of the program, it uses nbonacci() and calculateNbonacciRatio() to find 20 numbers for
* nbonacci sequences 2 through 5. It also calculates the nbonacci ratios for all of them and displays the results 
to the console
*/
int main()
{
	// setting up the titles since they are used more than once
	std::string fibTitle = "Fibonacci";
	std::string triTitle = "Tribonacci";
	std::string fourTitle = "Fourbonacci";
	std::string fiveTitle = "Fivebonacci";

	int startPos = 0; // start of the sequence
	int endPos = 19; // nth number of the sequence to stop on

	int fibSeries = 2; // initlizes series variable for particular sequence
	
	std::cout << "--- " + fibTitle + " --- \n"; // prints out title

	// iters from n = 0 to n = 19
	for (int i = startPos; i < endPos; i++)
	{
		std::cout << std::to_string(nbonacci(fibSeries, i)) + " "; // prints result of ith nbonacci number
	}
	std::cout << std::to_string(nbonacci(fibSeries, endPos)) + "\n"; // this is here to add a new line

	int triSeries = 3;

	std::cout << "--- " + triTitle + " --- \n";

	for (int i = startPos; i < endPos; i++)
	{
		std::cout << std::to_string(nbonacci(triSeries, i)) + " ";
	}
	std::cout << std::to_string(nbonacci(triSeries, endPos)) + "\n";

	int fourSeries = 4;

	std::cout << "--- " + fourTitle + " --- \n";

	for (int i = startPos; i < endPos; i++)
	{
		std::cout << std::to_string(nbonacci(fourSeries, i)) + " ";
	}
	std::cout << std::to_string(nbonacci(fourSeries, endPos)) + "\n ";

	int fiveSeries = 5;

	std::cout << "--- " + fiveTitle + " --- \n";

	for (int i = startPos; i < endPos; i++)
	{
		std::cout << std::to_string(nbonacci(fiveSeries, i)) + " ";
	}
	std::cout << std::to_string(nbonacci(fiveSeries, endPos)) + "\n";

	std::cout << "\n"; // a new line makes the division between sequences and ratios more visible

	// calculate all the ratios

	computeNbonacciRatio(fibTitle, fibSeries);
	computeNbonacciRatio(triTitle, triSeries);
	computeNbonacciRatio(fourTitle, fourSeries);
	computeNbonacciRatio(fiveTitle, fiveSeries);

	return 0; // returns status code and ends the program
};