#include <iostream>
#include <ctime>
#include "timsort.h"

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	MyVector<int> vector;

	for (int i = 0; i < 1000; i++)
		vector.add(rand() % 100, i);
	
	vector.output();
	vector.setSize(1000);

	RunPtrSize run = {vector.getArrPtr(), 80 };
	timsort(vector);

	vector.output();
}