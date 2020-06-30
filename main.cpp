#include "Solutions.cpp"

int main()
{
	Solutions solutions;
	std::vector < int > nums = { 3,1,3,4,2 };
	int ans = solutions.findDuplicate(nums);
	

	std::cout << ans << std::endl;

	return 0;
}
