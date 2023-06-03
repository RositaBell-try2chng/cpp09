#include "PmergeMe.hpp"

static void	insertationSort(std::vector<int> &vec, std::vector<int>::iterator itStart, std::vector<int>::iterator itEnd)
{
	int		TMP;
	std::vector<int>::iterator it = itStart;
	std::vector<int>::iterator itTMP;
	//go until sort
	it++;
	for (; it != itEnd; it++)
	{
		if (*it < *(it - 1))
			break;
	}
	//move all
	while (it != itEnd)
	{
		if (*it >= *(it - 1))
		{
			it++;
			continue;
		}
		TMP = *it;
		it = vec.erase(it);
		if (TMP <= *itStart)
			itStart = vec.insert(itStart, TMP);
		else
		{
			itTMP = itStart;
			while (*itTMP < TMP && itTMP != itEnd)
			{
				itTMP++;
			}
			vec.insert(itTMP, TMP);
		}
	}
}

static void merge(std::vector<int>::iterator itStart, std::vector<int>::iterator itMiddle, std::vector<int>::iterator itEnd)
{
	std::vector<int> TMP;
	std::vector<int>::iterator it1 = itStart;
	std::vector<int>::iterator it2 = itMiddle;
	
	//fill TMP with choice
	while (it1 != itMiddle && it2 != itEnd)
	{
		if (*it1 < *it2)
		{
			TMP.push_back(*it1);
			it1++;
		}
		else
		{
			TMP.push_back(*it2);
			it2++;
		}
	}
	//fill full TMP
	for (; it1 != itMiddle; it1++)
		TMP.push_back(*it1);
	for (; it2 != itEnd; it2++)
		TMP.push_back(*it2);
	//copy TMP to vec
	it2 = itStart;
	for (it1 = TMP.begin(); it1 != TMP.end(); it1++)
	{
		*it2 = *it1;
		it2++;
	}
}

static void mergeSort(std::vector<int> &vec, std::vector<int>::iterator itStart, std::vector<int>::iterator itEnd)
{
	//exit from recursive
	if (itEnd - itStart <= INSERT_BORDER)
	{
		insertationSort(vec, itStart, itEnd);
		return;
	}
	//divide and sort two smaller vectors
	size_t						offsetIt = (itEnd - itStart) / 2;
	std::vector<int>::iterator	itMiddle = itStart + offsetIt;

	mergeSort(vec, itStart, itMiddle);
	mergeSort(vec, itMiddle, itEnd);
	merge(itStart, itMiddle, itEnd);
}

void	doItFor2(int arr[], size_t size)
{
	double				ts;
	std::vector<int>	vec;
	std::vector<int>::iterator itStart;
	std::vector<int>::iterator itEnd;

	std::cout << "vector sort" << std::endl;
	fillCont(arr, size, vec);
	ts = getTime();
	if (size > 1)
	{
		itStart = vec.begin();
		itEnd = vec.end();
		mergeSort(vec, itStart, itEnd);
	}
	ts = getTime() - ts;
	printCont(vec);
	std::cout << "Time to process a range of " << size << " elements with std::vector : " << ts << " ms" << std::endl;
	std::cout << std::boolalpha << "is vector sorted? " << isSort(vec) << std::endl;
}