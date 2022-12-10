#pragma once
#include <vector>
#include "Cell.h"

class Grid
{
public:

	void GenerateGrid(const size_t size);
	void PrintGrid();

	void CollapseCell();

	std::vector<std::vector<Cell>> GetGrid() { return m_Grid; }
	Cell GetCell(const size_t row, const size_t column);
	char GetCellValue(const size_t row, const size_t column);
	Cell GetLowestEntropyCell();
	int GetEntropy(const size_t row, const size_t column);


private:

	// Helper functions
	Cell GetRandomOpenCell();
	std::vector<Cell> GetUniqueNeighbourCells(const size_t row, const size_t column);
	
	char GetCellValue(const std::vector<Cell>& uniqueNeighbours);
	char GetOppsiteValue(char character);
	char GetMiddleValue(const std::vector<Cell>& uniqueNeighbours);
	char GetInbetweenValue(char char1, char char2);

	size_t GetCharacterIndex(char character) const;

	// Member variables
	std::vector<std::vector<Cell>> m_Grid;
	size_t m_GridSize = 0;
	size_t m_Rows = 0;
	size_t m_Columns = 0;

	std::vector<char> m_PotentialCellValues{ '1','2','3','4' };
};
