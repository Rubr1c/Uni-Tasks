#include "Excel.h"

ExcelWriter::ExcelWriter(std::vector<std::string>& cols) {
	m_Writer = xlsxiowrite_open("output.xlsx", "Sheet1");
	for (int i = 0; i < cols.size(); i++) {
		xlsxiowrite_add_cell_string(m_Writer, cols[i].c_str());
	}
	xlsxiowrite_next_row(m_Writer);
}

void ExcelWriter::addRow(std::string algorithm, 
						 std::string arrayUsed, 
						 int numOfMoves, 
						 std::string time) {

	xlsxiowrite_add_cell_string(m_Writer, algorithm.c_str());
	xlsxiowrite_add_cell_string(m_Writer, arrayUsed.c_str());
	xlsxiowrite_add_cell_int(m_Writer, numOfMoves);
	xlsxiowrite_add_cell_string(m_Writer, time.c_str());
	xlsxiowrite_next_row(m_Writer);
}

