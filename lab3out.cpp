//Khue Dang
//Lab3out
//Bug Zapper 

#include <iostream>
#include "graph1.h"
#include <ctime>

using namespace std;

//Function prototypes
void initDisplay();                                                //Displays heading area
int getNoBugs();                                                   //Prompts for the number of bugs to be displayed
int* getXCoords(int no_bugs);                                      //Generates random x-coordinates for each bug to be displayed
int* getYCoords(int no_bugs);                                      //Generates random y-coordinates for each bug to be displayed
int* displayObjects(int* x_coords, int* y_coords, int no_objects); //Displays bugs
int zapBugs(int* x, int* y, int* objects, int no_bugs);            //Allows the user to zap the bugs

int main()
{
	//Variable Declaration/Initialization
	int no_bugs = 0;
	int* x_coords = NULL;
	int* y_coords = NULL;
	int* objects = NULL;
	char repeat = 'y';

	//Random generator
	srand(time(0));

	//Display graphics
	displayGraphics();

	do
	{
		//Function call statements
		initDisplay();                                            //Displays heading area
		no_bugs = getNoBugs();                                    //Prompts for the number of bugs to be displayed
		x_coords = getXCoords(no_bugs);                           //Generates random x-coordinates for each bug to be displayed
		y_coords = getYCoords(no_bugs);                           //Generates random y-coordinates for each bug to be displayed
		objects = displayObjects(x_coords, y_coords, no_bugs);    //Displays bugs
		zapBugs(x_coords, y_coords, objects, no_bugs);            //Allows the user to zap the bugs

		//Cleanup memory	
		delete[] x_coords;
		delete[] y_coords;
		delete[] objects;

		//Prompts repeat
		cout << "Repeat program? (y/n) ";
		cin >> repeat;
		cout << endl;

		//Clears the Graphics and Console
		clearGraphics();
		system("cls");
	}while (repeat == 'Y' || repeat == 'y');
}

//Displays heading area
void initDisplay()
{
	displayPNG("grass.png", 0, 0);  //Grass
	drawRect(250, 0, 200, 40);      //White box
	gout << setPos(285, 20) << setColor(0, 0, 0) << "Score: 0" << endg;
	gout << setPos(375, 20) << setColor(0, 0, 0) << "Shots: 0" << endg;
}

//Prompts for the number of bugs to be displayed
int getNoBugs()
{
	//Variable declaration/initialization
	int no = 0;

	//Prompt for # bugs
	do
	{
		cout << "Enter # of Bugs to Display <Between 5 and 20>: ";
		cin >> no;

		//Perform data validation
		if (no < 5 || no > 20)
			cout << "Number must be between 5 and 20 inclusively. Please re-enter." << endl;
	} while (no < 5 || no > 20);
	return no;
}

//Generates random x-coordinates for each bug to be displayed
int* getXCoords(int no_bugs)
{
	//Variable declaration/initialization
	int i = 0;

	//Dynamically allocate the array for x-coords
	int* x = new int[no_bugs];

	//Generates x-coords for each object randomly
	for (i = 0; i < no_bugs; i++)
		x[i] = rand() % 577;
	return x;
}

//Generates random y-coordinates for each bug to be displayed
int* getYCoords(int no_bugs)
{
	//Variable declaration/initialization
	int i = 0;

	//Dynamically allocate the array for x-coords
	int* y = new int[no_bugs];

	//Generates x-coords for each object randomly
	for (i = 0; i < no_bugs; i++)
		y[i] = rand() % 377;
	return y;
}

//Displays bugs
int* displayObjects(int* x_coords, int* y_coords, int no_objects)
{
	//Dynamically allocate the array of integers 
	int* objects = new int[no_objects];

	//Display all objects at x/y random positions stored in x_coords/y_coords
	for (int i = 0; i < no_objects; i++)
	{
		objects[i] = displayPNG("bugs.png", x_coords[i], y_coords[i]);
	}
	return objects;
}

//Allows the user to zap the bugs
int zapBugs(int* x, int* y, int* objects, int no_bugs)
{
	int guess = 2*no_bugs;
	int bx = 0;
	int by = 0;
	int score = 0;
	int shots = 0;

	//Zap the bugs
	while (guess != 0 && score != no_bugs)
	{
		cout << "Enter x/y coordinate: ";
		cin >> bx >> by;
		++shots;
		gout << setPos(375, 20) << setColor(0, 0, 0) << "Shots: " << shots << endg;
		guess--;
	    setColor(drawCircle(10, bx, by), 0, 0, 0);
		for (int a = 10; a > 0; a--)
			setColor(drawCircle(a, bx, by), 0, 0, 0);

		for (int i = 0; i < no_bugs; i++)
		{
			if ((bx > x[i]) && (bx < x[i] + 64) && (by > y[i]) && (by < y[i] + 64))
			{
				removeObject(objects[i]);
				score++;
				gout << setPos(285, 20) << setColor(0, 0, 0) << "Score: " << score << endg;
			}
		}
	}

	//Displays result
	if (score == no_bugs)
		gout << setPos(330, 35) << setColor(0, 0, 0) << "Winner" << endg;
	else if (guess == 0)
		gout << setPos(330, 35) << setColor(0, 0, 0) << "Game over" << endg;
	return score;
}
