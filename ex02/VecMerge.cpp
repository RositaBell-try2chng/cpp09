#include "PmergeMe.hpp"

static void	insertationSort(std::vector<int> &vec, size_t size)
{
	size_t	j;
	size_t	i;
	int		TMP;

	//go until sort
	for (i = 1; i < size; i++)
	{
		if (vec[i] < vec[i - 1])
			break;
	}
	//move all
	i--;
	while (++i < size)
	{
		if (vec[i] >= vec[i - 1])
			continue;
		TMP = vec[i];
		vec.erase(vec.begin() + i);
		if (TMP <= vec[0])
			vec.insert(vec.begin(), TMP);
		else
		{
			j = 0;
			while (TMP > vec[j])
				j++;
			vec.insert(vec.begin() + j, TMP);
		}
	}
}

static void mergeSort(std::vector<int> &vec, size_t size)
{
	//exit from recursive
	if (size <= INSERT_BORDER)
	{
		insertationSort(vec, size);
		return;
	}
	//divide and sort two smaller vectors
	std::vector<int>	A(vec.begin(), vec.begin() + size / 2);
	std::vector<int>	B(vec.begin() + size / 2, vec.end());
	size_t				i = 0;
	size_t				j = 0;
	size_t				k = 0;

	mergeSort(A, size / 2);
	mergeSort(B, size / 2 + size % 2);
	while ((i < size / 2) && (j < size / 2 + size % 2))
	{
		if (A[i] < B[j])
			vec[k++] = A[i++];
		else
			vec[k++] = B[j++];
	}
	vec.resize(k);
	if (i < size / 2)
		vec.insert(vec.end(), A.begin() + i, A.end());
	else
		vec.insert(vec.end(), B.begin() + j, B.end());
}

void	doItFor2(int arr[], size_t size)
{
	double				ts;
	std::vector<int>	vec;

	std::cout << "vector sort" << std::endl;
	fillCont(arr, size, vec);
	ts = getTime();
	if (size > 2)
		mergeSort(vec, size);
	ts = getTime() - ts;
	printCont(vec);
	std::cout << "Time to process a range of " << size << " elements with std::vector : " << ts << " ms" << std::endl;
	std::cout << std::boolalpha << "is vector sorted? " << isSort(vec) << std::endl;
}