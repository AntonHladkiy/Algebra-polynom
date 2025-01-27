/*!
 * @file Polynom.h
 * @brief Header file for class Polynom
 * @details Definition of the class Polynom
 */

#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include "../Matrix/Matrix.h"

 /*!
  * @brief class Polynom that describes polynomial
  * @details 
  * polynomials in field p^n (p - prime)
  * coefficient             by (mod p)
  * power of this polinom -         n
  * Every object contains with terms (PolyTerm)
  * Every structure "PolyTerm" have objects that contains fields "key" and "next"
  * key - coefficient of term
  * next - pointer to next object of structure "PolyTerm"
  */
class Polynom {
private:
    long long prime;    // p
    long long power;    // n
    // Structure that describes term of Polynom
    struct PolyTerm {
        long long key;      // Coefficient of terms of polynomial
        long long pow;      // Power of term
        PolyTerm* next;     // Pointer to next term
    };
    PolyTerm* head;         // Pointer to the first term of polynom

public:
    /*constructors*/
    Polynom();
    Polynom(long long _prime, long long _power, std::vector<long long> keys);   //for all terms
    Polynom(long long _prime, long long _power, std::vector<std::vector<long long>> keys); //for some terms
    /*destructor*/
    ~Polynom() { }

    /*Getters and Setters*/
    PolyTerm* getHead() const { return head; }
    PolyTerm* getTerm(long long pow) const {    //retuns term by its power
        PolyTerm* tmp = head;
        if (head == nullptr) return nullptr;
        while (tmp) {
            if (tmp->pow == pow) return tmp;
            tmp = tmp->next;
        }
        return nullptr;
    }
    long long getTermKey(long long pow) const {    //retuns coef of a term by its power
        PolyTerm* term = getTerm(pow);
        if (term) return term->key;
        return 0;
    }
    // return power of a field
    long long getPower() const { return power; } 
    long long getPrime() const { return prime; }
    void setHead(PolyTerm* _head) { head = _head; }
    void setPower(long long _power) { power = _power; }
    void setPrime(long long _prime) { prime = _prime; }
    void copy(const Polynom pol) {
        prime = pol.getPrime();
        power = pol.getPower();
        head = nullptr;
        PolyTerm* tmp = pol.getHead();
        while (tmp) {
            addItem(makeItem(tmp->pow, tmp->key));
            tmp = tmp->next;
        }
    };
    std::string show() const;
    // return power of a polinomial
    long long getPolyPower() const {
        long long pow = 0;
        PolyTerm* tmp = head;
        if (head == nullptr) return pow;
        while (tmp) {
            if (tmp->pow > pow) { pow = tmp->pow; }
            tmp = tmp->next;
        }
        return pow; 
    }
    // Creates new term (PolyTerm) with coefficient val
    PolyTerm* makeItem(long long pow, long long val);
    // Adding term to the polynom in non-descending order
    void addItem(PolyTerm* el);
    
    /** #1      @author Daryna Bondarets    **/
    /*! #1
    * @brief Adding two polynomials in field
    */
    friend Polynom operator +(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Difference of two polynomials in field
    */
    friend Polynom operator -(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Multiplication of two polynomials in field
    */
    friend Polynom operator *(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Multiplicates polynomial in field on integer
    */
    friend Polynom operator *(Polynom const& p, long long const& number);
    friend Polynom operator *(long long const &number, Polynom const& p);
	/* #6
	* @brief Divides polynomial in field
	*/
	friend Polynom operator /(Polynom const& p1, Polynom const& p2);
	/* #6
	* @brief Get rest from the divison of polinomials
	*/
	friend Polynom operator %(Polynom const& p1, Polynom const& p2);
    /** #2      @author Darik Ivashyn    **/
    //...
    Polynom derivative() const;
    long long valueAtPoint(long long x) const;
    void normalization();
    /** #3      @author Karina Masol & Yuriy Momotenko     **/
    //...

    /** #4      @author Yana Skyrda    **/
    /*! #4
    * @brief This function implements algorithm  for finding number of roots for polynomial
    *        in accordance with Konig-Rados theorem
    */
    long long rootsNumber();

	/** #7      @author Nikita Pupov    **/
	/*! #7
	* @brief This method calculates greatest common divisor of two polynoms
	*/
	Polynom gcd(Polynom p);

    /* #9
    * @brief Equal operator
    */
    friend bool operator ==(Polynom const& p1, Polynom const& p2);

    /** #9      @author Rostyslav Mochulskyi   **/
    /*! #9
    * @brief This method calculates nth �yclotomic polynomial
    */
    static Polynom CyclotomicPolynomial(int prime, int n);

    /*! #10
     * @author Hryshchenko Yurii
     * @brief Gets irreducible factors of nth cyclomotic polynomial using Ri polynomials
     */
    std::vector<Polynom> factorizeCyclotomicRi(size_t n);


    /*! #5
    * @author Yaroslava Levchuk Natalia Makarenko
    * @brief This function implements algorithm  for finding invers
    */
    Polynom inversPoly(long long number, Polynom const& pol1);

    long long gcdforinvers(long long a, long long b, long long* x, long long* y);

protected:
    /*! #1
    * @brief Adding two polynomials in field
    */
    Polynom addPoly(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Difference of two polynomials in field
    */
    Polynom diffPoly(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Multiplication of two polynomials in field
    */
    Polynom multPoly(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Multiplication of two polynomials in field with power=1
    */
    Polynom multSimple(Polynom const& p1, Polynom const& p2);
    /*! #1
    * @brief Multiplicates polynomial in field on integer
    */
    Polynom multNumber(Polynom const& p, long long const& number);


	/*! #6
	* @brief Multiplication of two polynomials in field 
	*/
	Polynom multPolyforDivide(Polynom const& p1, Polynom const& p2);
	/*! #6
	* @brief Division
	*/
	std::pair<Polynom, Polynom> simple_division(Polynom const & p1, Polynom const & p2) const;
	/*! #6
	* @brief Division for numbers
	*/
	long long division_for_numbers(long long a, long long b, long long prime);
	/*! #6
	* @brief Inverse for numbers
	*/
	long long inverse(long long number, long long prime);
    /*! #9
    * @brief Function to check if n is prime or not 
    */
    static bool isPrime(int n);

    /*! #9
   * @brief Mobius Function
   */
    static int mobius(int N);
};

std::vector<long long> euclideanAlgorithm(long long a, long long b, int prime);
