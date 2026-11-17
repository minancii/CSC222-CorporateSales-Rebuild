
#ifndef DIVSALES_H
#define DIVSALES_H

// DivSales stores sales for one division.
// Each object owns its own dynamic array.
// Invariant: numberOfPeriods > 0 and sales points to
// an array containing that many double values.

class DivSales
{
private:
    double* sales;
    int numberOfPeriods;

public:
    // Create an array with the requested number of periods.
    DivSales(int periods);

    // Release the memory owned by the object.
    ~DivSales();

    // Copying will be implemented in a later step.
    DivSales(const DivSales&) = delete;
    DivSales& operator=(const DivSales&) = delete;

    // Return the number of sales periods.
    int getNumberOfPeriods() const;

    // Calculate total sales for this division.
    double getTotalSales() const;
};

#endif
#pragma once
