#pragma once
#include <iostream>
#include <xlsxwriter.h>
#include <array>
#include <variant>
#include <string>

template <size_t N>
class ExcelWriter {
    lxw_workbook* m_Workbook;
    lxw_worksheet** m_Worksheets;
    int m_CurrentSheet = 0;
    int* m_RowIndices;
    int* m_ChartCounts;

public:
    ExcelWriter(int sheetNumber);
    ~ExcelWriter();

    void addRow(std::array<std::variant<std::string, int>, N> arr);
    void switchSheet(int sheetNumber);
    void addChart(const std::pair<std::string, std::string>& names);
};

template <size_t N>
ExcelWriter<N>::ExcelWriter(int sheetNumber) {
    m_Workbook = workbook_new("output.xlsx");
    m_Worksheets = new lxw_worksheet * [sheetNumber];
    m_RowIndices = new int[sheetNumber];
    m_ChartCounts = new int[sheetNumber];

    for (int i = 0; i < sheetNumber; i++) {
        m_Worksheets[i] = workbook_add_worksheet(m_Workbook, ("Sheet" + std::to_string(i + 1)).c_str());
        for (int j = 0; j < N; j++) {
            if (j != 1) worksheet_set_column(m_Worksheets[i], j, j, 20.0, nullptr);
            else worksheet_set_column(m_Worksheets[i], j, j, 95.0, nullptr);
        }
        
        m_RowIndices[i] = 0;
        m_ChartCounts[i] = 0;
    }
}

template <size_t N>
ExcelWriter<N>::~ExcelWriter() {
    if (m_Workbook) {
        workbook_close(m_Workbook);
    }
    delete[] m_Worksheets;
    delete[] m_RowIndices;
    delete[] m_ChartCounts;
}

template <size_t N>
void ExcelWriter<N>::addRow(std::array<std::variant<std::string, int>, N> arr) {
    int i = 0;
    for (const auto& element : arr) {
        if (std::holds_alternative<std::string>(element)) {
            worksheet_write_string(m_Worksheets[m_CurrentSheet],
                m_RowIndices[m_CurrentSheet],
                i,
                std::get<std::string>(element).c_str(), nullptr);
        }
        else {
            worksheet_write_number(m_Worksheets[m_CurrentSheet],
                m_RowIndices[m_CurrentSheet],
                i,
                std::get<int>(element), nullptr);
        }
        i++;
    }
    m_RowIndices[m_CurrentSheet]++;
}

template <size_t N>
void ExcelWriter<N>::switchSheet(int sheetNumber) {
    m_CurrentSheet = sheetNumber - 1;
}

template <size_t N>
void ExcelWriter<N>::addChart(const std::pair<std::string, std::string>& names) {
    lxw_chart* chart = workbook_add_chart(m_Workbook, LXW_CHART_COLUMN);
    int start_row = 2 + (m_ChartCounts[m_CurrentSheet] * 30);
    int end_row = start_row + 29;

    worksheet_write_string(m_Worksheets[m_CurrentSheet],
        0,              // First row (0-based index)
        N - 1,          // Last column (helper column)
        "Array Size",   // Header text
        nullptr);       // No format

    // Create a helper column for characters
    char helper_col = 'A' + (N - 1); // Use the last column as helper
    for (int row = start_row; row <= end_row; row++) {
        std::string formula;
        if (row < start_row + 9) {  // First 9 rows (0-8)
            // Get only the 5th character
            formula = "=MID(B" + std::to_string(row) + ",5,1)";
        }
        else {
            // Get 5th and 6th characters
            formula = "=MID(B" + std::to_string(row) + ",5,2)";
        }
        worksheet_write_formula(m_Worksheets[m_CurrentSheet],
            row - 1, N - 1,  // Convert to 0-based index for row
            formula.c_str(),
            nullptr);
    }

    // Use helper column for categories
    std::string category_range = "Sheet" + std::to_string(m_CurrentSheet + 1) +
        "!$" + std::string(1, helper_col) + "$" + std::to_string(start_row) +
        ":$" + std::string(1, helper_col) + "$" + std::to_string(end_row);

    std::string value_range = "Sheet" + std::to_string(m_CurrentSheet + 1) +
        "!$" + static_cast<char>('A' + (N - 2)) +
        "$" + std::to_string(start_row) +
        ":$" + static_cast<char>('A' + (N - 2)) +
        "$" + std::to_string(end_row);

    chart_add_series(chart, category_range.c_str(), value_range.c_str());
    chart_title_set_name(chart, (names.first + " " + names.second).c_str());

    lxw_chart_options options = { .x_offset = 0, .y_offset = 0, .x_scale = 1.5, .y_scale = 1.0 };
    worksheet_insert_chart_opt(m_Worksheets[m_CurrentSheet],
        7 + (m_ChartCounts[m_CurrentSheet] * 30),
        5 ,
        chart,
        &options);

    m_ChartCounts[m_CurrentSheet]++;
}





