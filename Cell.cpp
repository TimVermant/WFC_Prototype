#include "Cell.h"

Cell::Cell() :
	m_Character{ '0' },
	m_Row{ 0 },
	m_Column{ 0 }
{
}


Cell::Cell(const char character, size_t row, size_t column) :
	m_Character{ character },
	m_Row{ row },
	m_Column{ column }
{
}

void Cell::SetCharacter(char character)
{
	m_Character = character;
	m_IsSet = true;
}

void Cell::SetGridPosition(const size_t row, const size_t column)
{
	m_Row = row;
	m_Column = column;
}
