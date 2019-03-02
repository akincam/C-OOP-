#include <iostream>
#include <string>
#include "cell.h"
using namespace std;


namespace ConnectFour
{

	Cell::Cell() : return_row(0), return_column(0), cell(0)
	
	{ /*Body intentionally empty*/ }
				
	Cell::Cell(char cell)
	{
		setCell(cell);
	}
	Cell::Cell(int cell_row ,int cell_column)
	{
		setRow(cell_row);
		setColumn(cell_column);
	}
}
