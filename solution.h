#pragma once

#include <vector>
#include <string>

//the solution class will wrap around the bits
class solution
{
public:
	solution(int numberBits , int low = 0 , int high = 10);
	solution(int numberBits, int low, int high , std::vector<int> bits );
	std::string toString() const;
	double fitness() const;
	std::vector<solution> singlePointCrossover(solution Other, double CrossoverProbability);
	void Mutate(double mutationProbability);

private:
	double bitsToDouble() const ;
	int nNumberOfBits , nLow , nHigh;
	std::vector<int> nBits; //chromosomes
	



};



