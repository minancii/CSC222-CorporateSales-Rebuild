
#include <iostream>
#include <string>
#include <stdexcept>
#include "DivSales.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdio>


using namespace std;

void checkTest(bool result, string name, int& passed, int& total)
{
    total++;

    cout << name << ": ";

    if (result)
    {
        cout << "PASS" << endl;
        passed++;
    }
    else
    {
        cout << "FAIL" << endl;
    }
}

void runSalesFileTest(const string& filename, int expectedPeriods,
    double expectedCorporateTotal, const double expectedDivTotals[6],
    int& passed, int& total, bool expectError = false)
{
    cout << "\n===== File Test: " << filename << " =====\n";
    DivSales::resetCorporateTotal();
    ifstream inputFile(filename);

    if (!inputFile)
    {
        cout << "ERROR: Could not open " << filename << endl;
        checkTest(expectError, "Open file", passed, total);
        return;
    }

    checkTest(true, "Open file", passed, total);

    int numberOfPeriods = 0;

    if (!(inputFile >> numberOfPeriods) || numberOfPeriods <= 0)
    {
        cout << "ERROR: Invalid period count." << endl;
        checkTest(expectError, "Valid period count", passed, total);
        return;
    }

    checkTest(numberOfPeriods == expectedPeriods,
        "Period count", passed, total);

    const int NUM_DIVISIONS = 6;

    DivSales divisions[NUM_DIVISIONS] = {
        DivSales(numberOfPeriods),
        DivSales(numberOfPeriods),
        DivSales(numberOfPeriods),
        DivSales(numberOfPeriods),
        DivSales(numberOfPeriods),
        DivSales(numberOfPeriods)
    };

    // Start a new corporate total for this file.
    DivSales::resetCorporateTotal();

    for (int d = 0; d < NUM_DIVISIONS; d++)
    {
        for (int p = 0; p < numberOfPeriods; p++)
        {
            // Read straight into the private dynamic array.
            if (!(inputFile >> divisions[d][p]) ||
                !isfinite(divisions[d][p]) ||
                divisions[d][p] <= 0.0)
            {
                cout << "ERROR: Invalid sales value at division "
                    << d + 1 << ", period " << p + 1 << endl;

                DivSales::resetCorporateTotal();
                checkTest(expectError, "Valid sales data", passed, total);
                return;
            }
        }

        // Add each completed division only once.
        DivSales::addToCorporateTotal(
            divisions[d].getTotalSales());
    }


    string extra;

    if (inputFile >> extra)
    {
        cout << "ERROR: Extra value in data file." << endl;
        DivSales::resetCorporateTotal();
        checkTest(expectError, "Exact data count", passed, total);
        return;
    }

    // Check if a bad file was incorrectly accepted.
    if (expectError)
    {
        checkTest(false, "Invalid file should be rejected",
            passed, total);
        DivSales::resetCorporateTotal();
        return;
    }

    checkTest(true, "Valid sales data and count", passed, total);

    // Print all sales in a table.
    cout << fixed << setprecision(2);

    cout << "\n" << setw(10) << "Period";

    for (int d = 0; d < NUM_DIVISIONS; d++)
    {
        cout << setw(14) << ("Division " + to_string(d + 1));
    }

    cout << endl;

    for (int p = 0; p < numberOfPeriods; p++)
    {
        cout << setw(10) << p + 1;

        for (int d = 0; d < NUM_DIVISIONS; d++)
        {
            cout << setw(14) << divisions[d][p];
        }

        cout << endl;
    }

    cout << setw(10) << "Total";

    for (int d = 0; d < NUM_DIVISIONS; d++)
    {
        cout << setw(14) << divisions[d].getTotalSales();
    }

    cout << "\nCorporate total: $"
        << DivSales::getCorporateTotal() << "\n\n";

    // Compare calculated totals with known results.
    for (int d = 0; d < NUM_DIVISIONS; d++)
    {
        checkTest(
            fabs(divisions[d].getTotalSales() -
                expectedDivTotals[d]) < 0.01,
            "Division " + to_string(d + 1) + " total",
            passed, total);
    }

    checkTest(
        fabs(DivSales::getCorporateTotal() -
            expectedCorporateTotal) < 0.01,
        "Corporate total", passed, total);
}

