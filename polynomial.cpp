#include "polynomial.h"

Polynomial::Polynomial()
{ // default constructor
	head = new Term();
	head->next = head;
	head->prev = head;
} // default constructor

Polynomial::Polynomial(const Polynomial& p)
{ // copy constructor
	*this = p; // creates deep copy
} // copy constructor

Polynomial::~Polynomial()
{ // destructor
	Term* delNode = head->next;
	Term* next = delNode->next;

	while (delNode != head)
	{ // while
		delNode->next = nullptr;
		delNode->prev = nullptr;
		delete delNode;
		delNode = next;
		next = next->next;
	} // while

	delNode->next = nullptr;
	delNode->prev = nullptr;
	delete delNode;
	delNode = nullptr;
} // destructor

/*
* Description: finds power of first term to return the degree of polynomial.
* Preconditions: created a polynnomial object.
* Postconditions: returns the degree of the polynomial, 0 if only a dummy 
*					header exists.
*/
int Polynomial::degree() const
{ // degree
	return (head->next)->power;
} // degree

/*
* Description: iterates through list to find coefficient of the term with the 
*				paramter power.
* Preconditions: created a polynnomial object with the parameter power term.
* Postconditions: returns the coefficient of the term with the parameter power.
*					if there is no term with the parameter power, returns -1.
*/
double Polynomial::coefficient(const int power) const
{ // coefficient
	Term* current = head->next;

	while (current != head)
	{ // while
		if (current->power == power)
		{ // if
			return current->coeff;
		} // if
		current = current->next;
	} // while

	return 0;
} // coefficient

/*
* Description: changes the coefficient of the term with the parameter power.
*				if there is no term with the parameter power, a new term is
*				inserted into the list by calling the insert method. if the new
*				coefficient is 0 then the term is removed from the polynomial.
* Preconditions: created a polynnomial object and called method with valid
*					parameters for a polynomial.
* Postconditions: returns true if the coefficient was changed successfully
*					and false if the user tried to change the dummy header,
*					insert a term with a coefficient of 0, or remove from an
*					empty list.
*/
bool Polynomial::changeCoefficient(const double newCoefficient, const int power)
{ // changeCoefficient
	if (power < 0)
	{
		return false;
	}
	Term* current = head->next;

	while (current != head && current->power >= power)
	{ // while
		if (current->power == power)
		{ // if
			if (newCoefficient == 0)
			{ // if
				return remove(current);
			} // if
			else
			{ // else
				current->coeff = newCoefficient;
				return true;
			} // else
		} // if
		else
		{ // else
			current = current->next;
		} // else
	} // while

	return insert(current, newCoefficient, power);
} // changeCoefficient

/*
* Description: adds the calling polynomial to the parameter polynomial p
*				and returns the sum of the two poynomials in a new polynomial.
*				The addition is done like a merge where the terms are added in
*				order from highest power to lowest.
* Preconditions: created 2 polynnomial objects and called the addition operator
*					on two polynomials.
* Postconditions: if one of the lists has 0 terms then it returns the other
*					polynomial. if both polynomials have terms then method 
*					creates a new polynomial which stores the sum of the terms. 
*					returns the newly created polynomial after adding.
*/
Polynomial Polynomial::operator+(const Polynomial& p) const
{ // operator+
	if (this->size == 0)
	{ // if
		return p;
	} // if
	else if (p.size == 0)
	{ // else if
		return *this;
	} // else if

	Polynomial polynomial;
	Term* rhs = (p.head)->next;
	Term* lhs = (this->head)->next;
	Term* previous = polynomial.head;

	while (lhs != this->head && rhs != p.head) 
	// loops through until one polynomial has been added
	{ // while
		Term* sum = new Term();
		bool insert = false;
		// when the sum of two terms is 0 the term not inserted
		if (lhs->power == rhs->power)
		{ // if
			double newCoeff = lhs->coeff + rhs->coeff;
			if (newCoeff == 0)
			{ // if
				lhs = lhs->next;
				rhs = rhs->next;
				insert = true;
			} // if
			else
			{ // else
				sum->coeff = newCoeff;
				sum->power = lhs->power;
				lhs = lhs->next;
				rhs = rhs->next;
			} // else
		} // if
		else if (lhs->power > rhs->power)
		{ // else if
			sum->coeff = lhs->coeff;
			sum->power = lhs->power;
			lhs = lhs->next;
		} // else if
		else
		{ // else 
			sum->coeff = rhs->coeff;
			sum->power = rhs->power;
			rhs = rhs->next;
		} // else 
		if (insert == false)
		{ // if
			previous->next = sum;
			previous->prev = sum;
			sum->prev = previous;
			sum->next = polynomial.head;

			previous = previous->next;
			polynomial.size++;
		} // if
		else
		{
			insert = false;
		}
	} // while

	while (rhs != p.head) // loops through until right polynomial is added
	{ // while
		Term* sum = new Term();

		sum->coeff = rhs->coeff;
		sum->power = rhs->power;
		previous->next = sum;
		previous->prev = sum;
		sum->prev = previous;
		sum->next = polynomial.head;

		previous = previous->next;
		sum = sum->next;
		rhs = rhs->next;
		polynomial.size++;
	} // while

	while (lhs != this->head) // loops through until left polynomial is added
	{ // while
		Term* sum = new Term();

		sum->coeff = lhs->coeff;
		sum->power = lhs->power;
		previous->next = sum;
		previous->prev = sum;
		sum->prev = previous;
		sum->next = polynomial.head;

		previous = previous->next;
		sum = sum->next;
		lhs = lhs->next;
		polynomial.size++;
	} // while

	return polynomial;
} // operator+

