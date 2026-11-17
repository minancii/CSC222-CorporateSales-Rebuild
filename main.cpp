
#include <iostream>
#include <string>
#include <stdexcept>
#include "DivSales.h"

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
    cout << "Passed " << passed << " of " << total
        << " checks." << endl;

    return 0;
}
