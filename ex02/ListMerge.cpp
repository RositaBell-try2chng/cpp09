#include "PmergeMe.hpp"

static std::list<int>::iterator moveIt(std::list<int>::iterator start, int size, bool flgForward)
{
	for (int i = 0; i < size; i++)
	{
		if (flgForward)
			start++;
		else
			start--;
	}
	return (start);
}

static void	finishIt(std::list<int>::iterator &itSrc, std::list<int> &lst, std::list<int>::iterator &itLst)
{
	while (itLst != lst.end())
	{
		*itLst = *itSrc;
		itLst++;
		itSrc++;
	}
}

static void insertationSort(std::list<int> &lst)
{
	std::list<int>::iterator	it = lst.begin();
	std::list<int>::iterator	iter = ++lst.begin();;
	int							TMP;

	//go until sort
	for (; iter != lst.end(); iter++)
	{
		if (*iter < *it)
			break;
		it++;
	}
	//move all
	while (it != lst.end())
	{
		if (*it >= *moveIt(it, 1, false))
		{
			it++;
			continue;
		}
		TMP = *it;
		it = lst.erase(it);
		if (TMP <= *lst.begin())
			lst.push_front(TMP);
		else
		{
			iter = lst.begin();
			while (TMP > *iter)
				iter++;
			lst.insert(iter, TMP);
		}
	}
}

static void	mergeSort(std::list<int> &lst, size_t size)
{
	//exit from recursive
	if (size <= INSERT_BORDER)
	{
		insertationSort(lst);
		return;
	}
	//divide and sort two small lists
	size_t sizeA = size / 2;
	size_t sizeB = sizeA + size % 2;
	std::list<int> A(sizeA);
	std::list<int> B(sizeB);
	std::list<int>::iterator iter;

	std::list<int>::iterator it = lst.begin();
	std::list<int>::iterator it2 = moveIt(it, sizeA, true);
	A.assign(it, it2);

	it2 = lst.end();
	it = moveIt(it2, sizeB, false);
	B.assign(it, it2);

	mergeSort(A, sizeA);
	mergeSort(B, sizeB);

	//fill lst in correct order
	it = A.begin();
	it2 = B.begin();
	iter = lst.begin();
	while (it != A.end() && it2 != B.end() && iter != lst.end())
	{
		if (*it < *it2)
		{
			*iter = *it;
			it++;
		}
		else
		{
			*iter = *it2;
			it2++;
		}
		iter++;
	}
	if (it != A.end())
		finishIt(it, lst, iter);
	else
		finishIt(it2, lst, iter);
}

void	doItFor1(int arr[], size_t size)
{
	double			ts;
	std::list<int>	lst;

	std::cout << "list sort" << std::endl;
	fillCont(arr, size, lst);
	ts = getTime();
	if (size > 1)
		mergeSort(lst, size);
	ts = getTime() - ts;
	printCont(lst);
	std::cout << "Time to process a range of " << size << " elements with std::list : " << ts << " ms" << std::endl;
	std::cout << std::boolalpha << "is list sorted? " << isSort(lst) << std::endl;
}