#include "PmergeMe.hpp"

void printIts(std::list<int>::iterator start, std::list<int>::iterator end)
{
	while (start != end)
	{
		std::cout << *start << ' ';
		++start;
	}
	std::cout << std::endl;
}

static std::list<int>::iterator moveIt(std::list<int>::iterator start, int size, bool flgForward)
{
	for (int i = 0; i < size; ++i)
	{
		if (flgForward)
			++start;
		else
			--start;
	}
	return (start);
}

static void insertationSort(std::list<int> &lst, std::list<int>::iterator &begin, std::list<int>::iterator &end)
{
	std::list<int>::iterator	it = begin;
	std::list<int>::iterator	itTMP;
	int							TMP;

	//go until sort
	++it;
	for (; it != end; ++it)
	{
		if (*it < *moveIt(it, 1, false))
			break;
	}
	//move all
	while (it != end)
	{
		if (*it >= *moveIt(it, 1, false))
		{
			++it;
			continue;
		}
		TMP = *it;
		it = lst.erase(it);
		if (TMP <= *begin)
			begin = lst.insert(begin, TMP);
		else
		{
			itTMP = begin;
			while (*itTMP < TMP && itTMP != end)
				++itTMP;
			lst.insert(itTMP, TMP);
		}
	}
}

static void merge(std::list<int>::iterator begin, std::list<int>::iterator middle, std::list<int>::iterator end)
{
	std::list<int> TMP;
	std::list<int>::iterator it1 = begin;
	std::list<int>::iterator it2 = middle;

	//fill TMP with choice
	while (it1 != middle && it2 != end)
	{
		if (*it1 < *it2)
		{
			TMP.push_back(*it1);
			++it1;
		}
		else
		{
			TMP.push_back(*it2);
			++it2;
		}
	}
	//fill full TMP
	for (; it1 != middle; ++it1)
		TMP.push_back(*it1);
	for (; it2 != end; ++it2)
		TMP.push_back(*it2);
	//copy TMP to lst
	it2 = begin;
	for (it1 = TMP.begin(); it1 != TMP.end(); ++it1)
	{
		*it2 = *it1;
		++it2;
	}
}

static void	mergeSort(std::list<int> &lst, std::list<int>::iterator &begin, std::list<int>::iterator &end)
{
	std::list<int>::iterator middle;
	size_t	size = std::distance(begin, end);
	//exit from recursive
	if (size <= INSERT_BORDER)
	{
		insertationSort(lst, begin, end);
		return;
	}
	//divide and sort two small lists
	middle = begin;
	middle = moveIt(middle, (size / 2), true);
	mergeSort(lst, begin, middle);
	mergeSort(lst, middle, end);
	//merge
	merge(begin, middle, end);
}

void	doItFor1(int arr[], size_t size)
{
	double			ts;
	std::list<int>	lst;

	std::cout << "list sort" << std::endl;
	fillCont(arr, size, lst);
	ts = getTime();
	if (size > 1)
	{
		std::list<int>::iterator begin = lst.begin();
		std::list<int>::iterator end = lst.end();
		mergeSort(lst, begin, end);
	}
	ts = getTime() - ts;
	printCont(lst);
	std::cout << "Time to process a range of " << size << " elements with std::list : " << ts << " ms" << std::endl;
	std::cout << std::boolalpha << "is list sorted? " << isSort(lst) << std::endl;
}