/*
* Description: subtracts the polynomial p from the calling polynomial and 
*				returns the difference of the two poynomials in a new 
*				polynomial. The subtraction is done like a merge where the 
*				terms are subtracted in order from highest power to lowest.
* Preconditions: created 2 polynnomial objects and called the subtraction
*					operator on two polynomials.
* Postconditions: creates a new polynomial which stores the difference of the 
*					terms. returns the newly created polynomial after 
*					subtracting.
*/
Polynomial Polynomial::operator-(const Polynomial& p) const
{ // operator-
	Polynomial polynomial;
	Term* rhs = (p.head)->next;
	Term* lhs = (this->head)->next;
	Term* previous = polynomial.head;

	while (lhs != this->head && rhs != p.head)
	// loops until one polynomial has been subtracted
	{ // while
		Term* difference = new Term();
		bool insert = false; 
		// when the difference of two terms is 0 the term is not inserted
		if (lhs->power == rhs->power)
		{ // if
			double newCoeff = lhs->coeff - rhs->coeff;
			if (newCoeff == 0)
			{
				lhs = lhs->next;
				rhs = rhs->next;
				insert = true;
			}
			else
			{
				difference->coeff = newCoeff;
				difference->power = lhs->power;
				lhs = lhs->next;
				rhs = rhs->next;
			}
		} // if
		else if (lhs->power > rhs->power)
		{ // else if
			difference->coeff = lhs->coeff;
			difference->power = lhs->power;
			lhs = lhs->next;
		} // else if
		else
		{ // else
			difference->coeff = rhs->coeff * -1;
			difference->power = rhs->power;
			rhs = rhs->next;
		} // else
		if (insert == false)
		{
			previous->next = difference;
			previous->prev = difference;
			difference->prev = previous;
			difference->next = polynomial.head;
			previous = previous->next;
			difference = difference->next;
			polynomial.size++;
		}
		else
		{
			insert = false;
		}
		
	} // while

	while (rhs != p.head) // loops until right polynomial has been subtracted
	{ // while
		Term* difference = new Term();

		difference->coeff = rhs->coeff * -1;
		difference->power = rhs->power;
		previous->next = difference;
		previous->prev = difference;
		difference->prev = previous;
		difference->next = polynomial.head;

		previous = previous->next;
		difference = difference->next;
		rhs = rhs->next;
		polynomial.size++;
	} // while

	while (lhs != this->head) // loops until left polynomial has been subtracted
	{ // while
		Term* difference = new Term();

		difference->coeff = lhs->coeff;
		difference->power = lhs->power;
		previous->next = difference;
		previous->prev = difference;
		difference->prev = previous;
		difference->next = polynomial.head;

		previous = previous->next;
		difference = difference->next;
		lhs = lhs->next;
		polynomial.size++;
	} // while

	return polynomial;
} // operator-

/*
* Description: compares the calling polynomial to polynomial p by comparing 
*				each term and power to check for equality.
* Preconditions: created 2 polynnomial objects and called the equality
*					operator on two polynomials.
* Postconditions: returns true if the two polynomials are equal and false if
*					they are not.
*/
bool Polynomial::operator==(const Polynomial& p) const
{ // operator==
	if (this->size == 0 && p.size == 0)
	{ // if
		return true;
	} // if
	if (this->size != p.size)
	{ // if
		return false;
	} // if
	else
	{ // else
		Term* lhs = (this->head)->next;
		Term* rhs = (p.head)->next;

		while (lhs != this->head && rhs != p.head)
		{ // while
			if (lhs->coeff != rhs->coeff || lhs->power != rhs->power)
			{ // if
				return false;
			}// if
			lhs = lhs->next;
			rhs = rhs->next;
		} // while

		return true;
	} // else
} // operator==

/*
* Description: compares the calling polynomial to polynomial p by comparing
*				each term and power to check for equality.
* Preconditions: created 2 polynnomial objects and called the inequality
*					operator on two polynomials.
* Postconditions: returns true if the two polynomials are not equal and false 
*					if they are equal.
*/
bool Polynomial::operator!=(const Polynomial& p) const
{ // operator!=
	if (this->size == 0 && p.size == 0)
	{ // if
		return false;
	} // if
	if (this->size != p.size)
	{ // if
		return true;
	} // if
	else
	{ // else
		Term* lhs = (this->head)->next;
		Term* rhs = (p.head)->next;

		while (lhs != this->head && rhs != p.head)
		{ // while
			if (lhs->coeff != rhs->coeff || lhs->power != rhs->power)
			{ // if
				return true;
			}// if
			lhs = lhs->next;
			rhs = rhs->next;
		} // while

		return false;
	} // else
} // operator!=

