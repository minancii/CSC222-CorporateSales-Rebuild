
#include <iostream>
#include <string>
#include <stdexcept>
#include "DivSales.h"
#include <sstream>

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
    cout << "Passed " << passed << " of " << total
        << " checks." << endl;

    return 0;
}
