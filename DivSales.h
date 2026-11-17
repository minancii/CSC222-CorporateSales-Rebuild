
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

    // Total sales shared by all DivSales objects.
    static double corporateTotal;


public:
    // Create an array with the requested number of periods.
    DivSales(int periods);

    // Release the memory owned by the object.
    ~DivSales();


    // Make an independent copy of another DivSales object.
    DivSales(const DivSales& other);

    // Copy data into an existing DivSales object.
    DivSales& operator=(const DivSales& other);


    // Return the number of sales periods.
    int getNumberOfPeriods() const;

    // Calculate total sales for this division.
    double getTotalSales() const;

    // Get the total sales of all divisions.
    static double getCorporateTotal();

    // Clear the total before loading a new sales file.
    static void resetCorporateTotal();

    // Add one completed division's total.
    static void addToCorporateTotal(double amount);


    // Read or change a sales value using its index.
    double& operator[](int index);

    // Read a sales value from a const object.
    const double& operator[](int index) const;

};

#endif
#pragma once
