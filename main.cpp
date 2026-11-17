
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
    cout << "Passed " << passed << " of " << total
        << " checks." << endl;

    return 0;
}
