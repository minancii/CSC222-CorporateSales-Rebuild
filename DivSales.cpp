
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

DivSales::DivSales(const DivSales& other)
    : sales(nullptr), numberOfPeriods(other.numberOfPeriods)
{
    // Give the copied object its own memory.
    sales = new double[numberOfPeriods];

    for (int i = 0; i < numberOfPeriods; i++)
    {
        sales[i] = other.sales[i];
    }
}

DivSales& DivSales::operator=(const DivSales& other)
{
    // Do nothing if the object is assigned to itself.
    if (this == &other)
    {
        return *this;
    }

    // Allocate memory before deleting the old array.
    double* newSales = new double[other.numberOfPeriods];

    for (int i = 0; i < other.numberOfPeriods; i++)
    {
        newSales[i] = other.sales[i];
    }

    delete[] sales;

    sales = newSales;
    numberOfPeriods = other.numberOfPeriods;

    return *this;
}
