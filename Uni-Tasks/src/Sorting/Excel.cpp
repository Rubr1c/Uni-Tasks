#include "Excel.h"

ExcelWriter::ExcelWriter(std::vector<std::string>& cols) {
	writer = xlsxiowrite_open("output.xlsx", "Sheet1");
	for (int i = 0; i < cols.size(); i++) {
		xlsxiowrite_add_cell_string(writer, cols[i].c_str());
	}
	xlsxiowrite_next_row(writer);
}

void ExcelWriter::addRow(std::string algorithm, 
						 std::string arrayUsed, 
						 int numOfMoves, 
						 std::string time) {

	xlsxiowrite_add_cell_string(writer, algorithm.c_str());
	xlsxiowrite_add_cell_string(writer, arrayUsed.c_str());
	xlsxiowrite_add_cell_int(writer, numOfMoves);
	xlsxiowrite_add_cell_string(writer, time.c_str());
	xlsxiowrite_next_row(writer);
}