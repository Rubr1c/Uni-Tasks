#pragma once
#include <iostream>
#include <xlsxio_write.h>
#include <vector>
#include <string>

class ExcelWriter {
	xlsxiowriter m_Writer;
public:
	ExcelWriter(std::vector<std::string>& cols);
	~ExcelWriter() { xlsxiowrite_close(m_Writer); }

	void addRow(std::string algorithm, std::string arrayUsed, int numOfMoves, std::string time);
};