#include <iostream>
#include <stack>
#include <ctime>
#include <string>
#include <stdlib.h>    
#include <time.h> 
#include <typeinfo>
#include <fstream>
using namespace std;




const int max = 21;

void addWall(int** maze, int divide, const int halfWay, int min, int max)
{
	//int depth, increase depth
	//return out when depth is maxed log2(max)

	//cout <<endl<< divide << halfWay << min << max << endl;
	
	int halfX = halfWay;
	int halfY = halfWay;


	srand(time(NULL));
	
	int path = rand() % 2;



	
	if (divide == 0)
	{
		if (path == 0)
		{
			for (int i = 0; i < max - 2; i++)
			{

				maze[i][halfY] = 1;
			}
		}
		else
		{
			for (int i = 2; i < max; i++)
			{

				maze[i][halfY] = 1;
			}
		}
	}
	else
	{
		if (path == 0)
		{
			for (int i = 0; i < max - 2; i++)
			{
				maze[halfX][i] = 1;
			}
		}
		else
		{
			for (int i = 2; i < max; i++)
			{

				maze[halfX][i] = 1;
			}
		}
	}
	

}


void makeMaze(int** maze, int xMin, int xMax, int yMin, int yMax, int divide)
{


	cout <<endl<< "x min: " << xMin << "\tx max: " << xMax << "\ty min: " << yMin << "\ty max: " << yMax << "\tdivide: " << divide;

if (((xMax - xMin) <=2) || ((yMax - yMin) <= 2))
return;

int halfX = (xMax - xMin) / 2;
int halfY = (yMax - yMin) / 2;

srand(time(NULL));
int cross = divide;

//cout << endl << cross;
//if we are cutting by columns
if (cross == 0)
{
	addWall(maze, cross, halfY, xMin, xMax);
	if (halfY > yMin)    
	{
		makeMaze(maze, xMin, xMax, yMin, halfY - 1, 1);
	}
	if (yMax > halfY + 1)
	{
		makeMaze(maze, xMin, xMax, halfY + 1, yMax, 1);
	}
}

else //we are cutting by rows
{
	addWall(maze, cross, halfX, yMin, yMax);

	if (halfX > xMin) 
	{
		makeMaze(maze, xMin, halfX - 1, yMin, yMax, 0);
	}
	if (xMax > halfX + 1)
	{
		makeMaze(maze, halfX + 1, xMax, yMin, yMax, 0);
	}
}


}


int** startMaze(unsigned height, unsigned width)
{

	int** newArray = 0;
	newArray = new int*[height];

	for (int h = 0; h < height; h++)
	{

		newArray[h] = new int[width];

		for (int w = 0; w < width; w++)
		{
			if (w == 0)
			{
				newArray[h][0] = 1;
			}
			else if (h == 0)
			{
				newArray[0][w] = 1;
			}

			else if (w == max - 1)
			{
				newArray[h][max - 1] = 1;
			}
			else if (h == max - 1)
			{
				newArray[max - 1][w] = 1;
			}
			else
			{
				newArray[h][w] = 0;
			}

		}
	}

	
	return newArray;
}


void printMaze(int** new2DArray)
{

	
	printf("Array contents: \n");
	cout << "0\t1\t" << max << "\t" << max << "\t 1,1 \t 20,20";
	cout << endl;

	for (int h = 0; h < max; h++)
	{
		for (int w = 0; w < max; w++)
		{
			printf("%i ", new2DArray[h][w]);
		}
		printf("\n");
	}


}


void saveMaze(int** new2DArray)
{

	ofstream output;
	char file[20];
	char input;

	cout << endl << "Save Maze? (Y)/(N): ";
	cin >> input;

	if ((input == 'y') || (input == 'Y')) {
		cout << endl << "Save as: ";
		cin >> file;

		output.open(file);
	



		
		for (int i = 0; i < max; i++) {
			output << endl;
			for (int j = 0; j < max; j++) {
				output <<" "<< new2DArray[i][j]<<" ";     
			}
			output << endl;
		}
		
		cout << "Maze has been saved to" << "/" << file << "/" << endl;
		output.close();
		

	}
}



int main()
{


	int** my2DArray = startMaze(max, max);


	makeMaze(my2DArray, 0, max, 0, max, 0);

	printMaze(my2DArray);
	saveMaze(my2DArray);


	
	return 0;
}