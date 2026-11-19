# Corporate Sales Project - CSC 222

This is my Corporate Sales project for CSC 222. The program uses a DivSales class to hold the sales data for the six divisions. Each division has its own dynamic array and the number of sales periods is read in from text file.

## Project Files

- DivSales.h - class declaration and member functions.
- DivSales.cpp - class implementation, dynamic memory, operator overloading and Rule of Three.
- main.cpp - reads the data files, shows the sales totals and does the tests.
- Corporate_Sales_Quarterly_Test_Data.txt - Quarterly sales data.
- Corporate_Sales_Monthly_Test_Data.txt - Monthly sales data.

## How to Run

I used Visual Studio 2026 for this project. Open the solution in VS, ensure two sales data files are in the project working directory and then build and run the program.

## Testing

I tested the programme with both quarterly and monthly sales data.

- Quarterly corporate total: $3,064,150.00
- Monthly corporate total: $8,338,700.00
- Final test results: 80/80 checks passed.

I tested invalid indexes, deep copy, self assignment and various file errors. I used the VS debugger to see how it handled a negative sales value

## GitHub

I did the project in stages, committing each feature after I'd tested it. The commits show the constructor, the operator overloading, the Rule of Three, the corporate totals, the file input and the final testing.
