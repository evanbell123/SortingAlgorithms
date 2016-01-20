#include "Header.h"

vector<int> *readFrequencies(string fileName);

void displayFrequencies(vector<int> *frequencies);
void displayQuickSortVars(unsigned int i, unsigned int j, unsigned int left, unsigned int right, int pivot);
unsigned getNumberOfDigits(unsigned i);

void quickSort(vector<int> *&frequencies, unsigned int left, unsigned int right);


void main()
{

	vector<string> *fileNameVector = new vector<string>;
	vector<vector<int>*> *freqVector = new vector<vector<int>*>;
	int i = 0;
	string fileName = "dataset1.txt";
	char repeat = 'n';

	cout << "Please Read:" << endl;
	cout << "Datasets must be must be in text files." << endl;
	cout << "The first character in the file must be a space." << endl;
	cout << "After the space comes the first frequency" << endl;
	cout << "followed by a comma, then a space" << endl;
	cout << "The program will stop reading if it finds a zero" << endl << endl;

	do {
		cout << "Enter the name of the text file you want to compute (Ex. dataset1.txt):	" << endl;
		//cin >> fileName;
		fileNameVector->push_back(fileName);
		freqVector->push_back(readFrequencies(fileName));
		cout << "Unsorted" << endl;
		displayFrequencies(freqVector->at(0));
		int width = 10;

		cout << "i" << setw(width - 1) << "j" << setw(width + 1) << "left" << setw(width) << "right" << setw(width - 1) << "pivot" << endl;
		quickSort(freqVector->at(0), 0, freqVector->at(0)->size() - 1);
		cout << "Sorted" << endl;
		displayFrequencies(freqVector->at(0));
		cout << "Would you like to enter another file? Y = yes, N = no	" << endl;

		//cin >> repeat;

	} while (repeat == 'Y' || repeat == 'y');

	cout << endl;
	system("PAUSE");


}

void quickSort(vector<int> *&freqVector, unsigned int left, unsigned int right) {

	unsigned int i = left;
	unsigned int j = right;
	unsigned int tmp;
	int pivot = freqVector->at((left + right) / 2);

	cout << "init" << endl;
	displayQuickSortVars(i, j, left, right, pivot);

	/* partition */

	while (i <= j)
	{
		
		while (freqVector->at(i) < pivot)
		{
			cout << freqVector->at(i) << " < pivot" << endl;
			i++;
			displayQuickSortVars(i, j, left, right, pivot);
		}

		while (freqVector->at(j) > pivot)
		{
			cout << freqVector->at(j) << " > pivot" << endl;
			j--;
			displayQuickSortVars(i, j, left, right, pivot);
		}

		if (i <= j)
		{
			tmp = freqVector->at(i);
			freqVector->at(i) = freqVector->at(j);
			freqVector->at(j) = tmp;
			i++;
			j--;
			displayQuickSortVars(i, j, left, right, pivot);
		}
		
	};

	/* recursion */

	if (left < j)
	{
		quickSort(freqVector, left, j);
	}

	if (i < right)
	{
		quickSort(freqVector, i, right);
	}
}

vector<int> *readFrequencies(string fileName)
{
	ifstream inFile(fileName); //the first character in the file must be a space
	string line;
	size_t stringSize;
	vector<int> *freqVector = new vector<int>;
	int frequency;
	if (inFile.is_open())
	{
		while (!inFile.eof() && line != "0")
		{
			getline(inFile, line, ','); //get next frequency
			line.erase(0, 1); // remove the space
			frequency = stoi(line, &stringSize); //convert to integer
			if (frequency != 0)
			{
				freqVector->push_back(frequency);
			}
		}
		inFile.close();
	}
	else
	{
		cout << "Unable to open file";
	}
	return freqVector;
}

void displayQuickSortVars(unsigned int i, unsigned int j, unsigned int left, unsigned int right, int pivot)
{
	int width = 10;

	cout << i << setw(width - getNumberOfDigits(i)) << j << setw(width - getNumberOfDigits(j)) << left << setw(width - getNumberOfDigits(left)) << right << setw(width - getNumberOfDigits(right)) << pivot << endl;
}

void displayFrequencies(vector<int> *frequencies)
{

	for (unsigned int i = 0; i < frequencies->size(); i++)
	{
		cout << frequencies->at(i) << ", ";
	}
	cout << endl;
}

unsigned getNumberOfDigits(unsigned i)
{
	return i > 0 ? (int)log10((double)i) + 1 : 1;
}