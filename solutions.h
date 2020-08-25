#include "utilities.h"
#include "math.h"
#ifndef SOLUTIONS_HPP
#define SOLUTIONS_HPP




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
		std::vector<int> sub = std::vector<int>(nums.begin() + index, (nums.begin() + (k + index)));
		int sum = 0;
		if (k % 2 == 0)
		{
			for (int i = 0; i < sub.size(); i++)
				sum += sub[i];
			mediumSlidingWindow.push_back((double)sum / k);
		}
		else
		{
			merge_sort(sub, 0, sub.size() - 1);
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
	merge_sort(nums, 0, nums.size() - 1);
	int num = nums[0];
	for (int i = 1; i < nums.size(); i++)
		if (nums[i] == num)
			return nums[i];
		else
			num = nums[i];
}

	/*			Maximum Number of Events That Can Be Attended
	Given an array of events where events[i] = [startDayi, endDayi]. Every event i starts at startDayi and ends at endDayi.

	You can attend an event i at any day d where startTimei <= d <= endTimei. Notice that you can only attend one event at any time d.

	Return the maximum number of events you can attend.
	*/
int maxEvents(std::vector<std::vector<int>>& events) {
	std::vector<int> subset;
	for (int i = 0; i < events.size(); i++)
		subset.push_back(events[i][0]);
	
	merge_sort(subset, 0, subset.size() - 1);
	std::vector<int> Days;
	Days.push_back(subset.at(0));
	for (int i = 1; i < subset.size(); i++)
		if (subset[i] != subset[i - 1])
			Days.push_back(subset[i]);

	std::vector<std::vector<int>> sortedSubset;
	for (int i = 0; i < Days.size(); i++)
	{
		std::vector<int> secondSubset;
		for (int j = 0; j < events.size(); j++)
		{
			if (events[j][0] == Days[i])
				secondSubset.push_back(events[j][1]);
		}
		merge_sort(secondSubset, 0, secondSubset.size() - 1);
		for (int j = 0; j < secondSubset.size(); j++)
			sortedSubset.push_back({ Days[i], secondSubset[j] });
	}
	for (int i = 0; i < sortedSubset.size(); i++)
		std::cout << "[" << sortedSubset[i][0] << "," << sortedSubset[i][1] << "] ";

	Days.clear();
	for (int i = sortedSubset[sortedSubset.size() - 1][1]; i > 0; i--)
		Days.push_back(i);

	merge_sort(Days, 0, Days.size() - 1);

	int index = 0;
	int count = 0;
	for (int i = 0; i < sortedSubset.size(); i++)
	{
		if ((Days[index] >= sortedSubset[i][0]) && (Days[index] <= sortedSubset[i][1]))
		{
			count++;
			index++;
		}
	}

	return count;
}

	/*			Custom Sort String
	S and T are strings composed of lowercase letters. In S, no letter occurs more than once.

	S was sorted in some custom order previously. We want to permute the characters of T
	so that they match the order that S was sorted. More specifically, if x occurs before
	y in S, then x should occur before y in the returned string.

	Return any permutation of T (as a string) that satisfies this property.
	*/
std::string customSortString(std::string S, std::string T) {
	std::map<char, char> order;
	std::map<char, char> mapped_pairs;
	std::string ans = "";
	std::map<char, char>::iterator it;
	
	for (int i = 0; i < S.length(); i++)
		(i < (S.length() - 1)) ? order.insert(std::pair<char, char>(S[i], S[i + 1])) : order.insert(std::pair<char, char>(S[i], '\0'));

	for (int i = 0; i < T.length(); i++)
		if ((it = order.find(T[i])) != order.end())
			mapped_pairs.insert(std::pair<char, char>(it->first, it->second));
		else
			ans += T[i];


	char start = '\0';
	for (int i = 0; i < S.length(); i++)
		if ((it = mapped_pairs.find(S[i])) != mapped_pairs.end())
		{
			start = S[i];
			break;
		}

	while (start != '\0')
	{
		for (int i = 0; i < T.length(); i++)
			if (T[i] == start)
				ans += start;
		start = mapped_pairs[start];
	}
	return ans;
}

	/* Partition Array into Disjoint Intervals
	Given an array A, partition it into two (contiguous) subarrays left and right so that:

		Every element in left is less than or equal to every element in right.
		left and right are non-empty.
		left has the smallest possible size.
	Return the length of left after such a partitioning.  It is guaranteed that such a partitioning exists.
	*/
int partitionDisjoint(std::vector<int>& A) {
	std::vector<int> left;
	int initial = A[0];
	for (int i = 0; i < A.size(); i++)
		if (A[i] > initial)
			break;
		else
			left.push_back(A[i]);

	return left.size();
}

int maxSumAfterPartitioning(std::vector<int>& A, int K) {
	if (A.size() == 0)
		return 0;
	else if (A.size() <= K)
		return max_in_array(A) * (A.size() - 1);
	
	std::vector<int> list(A.begin(), A.begin() + K);

	for (int i = 0; i < list.size(); i++)
		std::cout << list[i];

	return 0;
}

	/*	1324. Print Words Vertically

	Given a string s. Return all the words vertically in the same order in which they appear in s.
	Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
	Each word would be put on only one column and that in one column there will be only one word.
	
	*/
std::vector<std::string> printVertically(std::string s) {
	std::vector<std::string> words;
	int position_1 = 0; // used to split the string
	int longest = 0;	// used to find the index of the longest in words
	int length = 0;		// used to compare the lengths among strs (length of the longest string in words)
	int j = 0;			// keeps index of longest in words
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			std::string str = s.substr(position_1, i - position_1);
			words.push_back(str);
			position_1 = i + 1;
			if (str.length() >= length) {
				length = str.length();
				longest = j;
			}
			j++;
		}
		else if (i == s.length() - 1){
			std::string str = s.substr(position_1);
			words.push_back(str);
			if (str.length() >= length) {
				length = str.length();
				longest = j;
			}
		}
	}

	std::vector<std::string> ans(length, "");
	for (int i = 0; i < length; i++) {
		for (int w = 0; w < words.size(); w++) {
			if ((i == length-1) && (words[w] == words[longest])) {
				ans[i] += words[w][i];
				break;
			}
			if (i > (words[w].size()-1))
				ans[i] += ' ';
			else if(i < words[w].size())
				ans[i] += words[w][i];
		}
	}
	return ans;
}

		

#endif
