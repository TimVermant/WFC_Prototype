#include <iostream>
#include "Grid.h"

void Grid::GenerateGrid(size_t size)
{

	m_GridSize = size * size;
	m_Rows = size;
	m_Columns = size;
	for (size_t row = 0; row < size; row++)
	{
		std::vector<Cell> newRow;
		for (size_t column = 0; column < size; column++)
		{

			newRow.push_back(Cell{ '0',row,column });

		}
		m_Grid.push_back(newRow);
	}

}

void Grid::PrintGrid()
{
	for (std::vector<Cell> row : m_Grid)
	{
		for (const Cell& cell : row)
		{
			std::cout << cell.GetCharacter();
		}
		std::cout << std::endl;
	}

}

void Grid::CollapseCell()
{
	Cell cell = GetLowestEntropyCell();
	size_t row = cell.GetRow();
	size_t column = cell.GetColumn();
	char newValue = GetCellValue(row, column);
	m_Grid.at(row).at(column).SetCharacter(newValue);
}

Cell Grid::GetCell(const size_t row, const size_t column)
{
	return m_Grid.at(row).at(column);
}

char Grid::GetCellValue(const size_t row, const size_t column)
{
	std::vector<Cell> uniqueNeighbours = GetUniqueNeighbourCells(row, column);
	std::cout << "Unique neighbours: " << uniqueNeighbours.size() << " - ";
	return GetCellValue(uniqueNeighbours);
}

Cell Grid::GetLowestEntropyCell()
{
	// This is the max entropy so it will select a random tile 
	int lowestEntropy = 5;
	Cell cell = m_Grid.at(0).at(0);
	for (size_t row = 0; row < m_Rows; row++)
	{
		for (size_t column = 0; column < m_Columns; column++)
		{
			int entropy = GetEntropy(row, column);
			if (entropy < lowestEntropy && !m_Grid.at(row).at(column).IsSet())
			{
				lowestEntropy = entropy;
				cell = GetCell(row, column);
			}


		}
	}


	return cell;
}

int Grid::GetEntropy(const size_t row, const size_t column)
{
	int currentEntropy = 4;
	std::vector<Cell> uniqueNeighbours = GetUniqueNeighbourCells(row, column);
	size_t uniqueSize = uniqueNeighbours.size();

	if (uniqueSize == 1)
	{
		currentEntropy = 2;
	}
	else if (uniqueSize >= 2)
	{
		currentEntropy = 1;
	}


	return currentEntropy;
}


//HELPERS


Cell Grid::GetRandomOpenCell()
{
	for (std::vector<Cell> row : m_Grid)
	{
		for (Cell cell : row)
		{
			if (!cell.IsSet())
			{
				return cell;
			}
		}

	}

	// When it returns here the Cell is set and the grid is collapsed
	return m_Grid.at(0).at(0);
}

std::vector<Cell> Grid::GetUniqueNeighbourCells(const size_t row, const size_t column)
{
	std::vector<Cell> neighbours;

	if (row + 1 < m_Grid.size())
	{
		neighbours.push_back(m_Grid.at(row + 1).at(column));
	}
	if (row != 0)
	{
		neighbours.push_back(m_Grid.at(row - 1).at(column));
	}

	if (column + 1 < m_Grid.at(row).size())
	{
		neighbours.push_back(m_Grid.at(row).at(column + 1));
	}
	if (column != 0)
	{
		neighbours.push_back(m_Grid.at(row).at(column - 1));
	}
	int currentEntropy = 4;
	std::vector<Cell> uniqueNeighbours;
	for (Cell neighbour : neighbours)
	{
		if (neighbour.GetCharacter() != '0' &&
			std::find(uniqueNeighbours.begin(), uniqueNeighbours.end(), neighbour) == uniqueNeighbours.end())
		{
			uniqueNeighbours.push_back(neighbour);
		}
	}
	return uniqueNeighbours;
}


char Grid::GetCellValue(const std::vector<Cell>& uniqueNeighbours)
{
	char cellValue = '0';
	size_t uniqueSize = uniqueNeighbours.size();


	switch (uniqueSize)
	{
	case 0:
	{
		// Give it a random value 1 - 4

		size_t randomIndex = rand() % m_PotentialCellValues.size();
		cellValue = m_PotentialCellValues.at(randomIndex);

	}
	break;
	case 1:
	{
		// Can be anything but the opposite value
		// Either value - 1, value, value + 1 (clamped)

		size_t randomIndex = rand() % m_PotentialCellValues.size();
		char oppositeValue = GetOppsiteValue(uniqueNeighbours.at(0).GetCharacter());
		cellValue = m_PotentialCellValues.at(randomIndex);
		while (cellValue == oppositeValue)
		{
		
			randomIndex = rand() % (m_PotentialCellValues.size() - uniqueSize);
			cellValue = m_PotentialCellValues.at(randomIndex);

		}
	}
	break;
	case 2:
	{// Is value inbetween

		int char1 = uniqueNeighbours.at(0).GetCharacter() - '0';
		int char2 = uniqueNeighbours.at(1).GetCharacter() - '0';
		if (std::abs(char1 + char2) % 2 != 0)
		{
			// pick one of the two
			size_t randomIndex = rand() % (uniqueSize);
			cellValue = uniqueNeighbours.at(randomIndex).GetCharacter();
		}
		else
		{
			cellValue = GetInbetweenValue(uniqueNeighbours.at(0).GetCharacter(), uniqueNeighbours.at(1).GetCharacter());

		}
	}
	break;
	case 3:
	{
		cellValue = GetMiddleValue(uniqueNeighbours);
	}
	break;


	}


	return cellValue;
}

// Get opposite value
char Grid::GetOppsiteValue(char character)
{
	auto it = std::find(m_PotentialCellValues.begin(), m_PotentialCellValues.end(), character);

	if (it == m_PotentialCellValues.end() - 1 || it == m_PotentialCellValues.end() - 2)
	{
		it -= 2;
	}
	else
	{

		it += 2;
	}

	return *it;
}

// Get middle value - Assume size == 3
char Grid::GetMiddleValue(const std::vector<Cell>& uniqueNeighbours)
{

	char char1 = uniqueNeighbours.at(0).GetCharacter();
	char char2 = uniqueNeighbours.at(1).GetCharacter();
	char char3 = uniqueNeighbours.at(2).GetCharacter();
	char middleValue = '0';

	if (std::abs(char1 - char2) > 1)
	{
		middleValue = char3;
	}
	else if (std::abs(char2 - char3) > 1)
	{
		middleValue = char1;
	}
	else if (std::abs(char3 - char1) > 1)
	{
		middleValue = char2;
	}
	return middleValue;
}

char Grid::GetInbetweenValue(char char1, char char2)
{
	size_t index1 = GetCharacterIndex(char1);
	index1++;
	if (index1 == m_PotentialCellValues.size())
	{
		index1 = 0;
	}
	return m_PotentialCellValues.at(index1);
}

size_t Grid::GetCharacterIndex(char character) const
{
	for (size_t i = 0; i < m_PotentialCellValues.size(); i++)
	{
		if (m_PotentialCellValues.at(i) == character)
		{
			return i;
		}
	}
	return m_PotentialCellValues.size();
}








