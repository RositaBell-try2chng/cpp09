#ifndef PMERGEME_TPP
# define PMERGEME_TPP

//templates
template <typename T>
void fillCont(int arr[], size_t size, T &cont)
{
	for (size_t i = 0; i < size; i++)
		cont.push_back(arr[i]);
}

template <typename T>
bool isSort(T &cont)
{
	typename T::iterator it;
	typename T::iterator itN = ++cont.begin();
	typename T::iterator itE = --cont.end();

	for (it = cont.begin(); it != itE; it++)
	{
		if (*it > *itN)
			return false;
		itN++;
	}
	return true;
}

template <typename T>
void printCont(T &cont)
{
	typename T::iterator	iter = cont.begin();
	int						i = 0;

	std::cout << "After: ";
	while (iter != cont.end() && i < MAX_PRINT)
	{
		std::cout << *iter << " ";
		iter++;
		i++;
	}
	if (iter != cont.end())
		std::cout << "[...]";
	std::cout << std::endl;
	//std::cout << "container size is " << cont.size() << std::endl;
}
#endif