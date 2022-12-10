#include "WFC.h"
#include <iostream>;

void WFC::PrintGrid()
{
	m_Grid.PrintGrid();
}

void WFC::CollapseGrid(int iterations = 0)
{
	srand(time(NULL));
	int counter = 0;
	if (iterations == 0)
	{
		while (!IsCollapsed())
		{
			CollapseNode();
			++counter;
			if (counter % 10 == 0) {
				std::cout << "After " << counter << " iterations: " << std::endl;
				PrintGrid();
				std::cout << std::endl;
			}
		}
	}
	else
	{
		while (!IsCollapsed() && iterations > counter)
		{
			CollapseNode();
			++counter;
			if (counter % 10 == 0) {
				std::cout << "After " << counter << " iterations: " << std::endl;
				PrintGrid();
				std::cout << std::endl;
			}
		}
	}

	std::cout << "Iterated over the grid " << counter << " times" << std::endl;


}



void WFC::CollapseNode()
{
	m_Grid.CollapseCell();
}


bool WFC::IsCollapsed()
{
	for (std::vector<Cell> cells : m_Grid.GetGrid())
	{
		for (Cell cell : cells)
		{
			if (!cell.IsSet())
			{
				return false;
			}
		}
	}
	return true;
}