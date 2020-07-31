#include "Solutions.cpp"

int main()
{
	Solutions solutions;
	std::vector<int> input = { 1,15,7,9,2,5,10 };

	std::cout << solutions.maxSumAfterPartitioning(input, 3);
	


	return 0;
}