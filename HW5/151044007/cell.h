#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

namespace ConnectFour
{

	class Cell
	{
		public:
			Cell();
			Cell(char cell);
			Cell(int cell_row ,int cell_column);
			
			inline void setRow(int cell_row) {return_row=cell_row;}
			inline void setColumn(int cell_column) {return_column=cell_column;}
			inline void setCell(char content_cell) {cell=content_cell;}
			
			inline int getRow() const {return return_row;}	
			inline int getColumn() const {return return_column;}	
			inline char getCell() const {return cell;}
							
		private:
			int return_row;
			int return_column;
			char cell;	
	};
	


}
#endif
