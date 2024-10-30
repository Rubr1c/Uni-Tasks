#pragma once
#include <iostream>
#include <xlsxio_write.h>
#include <vector>
#include <string>

class ExcelWriter {
	xlsxiowriter writer;
public:
	ExcelWriter(std::vector<std::string>& cols);
	~ExcelWriter() { xlsxiowrite_close(writer); }

	void addRow(std::string algorithm, std::string arrayUsed, int numOfMoves, std::string time);
};