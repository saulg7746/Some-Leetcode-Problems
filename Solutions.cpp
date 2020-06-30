#include "utilities.h"
#ifndef SOLUTIONS_CPP
#define SOLUTIONS_CPP


class Solutions {
public:

	/*				Maximum Points You Can Obtain from Cards
	There are several cards arranged in a row, and each card has an associated number of points The points are given in the integer array cardPoints.
	In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.
	Your score is the sum of the points of the cards you have taken.
	Given the integer array cardPoints and the integer k, return the maximum score you can obtain.
		Input: cardPoints = [1,2,3,4,5,6,1], k = 3
		Output: 12
	*/
	int maxScore(std::vector<int>& cardPoints, int k) {
		if (k == 1)
			if (cardPoints.front() > cardPoints.back())
				return cardPoints.front();
			else
				return cardPoints.back();
		else
		{
			std::vector<int> leftArray = std::vector<int>(cardPoints.begin() + 1, cardPoints.end());
			int newK = k - 1;
			int left = maxScore(leftArray, newK) + cardPoints.front();
			std::vector<int> rightArray = std::vector<int>(cardPoints.begin(), cardPoints.end() - 1);
			int right = maxScore(rightArray, newK) + cardPoints.back();
			if (left > right)
				return left;
			else
				return right;
		}
	}

	/*				Minimum Swaps to Make Strings Equal
	You are given two strings s1 and s2 of equal length consisting of letters "x" and "y" only.
	Your task is to make these two strings equal to each other. You can swap any two characters that belong to different strings,
	which means: swap s1[i] and s2[j]

	Input: s1 = "xxyyxyxyxx", s2 = "xyyxyxxxyx"
	Output: 4

	*/
	int minimumSwap(std::string s1, std::string s2) {
		if (s1.length() != s2.length())
			return -1;
		if (s1 == s2)
			return 0;
		std::string subS1 = "";
		int numY = 0;
		int numX = 0;
		std::string subS2 = "";
		int count = 0;
		for (int i = 0; i < s1.length(); i++)
		{
			if (s1[i] != s2[i])
			{
				subS1 += (s1[i]);
				subS2 += (s2[i]);
				if (s1[i] == 'x')
					numX++;
				if (s2[i] == 'y')
					numY++;
			}
		}
		if (numX != numY)
			return -1;
		if (subS1.length() % 2 != 0)
			return -1;
		s1.clear();
		s2.clear();
		for (int i = 0; i < subS1.length(); i++)
			if (i < numX)
				s1 += 'x';
			else
				s1 += 'y';


		for (int i = 0; i < subS2.length(); i++)
			if (i < numY)
				s2 += 'y';
			else
				s2 += 'x';


		while (!s1.empty())
		{
			subS1 = s1.substr(0, 2);
			subS2 = s2.substr(0, 2);
			if (((subS1 == "xy") && (subS2 == "yx")) || ((subS2 == "xy") && (subS1 == "yx")))
				count += 2;
			else if (((subS1 == "xx") && (subS2 == "yy")) || ((subS2 == "xx") && (subS1 == "yy")))
				count++;
			s1 = s1.substr(2);
			s2 = s2.substr(2);
		}
		return count;
	}

	/*				Sliding Window Median
	Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

	Examples:
	[2,3,4] , the median is 3

	[2,3], the median is (2 + 3) / 2 = 2.5

	Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Your job is to output the median array for each window in the original array.

	For example,
	Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.
	Window position                Median
	---------------               -----
	[1  3  -1] -3  5  3  6  7       1
	1 [3  -1  -3] 5  3  6  7       -1
	1  3 [-1  -3  5] 3  6  7       -1
	1  3  -1 [-3  5  3] 6  7       3
	1  3  -1  -3 [5  3  6] 7       5
	1  3  -1  -3  5 [3  6  7]      6
	
	Therefore, return the median sliding window as [1,-1,-1,3,5,6].

	*/
	std::vector<double> medianSlidingWindow(std::vector<int>& nums, int k) {
		int index = 0;
		std::vector<double> mediumSlidingWindow;
		while ((k + index) <= nums.size())
		{
			std::vector<int> sub = std::vector<int>(nums.begin() + index, (nums.begin()+ (k+index)));
			int sum = 0;
			if (k % 2 == 0)
			{
				for (int i = 0; i < sub.size(); i++)
					sum += sub[i];
				mediumSlidingWindow.push_back((double)sum / k);
			}
			else
			{
				merge_sort(sub, 0, sub.size()-1);
				mediumSlidingWindow.push_back(sub[(sub.size() / 2)]);
			}
			index++;
		}
		return mediumSlidingWindow;
	}

	/*			Find the Duplicate Number
	Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), 
	prove that at least one duplicate number must exist. Assume that there is only one duplicate number, 
	find the duplicate one.

	Example 1:
		Input: [1,3,4,2,2]
		Output: 2

	Example 2:
		Input: [3,1,3,4,2]
		Output: 3
	*/
	int findDuplicate(std::vector<int>& nums) {
		merge_sort(nums, 0 , nums.size()-1);
		int num = nums[0];
		for (int i = 1; i < nums.size(); i++)
			if (nums[i] == num)
				return nums[i];
			else
				num = nums[i];
	}
};

#endif
