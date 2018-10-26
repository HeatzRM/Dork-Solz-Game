// Game1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "cmath"
#include "ctime" //used for randomizing seed, rand()
#include "conio.h"//console i/o
#include "windows.h"//used for sleep()

using namespace std;

const int width = 20;
const int height = 10;


int gametime = 0;

int tailX[100], tailY[100];
int nTail;

int x, y; //variable position
int objectX, objectY, object2X, object2Y, object3X, object3Y; //ball location
int score; //optional

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };//enum directions
eDirection dir;

bool gameOver;

void Setup()
{
	int n;
	gameOver = true;
	cout << "Enter any Character then press Enter to start..." << endl << endl;


	cout << "----------=Dork solz=----------" << endl;
	cout << "-----------Game rules----------" << endl;
	cout << "------No hitting of walls------" << endl;
	cout << "-------Get a score of 50------" << endl;
	cout << "-------until timer finish------" << endl;
	cout << "----USE A W S D for movement---" << endl;
	cout << "----------GoodLuck!------------" << endl;

	cin >> n ;
	gameOver = false;

	dir = STOP;//stoping player entity

			   //spawn position
	x = width / 2;
	y = height / 2;

	srand(time(NULL));//generates random seed value
	objectX = rand() % width;
	objectY = rand() % width;


	srand(time(NULL));//generates random seed value 2
	object2X = rand() % width;
	object2Y = rand() % width;

	srand(time(NULL));//generates random seed value 3
	object3X = rand() % width;
	object3Y = rand() % width;

	score = 0;
	gametime = 600;

}

void Draw()
{

	system("cls"); // clears screen

				   //printing topwall
	for (int i = 0; i < width + 2; i++)
		cout << "=";
	cout << endl;

	//printing left and right
	for (int i = 0; i < height; i++)
	{
		//generating inside the area
		for (int j = 0; j < width; j++)
		{

			if (j == 0)
				cout << "|";//left wall

			if (i == y && j == x)//player entity
				cout << "@";

			else if (i == objectY && j == objectX)//object entity
				cout << "X";
			

			else if (i == object2Y && j == object2X)//object entity
				cout << "X";


			else if (i == object3Y && j == object3X)//object entity
				cout << "X";

			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{

					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}

				}
				if (!print)
					cout << " ";
			}
			if (j == width - 1)
				cout << "|";//right wall

		}

		cout << endl;
	}

	//printing bottomwall
	for (int i = 0; i < width + 2; i++)
		cout << "=";
	cout << endl;

	//printing score
	cout << "Score: " << score << endl;

	if (gametime > 0) {
		cout << "Time Left: " << gametime << endl;
		gametime--;
		
	}
	else	gameOver = true;

	if (score == 50)
	{
		cout << "Congrats u won" << endl;
		gameOver = true;
	}


}

void Input()//controling the game simulation...
{
	if (_kbhit())//keyboard hit
	{
		switch (_getch())
		{
			//  w=up, s=down, d=right, a=left
			/*		W
			A   S	D	*/

		case 'a':
			dir = LEFT;//setting direction to enum LEFT etc...
			break;

		case 'd':
			dir = RIGHT;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'w':
			dir = UP;
			break;

		case 'x': //ends game
			gameOver = true;
			break;

		}
	}
}



void Logic()//handles movement inside the map
{
	switch (dir) //switched direction from Input()
	{
	case LEFT:
		x--;
		break;

	case RIGHT:
		x++;
		break;

	case UP:
		y--;
		break;

	case DOWN:
		y++;
		break;

	default:
		break;
	}

	if (x > width || x < 0 || y > height || y < 0)
	{
		gameOver = true;
		cout << "lol u lose..." << endl;
	}	

	if (x == objectX&&y == objectY)
	score += 10;
	
	if (x == object2X&&y == object2Y)
		score += 10;

	//randomize object location
	objectX = rand() % width;
	objectY = rand() % width;

	object2X = rand() % width;
	object2Y = rand() % width;


	object3X = rand() % width;
	object3Y = rand() % width;
}


int main()
{
	Setup();//start set up of the game
	while (!gameOver) //while not gameover, keeps looping...
	{
		Draw();
		Input();
		Logic();
		Sleep(100);
	}
	cout << "Game finished" << endl;
	system("pause");
	return 0;
}

