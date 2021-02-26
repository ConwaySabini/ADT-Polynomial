// ----------------------- polynomialDriver.cpp -------------------------------

// @author Sabini Ethan 343

// @date January 1, 2020

// @modified January 17, 2020

// ----------------------------------------------------------------------------

// Purpose - This driver tests all of the methods and operators of the
// polynomial ADT.

// ----------------------------------------------------------------------------
#include <iostream>
using namespace std;

#include "polynomial.h"


int main()
{
	// Polynomials to test
	Polynomial p1, p2, p3, p4, p5, p6;

	// Insert Terms
	p1.changeCoefficient(0.5, 1);
	p1.changeCoefficient(1.24, 2);
	p1.changeCoefficient(3, 0);
	p1.changeCoefficient(-2.5, 4);
	p1.changeCoefficient(-6.7, 5);
	p1.changeCoefficient(14, 8);

	// Insert Terms
	p2.changeCoefficient(-1.2, 1);
	p2.changeCoefficient(35, 9);
	p2.changeCoefficient(4, 4);
	p2.changeCoefficient(8, 5);
	p2.changeCoefficient(5, 7);

	// Insert Terms
	p4.changeCoefficient(0, 0);
	p4.changeCoefficient(0, 1);
	p4.changeCoefficient(6.7, 2);
	p4.changeCoefficient(-7, -2);
	p4.changeCoefficient(74, 3);
	p4.changeCoefficient(200, 4);
	p4.changeCoefficient(45, 9);
	p4.changeCoefficient(-6.25, 14);

	// Test Addition, Subtraction, Addition Assignment, Subtraction Assignment,
	// and Assignment operators
	p3 += p2;
	p2 = p1 + p2;
	p4 -= p1;
	p5 = p4;
	p6 = p2;

	// Test degree and coefficient methods
	int degree1 = p1.degree();
	int degree2 = p2.degree();
	int degree3 = p4.degree();
	double coeff = p2.coefficient(9);
	double coeff2 = p2.coefficient(0);
	double coeff3 = p2.coefficient(4);

	// Test equality
	bool equal = false;
	if (p5 == p4)
	{
		equal = true;
	}

	p4 = p3 + p4;

	// Test inequality
	bool equal2 = true;
	if (p5 != p4)
	{
		equal2 = false;
	}

	// Test equality
	bool equal3 = false;
	if (p6 == p2)
	{
		equal3 = true;
	}

	// Test inequality
	bool equal4 = true;
	if (p6 != p5)
	{
		equal4 = false;
	}

	// Prints test results to the console
	cout << "ADT Polynomial Driver" << endl;
	cout << endl;

	cout << "p1: degree: " << degree1 << endl;
	cout << "Expected: 8" << endl;
	cout << endl;

	cout << "p2: degree: " << degree2 << endl;
	cout << "Expected: 9" << endl;
	cout << endl;

	cout << "p4: degree: " << degree3 << endl;
	cout << "Expected: 14" << endl;
	cout << endl;

	cout << "p2: coefficient of 9: " << coeff << endl;
	cout << "Expected: 35" << endl;
	cout << endl;

	cout << "p2: coefficient of 0: " << coeff2 << endl;
	cout << "Expected: 3" << endl;
	cout << endl;

	cout << "p2: coefficient of 4: " << coeff3 << endl;
	cout << "Expected: 1.5" << endl;
	cout << endl;

	cout << "p5 == p4: " << equal << endl;
	cout << "Expected: True" << endl;
	cout << endl;

	cout << "p5 != p4: " << equal2 << endl;
	cout << "Expected: False" << endl;
	cout << endl;

	cout << "p6 == p2: " << equal3 << endl;
	cout << "Expected: True" << endl;
	cout << endl;

	cout << "p6 != p5: " << equal4 << endl;
	cout << "Expected: False" << endl;
	cout << endl;

	cout << "p1: " << p1 << endl;
	cout << "Expected: 14x^8-6.7x^5-2.5x^4 + 1.24x^2 + 0.5";
	cout << "*x ^ 1 + 3" << endl;
	cout << endl;

	cout << "p2: " << p2 << endl;
	cout << "Expected: 35x^9 + 14x^8 + 5x^7 + 1.3x^5 + 1.5x^4";
	cout << "+ 1.24 * x^2 + -0.7 * x^1 + 3" << endl;
	cout << endl;

	cout << "p3: " << p3 << endl;
	cout << "Expected: 35x^9 + 5x^7 + 8x^5 + 4x^4 + -1.2x";
	cout << endl;
	cout << endl;

	cout << "p4: " << p4 << endl;
	cout << "Expected: -6.25x^14 + 80x^9-14x^8 + 5x^7 + 14.7";
	cout << "*x ^ 5 + 206.5x^4 + 74x^3 + 5.46x^2-1.7x^";
	cout << "1-3" << endl;
	cout << endl;

	cout << "p5: " << p5 << endl;
	cout << "Expected: -6.25x^14 + 45x^9-14x^8 + 6.7x^5 + ";
	cout << "202.5x^4 + 74x^3 + 5.46x^2-0.5x-3" << endl;
	cout << endl;

	// Test remove() by removing all Terms
	p1.changeCoefficient(0, 0);
	p1.changeCoefficient(0, 1);
	p1.changeCoefficient(0, 4);
	p1.changeCoefficient(0, 8);
	p1.changeCoefficient(0, 5);
	p1.changeCoefficient(0, 2);

	// Print remove test results
	cout << "p1: " << p1 << endl;
	cout << "Expected: " << endl;
	cout << endl;
}
