#pragma once

class Cell
{
public:
	Cell(const char character, size_t row, size_t column);
	Cell();

	bool operator == (const Cell& cell)
	{
		return m_Character == cell.m_Character;
	}

	// Setters
	void SetCharacter(char character);
	void SetGridPosition(const size_t row, const size_t column);


	// Getters
	bool IsSet() { return m_IsSet; }
	char GetCharacter() const { return m_Character; }
	size_t GetRow() { return m_Row; }
	size_t GetColumn() { return m_Column; }

private:
	char m_Character;
	size_t m_Row;
	size_t m_Column;

	bool m_IsSet = false;
};