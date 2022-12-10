#pragma once
#include "Grid.h"

class WFC
{
public:

	WFC(Grid grid) :m_Grid{ grid } {}
	
	void PrintGrid();
	void CollapseGrid(int iterations);
	bool IsCollapsed();

private:
	void CollapseNode();

	Grid m_Grid;

};