/*
* Description: creates a deep copy of polynomial p and stores it in the calling
*				object.
* Preconditions: created 2 polynnomial objects and called the assignment
*					operator on two polynomials.
* Postconditions: if the two polynomials are the same object, thenm it returns
*					itself. otherwise, returns a polynomial containing the deep 
*					copy of p.
*/
Polynomial& Polynomial::operator=(const Polynomial& p)
{ // operator=
	if (this->head == nullptr)
	{ // if
		head = new Term();
		head->next = head;
		head->prev = head;
		head->coeff = 0;
		head->power = 0;
		this->size = 0;
	} // if
	if (p.size == 0)
	{ // if
		if (this->size != 0)
		{ // if
			this->removeAll();
		} // if
		return *this;
	} // if
	if (p == *this)
	{ // if
		return *this;
	} // if

	this->removeAll();
	Term* toCopy = (p.head)->next;
	Term* current = (this->head)->next;
	Term* previous = this->head;

	while (toCopy != p.head)
	{ // while
		Term* copy = new Term();
		copy->coeff = toCopy->coeff;
		copy->power = toCopy->power;
		previous->next = copy;
		current = copy;
		current->prev = previous;
		previous = previous->next;
		size++;
		toCopy = toCopy->next;
	} // while

	current->next = this->head;
	(this->head)->prev = current;
	return *this;
} // operator=

/*
* Description: adds the polynomial p to the calling polynomial
* Preconditions: created 2 polynnomial objects and called the addition 
*					assignment operator on two polynomials.
* Postconditions: Adds the two polynomials and modifies the calling polynomial
*					then returns the calling polynomial with the sum of the 
*					two polynomials.
*/
Polynomial& Polynomial::operator+=(const Polynomial& p)
{ // operator+=
	*this = *this + p;
	return *this;
} // operator+=

/*
* Description: subtracts the polynomial p from the calling polynomial
* Preconditions: created 2 polynnomial objects and called the subtraction
*					assignment operator on two polynomials.
* Postconditions: subtracts the two polynomials and modifies the calling 
					polynomial then returns the calling polynomial with the 
					difference of the two polynomials.
*/
Polynomial& Polynomial::operator-=(const Polynomial& p)
{ // operator-=
	*this = *this - p;
	return *this;
} // operator-=

/*
* Description: inserts a new Term with a newCoefficient and power just before
*				the pos term.
* Preconditions: created a polynnomial object and called the changeCoefficient
*					method with a power that is not yet in the polynomial.
* Postconditions: if the newCoefficient is 0 then return false, otherwise the
*					term with the newCoefficient and power is inserted into the
*					polynomial just before the pos term. the pointers of the
*					pos term and the term before it change to point to the
*					inserted term. the size is increased by one. returns true.
*/
bool Polynomial::insert(Term* pos, const double newCoefficient, const int power)
{ // insert
	if (newCoefficient == 0)
	{ // if
		return false;
	} // if
	Term* prevNode = pos->prev;
	Term* insNode = new Term();

	prevNode->next = insNode;
	insNode->coeff = newCoefficient;
	insNode->power = power;
	insNode->next = pos;
	insNode->prev = prevNode;
	pos->prev = insNode;

	this->size++;
	return true;
} // insert

/*
* Description: removes the term specified by the argument pos.
* Preconditions: created a polynnomial object and called the changeCoefficient
*					method with newCoefficient of 0, on an existing term power.
* Postconditions: if the size of the polynomial is 0 then it returns false,
					otherwise the term pointed to by pos is removed and the 
					pointers of the previous and next nodes are changed to
					point to each other.
*/
bool Polynomial::remove(Term* pos)
{ // remove
	if (size == 0)
	{ // if
		return false;
	} // if
	Term* prevNode = pos->prev;
	Term* nextNode = pos->next;

	pos->next = nullptr;
	pos->prev = nullptr;
	prevNode->next = nextNode;
	nextNode->prev = prevNode;
	delete pos;
	pos = nullptr;

	size--;
	return true;
} // remove

/*
* Description: removes all terms from the polynomial except for the dummy 
*				header.
* Preconditions: created a polynnomial object and called the assignment 
*					operator on two polynomials where the left one has to be
*					cleared before copying.
* Postconditions: all terms except the dummy header are removed from the 
*					polynomial then returns true. size is set back to 0.
*/
bool Polynomial::removeAll()
{ // removeAll
	Term* delNode = head->next;
	Term* next = delNode->next;

	while (delNode != head)
	{ // while
		delNode->next = nullptr;
		delNode->prev = nullptr;
		delete delNode;
		delNode = next;
		next = next->next;
	} // while

	delNode->next = delNode;
	delNode->prev = delNode;

	this->size = 0;
	return true;
} // removeAll

