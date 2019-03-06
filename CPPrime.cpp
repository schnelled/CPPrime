/*======================================================================
Program:		CPPrime
Author:			Dustin Schnelle (schnelled)
Date:			March 5th, 2019
Description:	Determines if individual integers from a vector are prime
				with the usage of mutlithreading. Prime integers are
				then stored in the prime number vector, so they can be
				displayed to the user.
======================================================================*/
#include <iostream>			// Standard input and output
#include <vector>			// Vector container (STL container)
#include <thread>			// Threads of execution
#include <mutex>			// Mutual exclusion
#include <algorithm>		// Sorting algorithm

using namespace std;

// Function prototyping
void prime(vector<int> &, int, int,  vector<int> &);

// Global mutex
mutex vectorMutex;

void main(int argc, char* argv[])
{
	// Create an instance of the vector containers
	vector<int> numbers;
	vector<int> primeNumbers;


	// Initialize the vectors with numbers from 1-100
	for (int i = 0; i <= 100; i++) {
		numbers.push_back(i);
	}

	// Display the original vector of numbers
	cout << "Original Numbers: ";
	for (vector<int>::iterator itor = numbers.begin(); itor != numbers.end(); itor++) {
		// Check if last item
		if (numbers.back() == *itor) {
			// Display last number
			cout << *itor << endl << endl;
		}
		else {
			// Display current number
			cout << *itor << ",";
		}
	}

	// Spawn first worker thread that calls prime
	thread t1(prime, ref(numbers), 0, numbers.size() / 2, ref(primeNumbers));
	// Spawn second worker thread that calles prime
	thread t2(prime, ref(numbers), numbers.size() / 2, numbers.size(), ref(primeNumbers));

	// Syncronize the threads
	t1.join();
	t2.join();

	// Sort the vector of prime numbers
	sort(primeNumbers.begin(), primeNumbers.end());

	// Display the prime vector of numbers
	cout << "Prime Numbers: ";
	for (vector<int>::iterator itor = primeNumbers.begin(); itor != primeNumbers.end(); itor++) {
		// Check if last item
		if (primeNumbers.back() == *itor) {
			// Display last number
			cout << *itor << endl;
		}
		else {
			// Display current number
			cout << *itor << ",";
		}
	}

	// Pause the console screen
	cout << "Press any key to exit" << endl;
	cin.get();
}

/*-----------------------------------------------------------------------
Function:		prime
Inputs:			vector<int> &v - Reference to the original vector.
				int begin - Beginning of the range of vector values.
				int end - End of the range of vector values.
				vector<int> &pv - Reference to the vector of prime numbers.
Outputs:		void (None)
Description:	Loops through a range of vector integer values to
				determine if they are prime. If the integer value is
				prime then it's stored in the prime vector.
-----------------------------------------------------------------------*/
void prime(vector<int> &v, int begin, int end, vector<int> &pv)
{
	// Declare and initialize counter variable
	int count = 0;

	// Loop through the range of numbers
	for (int i = begin; i < end; i++) {
		// Check if the number is greater than one
		if (v[i] > 1) {
			// Loop through numbers 1-num
			for (int j = 1; j < v[i]; j++) {
				// Check if num modulo(i) = 0
				if (v[i] % j == 0)
				{
					// Increament the counter
					count++;
				}
				// Check if count is greater than one
				if (count > 1) {
					break;
				}
			}
			// Check if counter is eqaul to one
			if (count == 1) {
				// Lock this section of code
				vectorMutex.lock();
				// Add the prime number to the prime vector
				pv.push_back(v[i]);
				// Unlock this section of code
				vectorMutex.unlock();
			}
		}
		// Reset the count variable
		count = 0;
	}
	// Return from the function
	return;
}