
#include "DivSales.h"
#include <stdexcept>

DivSales::DivSales(int periods)
    : sales(nullptr), numberOfPeriods(periods)
{
    if (periods <= 0)
    {
        throw std::invalid_argument(
            "Number of periods must be greater than zero.");
    }

    // Allocate the array and start every value at zero.
    sales = new double[periods] {};
}

DivSales::~DivSales()
{
    delete[] sales;
}

int DivSales::getNumberOfPeriods() const
{
    return numberOfPeriods;
}

double DivSales::getTotalSales() const
{
    double total = 0.0;

    for (int i = 0; i < numberOfPeriods; i++)
    {
        total += sales[i];
    }

    return total;
}

// Allows reading and changing a sales value.
double& DivSales::operator[](int index)
{
    if (index < 0 || index >= numberOfPeriods)
    {
        throw std::out_of_range("Invalid sales period index.");
    }

    return sales[index];
}

// Allows reading a value without changing the object.
const double& DivSales::operator[](int index) const
{
    if (index < 0 || index >= numberOfPeriods)
    {
        throw std::out_of_range("Invalid sales period index.");
    }

    return sales[index];
}
