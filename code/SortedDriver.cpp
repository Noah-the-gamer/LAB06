// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.

//Modified By Noah Fulton October 29 2018



#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	//declare two variables needed to find nearest neighbor
	double isolated = 0;
	double neighborDistance = 0;
	//loop through the vector
	if (number.size() > 0)
	{
		for (int i = 0; i < number.size() - 1; i++)
		{
			//if this is location zero, default as nearest neighbor
			if (i == 0)
			{
				isolated = number[i];
				neighborDistance = number[i + 1] - number[i];
			}
			else if (i == (number.size() - 1))
			{
				//if this is the last number, only check the distance to the previous value
				if (number[i] - number[i - 1] > neighborDistance)
				{
					isolated = number[i];
				}
			}
			else
			{
				//temporarily hold the values for neighbor distance until the closest neighbor is calculated
				double tempNeighbor1 = number[i] - number[i - 1];
				double tempNeighbor2 = number[i + 1] - number[i];
				double tempNearestDist;
				//find which neighbor is closest
				if (tempNeighbor1 >= tempNeighbor2)
				{
					tempNearestDist = tempNeighbor2;
				}
				else
				{
					tempNearestDist = tempNeighbor1;
				}
				//see if this neighbor distance is the longest distance yet
				if (tempNearestDist > neighborDistance)
				{
					isolated = number[i];
					neighborDistance = tempNearestDist;
				}
			}
		}
	}
	return isolated;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	//easier to count how many occur
	int doOccur = 0;
	
	//iterate through the first list
	for (list<string>::iterator it1 = A.begin(); it1 != A.end(); ++it)
	{
		//iterate whrough the second list until a same occurs
		list<string>::iterator it2 = B.begin();
		bool noSames = true;
		do
		{
			if (*it1 == *it2)
			{
				noSames = false;
				doOccur++;
			}
			++it2;
		} while (it2 != B.end() && noSames);
	}
	//return how many don't occur in both by subtracting the amount that do occur from the size.
	return A.size() - doOccur;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
