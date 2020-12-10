#include "solution.h"
#include <sstream>
#include "Utils.h"
#include <iostream>


solution::solution(int _numberOfBits, int low, int high) : nNumberOfBits(_numberOfBits), nLow(low), nHigh(high) //this initializes automatically the values
{
	nBits.reserve(_numberOfBits); // we do this to avoid relocate the vector
	for (size_t i = 0; i < _numberOfBits; i++)
	{
		nBits.push_back(rand() % 2); //random number from 0 -1 
	}
}

solution::solution(int _numberOfBits, int low, int high, std::vector<int> bits) : nNumberOfBits(_numberOfBits), nLow(low), nHigh(high),
nBits(bits)
//this initializes automatically the values
{

}

//to return the solution decoded /to print the solution 
std::string solution::toString() const
{
	std::ostringstream stream;
	stream << "[";
	for (int bit : nBits)
	{
		stream << bit << " ";
	}
	stream << "] double = " << bitsToDouble() << " fitness = " << fitness();
	return stream.str();
}

// f(x) = x+2 * sin(x) current function to practice 
double solution::fitness() const
{
	double x = bitsToDouble();
	return x + 2 * sin(x);

}

//00110001 => double?

double solution::bitsToDouble() const
{
	double prec = precision(nLow, nHigh, nNumberOfBits);
	int dec = 0;
	for (int i = 0; i < nNumberOfBits; i++)
	{
		dec = dec + pow(2, i) * nBits[i];		//conversion from base 2 to base 10
	}
	return dec * prec + nLow;
}

std::vector<solution> solution::singlePointCrossover(solution Other, double CrossoverProbability)
{

	bool cross = randomProbability(CrossoverProbability);
	//std::cout << "Crossed ? -> " << cross;
	if (cross)
	{
		int crossPoint = rand() % nNumberOfBits;

		std::vector<int> bits1;
		std::vector<int> bits2;

		std::copy(this->nBits.begin(), this->nBits.begin() + crossPoint,
			std::back_inserter(bits1));
		std::copy(Other.nBits.begin() + crossPoint, Other.nBits.end(),
			std::back_inserter(bits1));

		std::copy(Other.nBits.begin(), Other.nBits.begin() + crossPoint,
			std::back_inserter(bits2));
		std::copy(this->nBits.begin() + crossPoint, this->nBits.end(),
			std::back_inserter(bits2));


		solution child1{ nNumberOfBits , nLow , nHigh , bits1 };

		solution child2{ nNumberOfBits , nLow , nHigh , bits2 };


		return {child1 , child2};
	}
	else
	{
		return { *this , Other };
	}

}

//performs mutations to the chromosomes
void solution::Mutate(double mutationProbability)
{
	//std::cout << "\nBefore mutation " << this->toString() << "\n";
	for (int i = 0; i < nNumberOfBits; i++) {
		bool mutateBool = randomProbability(mutationProbability);
		if (mutateBool)
		{
			nBits[i] = 1 - nBits[i]; //flips
			//std::cout << "[Mutated]\n";
		}
	}

	//std::cout << "After mutation " << this->toString() << "\n";
}

