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
    int m_CurrentSheet;
    int* m_RowIndices;

public:
    ExcelWriter(int sheetNumber);
    ~ExcelWriter();

    void addRow(std::array<std::variant<std::string, int>, N> arr);
    void switchSheet(int sheetNumber);
    void addChart();
};

template <size_t N>
ExcelWriter<N>::ExcelWriter(int sheetNumber) {
    m_Workbook = workbook_new("output.xlsx");
    m_Worksheets = new lxw_worksheet * [sheetNumber];
    m_RowIndices = new int[sheetNumber];

    for (int i = 0; i < sheetNumber; i++) {
        m_Worksheets[i] = workbook_add_worksheet(m_Workbook, ("Sheet" + std::to_string(i + 1)).c_str());
        for (int j = 0; j < N; j++) {
            if (j != 1) worksheet_set_column(m_Worksheets[i], j, j, 20.0, nullptr);
            else worksheet_set_column(m_Worksheets[i], j, j, 95.0, nullptr);
        }
        
        m_RowIndices[i] = 0;
    }

    m_CurrentSheet = 0;
}

// Destructor
template <size_t N>
ExcelWriter<N>::~ExcelWriter() {
    if (m_Workbook) {
        workbook_close(m_Workbook);
    }
    delete[] m_Worksheets;
    delete[] m_RowIndices;
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
void ExcelWriter<N>::addChart() {
    lxw_chart* chart = workbook_add_chart(m_Workbook, LXW_CHART_COLUMN);

    std::string categoriesRange = ""; 

    char lastColumnLetter = 'A' + static_cast<char>(N - 2);
    std::string valuesRange = "Sheet" + std::to_string(m_CurrentSheet + 1) +
        "!$" + lastColumnLetter + "$2:$" + lastColumnLetter + "$" +
        std::to_string(m_RowIndices[m_CurrentSheet]);

    chart_add_series(chart, nullptr, valuesRange.c_str()); 

    int chartInsertColumn = (m_CurrentSheet + 1) * (N + 1); 
    worksheet_insert_chart(m_Worksheets[m_CurrentSheet], 1, chartInsertColumn, chart);
}