int main()
{
    int passed = 0;
    int total = 0;

    cout << "===== DivSales Constructor Tests =====" << endl;

    DivSales quarterly(4);

    checkTest(quarterly.getNumberOfPeriods() == 4,
        "Quarterly array size is 4", passed, total);

    checkTest(quarterly.getTotalSales() == 0.0,
        "Quarterly array starts with zero sales", passed, total);

    DivSales monthly(12);

    checkTest(monthly.getNumberOfPeriods() == 12,
        "Monthly array size is 12", passed, total);

    checkTest(monthly.getTotalSales() == 0.0,
        "Monthly array starts with zero sales", passed, total);

    bool rejectedZero = false;

    try
    {
        DivSales invalid(0);
    }
    catch (const invalid_argument&)
    {
        rejectedZero = true;
    }

    checkTest(rejectedZero,
        "Reject zero periods", passed, total);

    bool rejectedNegative = false;

    try
    {
        DivSales invalid(-1);
    }
    catch (const invalid_argument&)
    {
        rejectedNegative = true;
    }

    checkTest(rejectedNegative,
        "Reject negative periods", passed, total);

    cout << endl;
    cout << "===== operator[] Tests =====" << endl;

    // Make sure all four values start at zero.
    bool allZeros = true;

    for (int i = 0; i < quarterly.getNumberOfPeriods(); i++)
    {
        if (quarterly[i] != 0.0)
        {
            allZeros = false;
        }
    }

    checkTest(allZeros, "Initial values are zero",
        passed, total);

    // Test first, middle, and last indexes.
    quarterly[0] = 120.0;
    quarterly[2] = 180.0;
    quarterly[3] = 200.0;

    checkTest(quarterly[0] == 120.0,
        "First index", passed, total);

    checkTest(quarterly[2] == 180.0,
        "Middle index", passed, total);

    checkTest(quarterly[3] == 200.0,
        "Last index", passed, total);

    // Test reading through a const reference.
    const DivSales& readOnly = quarterly;

    checkTest(readOnly[2] == 180.0,
        "Const operator[]", passed, total);

    // Total should be 120 + 0 + 180 + 200 = 500.
    checkTest(quarterly.getTotalSales() == 500.0,
        "Division total", passed, total);

    // Test a negative index.
    bool negativeRejected = false;

    try
    {
        quarterly[-1] = 999.0;
    }
    catch (const out_of_range&)
    {
        negativeRejected = true;
    }

    checkTest(negativeRejected,
        "Reject negative index", passed, total);

    // Index 4 is invalid for an array of size 4.
    bool highRejected = false;

    try
    {
        quarterly[4] = 999.0;
    }
    catch (const out_of_range&)
    {
        highRejected = true;
    }

    checkTest(highRejected,
        "Reject index past the end", passed, total);

    // Test invalid access through a const reference.
    bool constRejected = false;

    try
    {
        double unused = readOnly[4];
        (void)unused;
    }
    catch (const out_of_range&)
    {
        constRejected = true;
    }

    checkTest(constRejected,
        "Reject invalid const index", passed, total);

    checkTest(quarterly.getTotalSales() == 500.0,
        "Invalid indexes do not change sales",
        passed, total);

    // Test reading directly into an array element.
    istringstream input("75.5");
    input >> quarterly[1];

    checkTest(quarterly[1] == 75.5,
        "Read sales using input stream",
        passed, total);

    checkTest(quarterly.getTotalSales() == 575.5,
        "Total updates after changing sales",
        passed, total);

    // Test an array containing only one period.
    DivSales onePeriod(1);
    onePeriod[0] = 19.25;

    checkTest(onePeriod[0] == 19.25 &&
        onePeriod.getTotalSales() == 19.25,
        "Single-period array", passed, total);

    cout << endl;
    cout << "===== Rule of Three Tests =====" << endl;

    // Test the copy constructor.
    DivSales copied(quarterly);

    checkTest(copied.getNumberOfPeriods() == 4,
        "Copy constructor keeps array size",
        passed, total);

    checkTest(copied[0] == 120.0 &&
        copied[1] == 75.5 &&
        copied[2] == 180.0 &&
        copied[3] == 200.0,
        "Copy constructor copies all values",
        passed, total);

    // The two arrays should have different addresses.
    checkTest(&copied[0] != &quarterly[0],
        "Copy constructor uses separate memory",
        passed, total);

    copied[0] = 999.0;

    checkTest(quarterly[0] == 120.0 &&
        copied[0] == 999.0,
        "Changing copy does not change original",
        passed, total);

    // Test assignment between different array sizes.
    monthly[0] = 50.0;
    monthly[11] = 500.0;

    monthly = quarterly;

    checkTest(monthly.getNumberOfPeriods() == 4,
        "Assignment updates array size",
        passed, total);

    checkTest(monthly[0] == 120.0 &&
        monthly[1] == 75.5 &&
        monthly[2] == 180.0 &&
        monthly[3] == 200.0,
        "Assignment copies all values",
        passed, total);

    checkTest(&monthly[0] != &quarterly[0],
        "Assignment uses separate memory",
        passed, total);

    monthly[3] = 300.0;

    checkTest(quarterly[3] == 200.0 &&
        monthly[3] == 300.0,
        "Changing assigned object does not change original",
        passed, total);

    // Test assigning an object to itself.
    monthly = monthly;

    checkTest(monthly.getNumberOfPeriods() == 4 &&
        monthly[3] == 300.0,
        "Self-assignment keeps the data",
        passed, total);

    // Test chained assignment.
    DivSales first(1);
    DivSales second(2);

    first = second = quarterly;

    checkTest(first.getNumberOfPeriods() == 4 &&
        second.getNumberOfPeriods() == 4,
        "Chained assignment updates both sizes",
        passed, total);

    checkTest(first[0] == 120.0 &&
        second[3] == 200.0,
        "Chained assignment copies values",
        passed, total);

    checkTest(&first[0] != &second[0] &&
        &first[0] != &quarterly[0] &&
        &second[0] != &quarterly[0],
        "Chained assignment keeps separate arrays",
        passed, total);

    cout << endl;
    cout << "===== Static Corporate Total Tests =====" << endl;

    checkTest(DivSales::getCorporateTotal() == 0.0,
        "Corporate total starts at zero",
        passed, total);

    // Add the total of one division.
    DivSales::addToCorporateTotal(quarterly.getTotalSales());

    checkTest(DivSales::getCorporateTotal() == 575.5,
        "Add first division total",
        passed, total);

    // Copying an object should not change the shared total.
    DivSales totalCopy(quarterly);

    checkTest(DivSales::getCorporateTotal() == 575.5,
        "Copy constructor does not change corporate total",
        passed, total);

    // Assignment should not change the shared total either.
    DivSales totalAssigned(1);
    totalAssigned = quarterly;

    checkTest(DivSales::getCorporateTotal() == 575.5,
        "Assignment does not change corporate total",
        passed, total);

    // Changing a copied object's data should not
    // automatically change the corporate total.
    totalCopy[0] = 400.0;

    checkTest(DivSales::getCorporateTotal() == 575.5 &&
        quarterly[0] == 120.0,
        "Changing a copy does not affect original or total",
        passed, total);

    // Clear the total before loading another dataset.
    DivSales::resetCorporateTotal();

    checkTest(DivSales::getCorporateTotal() == 0.0,
        "Reset corporate total",
        passed, total);

    // Test adding two completed division totals.
    DivSales::addToCorporateTotal(quarterly.getTotalSales());
    DivSales::addToCorporateTotal(onePeriod.getTotalSales());

    checkTest(DivSales::getCorporateTotal() == 594.75,
        "Add totals from two divisions",
        passed, total);

    DivSales::resetCorporateTotal();

    checkTest(DivSales::getCorporateTotal() == 0.0,
        "Ready for next sales file",
        passed, total);

    cout << endl;
    cout << "===== Sales File Integration Tests =====" << endl;

    // Expected totals for each division.
    const double quarterlyTotals[6] = {
        548550.0, 430500.0, 649200.0,
        390800.0, 559400.0, 485700.0
    };

    const double monthlyTotals[6] = {
        1434850.0, 1179300.0, 1806600.0,
        1062600.0, 1556650.0, 1298700.0
    };

    runSalesFileTest(
        "Corporate_Sales_Quarterly_Test_Data.txt",
        4, 3064150.0, quarterlyTotals, passed, total);

    runSalesFileTest(
        "Corporate_Sales_Monthly_Test_Data.txt",
        12, 8338700.0, monthlyTotals, passed, total);

    cout << "\n===== Invalid File Tests =====" << endl;

    // Create temporary files with incorrect sales data.
    {
        ofstream file("CSC222_Test_Invalid_Periods.txt");
        file << "0\n";
    }

    {
        ofstream file("CSC222_Test_Invalid_Negative.txt");
        file << "1\n10 20 -5 40 50 60\n";
    }

    {
        ofstream file("CSC222_Test_Invalid_Text.txt");
        file << "1\n10 20 wrong 40 50 60\n";
    }

    {
        ofstream file("CSC222_Test_Invalid_Short.txt");
        file << "2\n10 20 30 40\n";
    }

    {
        ofstream file("CSC222_Test_Invalid_Extra.txt");
        file << "1\n10 20 30 40 50 60 70\n";
    }

    // Test a file that does not exist.
    runSalesFileTest(
        "CSC222_Test_Missing_File.txt",
        1, 0.0, quarterlyTotals, passed, total, true);

    checkTest(DivSales::getCorporateTotal() == 0.0,
        "Missing file leaves total at zero", passed, total);

    runSalesFileTest(
        "CSC222_Test_Invalid_Periods.txt",
        1, 0.0, quarterlyTotals, passed, total, true);

    checkTest(DivSales::getCorporateTotal() == 0.0,
        "Invalid period count leaves total at zero", passed, total);

    runSalesFileTest(
        "CSC222_Test_Invalid_Negative.txt",
        1, 0.0, quarterlyTotals, passed, total, true);

    checkTest(DivSales::getCorporateTotal() == 0.0,
        "Negative sales leave total at zero", passed, total);

    runSalesFileTest(
        "CSC222_Test_Invalid_Text.txt",
        1, 0.0, quarterlyTotals, passed, total, true);

    checkTest(DivSales::getCorporateTotal() == 0.0,
        "Text input leaves total at zero", passed, total);

    runSalesFileTest(
        "CSC222_Test_Invalid_Short.txt",
        2, 0.0, quarterlyTotals, passed, total, true);

    checkTest(DivSales::getCorporateTotal() == 0.0,
        "Short file leaves total at zero", passed, total);

    runSalesFileTest(
        "CSC222_Test_Invalid_Extra.txt",
        1, 0.0, quarterlyTotals, passed, total, true);

    checkTest(DivSales::getCorporateTotal() == 0.0,
        "Extra data leaves total at zero", passed, total);

    // Remove the temporary test files.
    remove("CSC222_Test_Invalid_Periods.txt");
    remove("CSC222_Test_Invalid_Negative.txt");
    remove("CSC222_Test_Invalid_Text.txt");
    remove("CSC222_Test_Invalid_Short.txt");
    remove("CSC222_Test_Invalid_Extra.txt");

    cout << endl;
    cout << "Passed " << passed << " of " << total
        << " checks." << endl;

    return 0;
}
