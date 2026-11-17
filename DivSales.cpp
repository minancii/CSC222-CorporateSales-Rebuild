
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
