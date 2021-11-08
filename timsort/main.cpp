#include <iostream>
#include <ctime>
#include "timsort.h"

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));

	MyVector<int> vector;

	for (int i = 0; i < 10000; i++)
		vector.add(rand() % 100, i);

	vector.output();

	cout << endl;

	timsortMerge(vector);

	vector.output();
}