/* Списочные структуры.
** Реализовать следующие структуры:
** односвязный список, динамический массив и стек.
** Стек можно реализовать как на базе списка, так и отдельно.
** Использовать стек для реализации алгоритма сортировочной станции.
** разрешённые символы в исходном выражении:
** +, -, *, /, ^, sin, cos, (, ), 0, 1, 2, 3, 4, 5, 6, 7, 8, 9.
** Для упрощения разбиения входной строки на токены разрешается
** отделять каждый символ пробелом.*/

#include <iostream>
#include "my_vector.h"
#include "my_list.h"
#include "my_stack.h"

using namespace std;

int priority(char symbol)
{
	switch (symbol)
	{
	case '+': return 1;
	case '-': return 1;
	case '*': return 2;
	case '/': return 2;
	case '^': return 3;
	default: return 0;
	}
	return 0;
}

int main(int argc, char* argv[])
{

	MyStack<char> output;
	MyStack<char> input;
	MyStack<char> operators;

	cout << "Please enter the original expression: ";

	char symbol = 0;
	cin.clear();

	do
	{
		cin.get(symbol);

		if (symbol != ' ' && symbol !='\n')
			output.push(symbol);

	}	while (symbol != '\n');

	cout << endl;
	//inverted for ease of reading data
	while (output.isNotEmpty())
	{
		input.push(output.pop());
	}

	while (input.isNotEmpty())
	{
		char symbol = input.pop();
		switch (symbol)
		{
		case '0': output.push(symbol); continue;
		case '1': output.push(symbol); continue;
		case '2': output.push(symbol); continue;
		case '3': output.push(symbol); continue;
		case '4': output.push(symbol); continue;
		case '5': output.push(symbol); continue;
		case '6': output.push(symbol); continue;
		case '7': output.push(symbol); continue;
		case '8': output.push(symbol); continue;
		case '9': output.push(symbol); continue;
		case '(': operators.push(symbol); continue;
		case 's': operators.push(symbol); continue;
		case 'i': operators.push(symbol); continue;
		case 'n': operators.push(symbol); continue;
		case 'c': operators.push(symbol); continue;
		case 'o': operators.push(symbol); continue;
		default: break;
		}

		switch (priority(symbol))
		{
		case 1:

			if (operators.isNotEmpty())
			{
				while (priority(operators.peek()) >= 1)
				{
					output.push(operators.pop());
				}

				operators.push(symbol);
			}
			else
				operators.push(symbol);

			continue;

		case 2:

			if (operators.isNotEmpty())
			{
				while (priority(operators.peek()) >= 2)
				{
					output.push(operators.pop());
				}

				operators.push(symbol);
			}
			else
				operators.push(symbol);

			continue;

		case 3:

			operators.push(symbol);

			continue;

		default: break;
		}

		if (symbol == ')')
		{
			while (operators.peek() != '(')
				output.push(operators.pop());

			operators.pop();

			while (operators.isNotEmpty() && (operators.peek() == 's' || operators.peek() == 'n'))
			{
				for (int i = 0; i < 3; i++)
				{
					input.push(operators.pop());
				}
				for (int i = 0; i < 3; i++)
				{
					output.push(input.pop());
				}
			}
		}
		else
		{
			cerr << "Error! Wrong Input!" << endl;
			return 0;
		}
	}

	while (operators.isNotEmpty())
	{
		output.push(operators.pop());
	}

	cout << "Reverse Polish notation: " << endl;

	output.output();

	return 0;
}