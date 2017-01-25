// Towers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
using namespace std;

int count;

typedef struct
{
	int pile, height, size;
} Disk;

void Solve(Disk**, Disk, int, Disk*, int&);
int Switch(Disk**, int, int);
void Move(Disk**, Disk, int, Disk*);
Disk* Search(Disk**, int, int&);
void PrintPiles(Disk**, int);

int main()
{
	int answer = 1;
	int n;
	while (answer)
	{
		::count = 0;
		cout << "Number of Disks: ";
		cin >> n;

		Disk** piles = new Disk*[3];

		for (int i = 0; i < 3; i++)
			piles[i] = new Disk[n + 1];

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < n + 1; j++)
				piles[i][j].size = 0;
		for (int i = 0, j = n; i < n; i++, j--)
		{
			piles[0][i].pile = 0;
			piles[0][i].height = i;
			piles[0][i].size = j;
		}

		Disk* current = piles[0];

		PrintPiles(piles, n);
		clock_t startTime = clock();
		Solve(piles, piles[0][0], 2, current, n);
		clock_t endTime = clock();
		clock_t clockTicksTaken = endTime - startTime;
		double timeInSeconds = clockTicksTaken / (double)CLOCKS_PER_SEC;
		PrintPiles(piles, n);

		cout << "Moves: " << ::count << endl << "Seconds: " << timeInSeconds << endl;
		cout << "Again? ";
		cin >> answer;
	}
	return 0;
}

void Solve(Disk** piles, Disk disk, int target, Disk* current, int& n)
{
	if (piles[current->pile][current->height + 1].size != 0)
	{
		current++;
		Solve(piles, piles[disk.pile][current->height], Switch(piles, current->pile, target), current, n);
	}

	Move(piles, disk, target, current);
	PrintPiles(piles, n);
	::count++;

	if (disk.size > 1)
	{
		disk.pile = target;
		current = Search(piles, disk.size - 1, n);
		Solve(piles, *current, disk.pile, current, n);
	}
	return;
}

int Switch(Disk** piles, int p, int target)
{
	if (p == 0)
		if (target == 1)
			return 2;
		else
			return 1;
	if (p == 1)
		if (target == 0)
			return 2;
		else
			return 0;
	if (p == 2)
		if (target == 0)
			return 1;
		else
			return 0;
	return 0;
}

void Move(Disk** piles, Disk disk, int target, Disk* current)
{
	Disk temp = piles[disk.pile][disk.height];
	piles[disk.pile][disk.height].size = 0;
	for (int i = 0;;i++)
		if (piles[target][i].size == 0)
		{
			piles[target][i] = temp;
			piles[target][i].height = i;
			piles[target][i].pile = target;
			current = &piles[target][i];
			break;
		}
	return;
}

Disk* Search(Disk** piles, int targetSize, int& n)
{
	for(int i = 0; i < 3; i++)
		for (int j = 0; j < n; j++)
		{
			if (piles[i][j].size == 0)
				break;
			if (piles[i][j].size == targetSize)
				return &piles[i][j];
		}
	return &piles[n][n];
}

void PrintPiles(Disk** piles, int n)
{
	for (int i = 0; i < 100000000; i++);

	system("CLS");
	cout << endl << endl << endl << endl << endl;
	for (int i = n; i >= 0; i--)
	{
		for (int j = 0; j < 3; j++)
		{
			if (piles[j][i].size == 0)
				cout << string(31, ' ');
			else
				cout << string(16 - piles[j][i].size, ' ')
				<< string(piles[j][i].size + (piles[j][i].size - 1), '#')
				<< string(16 - piles[j][i].size, ' ');
		}
		cout << endl;
	}
}