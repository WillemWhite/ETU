#include <iostream>
#include <ctime>
#include "timsort.h"

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));

	MyVector<int> vector(1000);

	for (int i = 0; i < 1000; i++)
		vector.getArrPtr()[i] = rand() % 100;

	vector.output();

	cout << endl;

	timsortGalloping(vector);

	vector.output();
}