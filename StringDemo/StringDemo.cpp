// StringDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
	char inputArr[]{ "calc.exe + 100 50" };
	int spaceCounter{};
	for (char* locationPtr{inputArr}; *locationPtr!= '\0'; ++locationPtr)
	{
		if (*locationPtr == ' ')
		{
			*locationPtr = '\0';
			++spaceCounter;
		}
	}
	
	const int size{ spaceCounter + 1 };
	char** argumentVectorArr = new char*[size]{};

	int argumentVectorIndex{};
	argumentVectorArr[argumentVectorIndex++] = inputArr;

	for (char* locationPtr{inputArr}; argumentVectorIndex< size;++locationPtr )
	{
		if (*locationPtr == '\0')
		{
			//eerst wordt de argumentVecetorIndex gebruikt om te assignen, dan pas wordt die value verhoogd
			argumentVectorArr[argumentVectorIndex++] = locationPtr + 1;
		}
	}

	for (int i = 0; i < size; i++)
	{
		std::cout << argumentVectorArr[i] << '\n';
	}
	delete[] argumentVectorArr;
	

	std::cin.get();
}
