#include "Solutions.cpp"

int main()
{
	Solutions solutions;
	std::vector < int > nums = { 1,3,-1,-3,5,3,6,7 };
	int k = 3;
	std::vector<double> ans = solutions.medianSlidingWindow(nums, k);
	for (int i = 0; i < ans.size(); i++)
		std::cout << ans.at(i) << ' ';

	return 0;
}