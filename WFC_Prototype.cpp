#include <iostream>
#include "WFC.h"



int main()
{

	size_t size = 9;
	Grid grid{};
	grid.GenerateGrid(size);
		
	WFC algorithm = WFC{ grid };
	algorithm.PrintGrid();
	algorithm.CollapseGrid(0);
	algorithm.PrintGrid();
	return 0;
}


