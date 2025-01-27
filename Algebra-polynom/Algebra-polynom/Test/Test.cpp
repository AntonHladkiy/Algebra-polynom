#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Polynom/Polynom.h"
#include <vector>

TEST_CASE("Polynomial")
{
    SUBCASE("Creating polynom")
    {
        Polynom polynomial1(3, 1, {{0, 1}, {2, 2}});
        REQUIRE(polynomial1.show() == "1 + 2*x^2");
        Polynom polynomial(3, 2, {1, 2});
        REQUIRE(polynomial.show() == "1 + 2*x");
    }
    SUBCASE("Creating empty polynom")
    {
        Polynom polynomial(3, 2, {3, 6});
        REQUIRE(polynomial.getHead() == nullptr);
    }
    SUBCASE("Creating copy of polynom")
    {
        Polynom polynomial(3, 2, {1, 2});
        Polynom copy;
        copy.copy(polynomial);
        REQUIRE(polynomial.show() == copy.show());
        REQUIRE(polynomial.getPower() == copy.getPower());
        REQUIRE(polynomial.getPrime() == copy.getPrime());
    }
    SUBCASE("Power of polynom")
    {
        Polynom poly1(3, 1, {1, 3, 3});
        REQUIRE(poly1.getPolyPower() == 0);
        Polynom poly2(3, 1, {1, 1});
        REQUIRE(poly2.getPolyPower() == 1);
        Polynom poly3(3, 1, {1, 1, 1});
        REQUIRE(poly3.getPolyPower() == 2);
    }
    SUBCASE("Adding polynoms")
    {
        Polynom poly1(3, 2, {1, 2});
        Polynom poly2 = poly1 + poly1;
        REQUIRE(poly1.show() == "1 + 2*x");
        REQUIRE(poly2.show() == "2 + 1*x");
        REQUIRE((poly1 + poly2).show() == "");
    }
    SUBCASE("Substract polynoms")
    {
        Polynom poly1(3, 2, {1, 2});
        Polynom poly2(3, 2, {2, 2});
        REQUIRE((poly1 - poly1).show() == "");
        REQUIRE((poly1 - poly2).show() == "2");
    }
    SUBCASE("Multiplicate polynoms")
    {
        Polynom poly1(3, 1, {1, 2});
        REQUIRE(poly1.show() == "1 + 2*x");

        REQUIRE(poly1.getTermKey(0) == 1);
        REQUIRE(poly1.getTermKey(1) == 2);
        REQUIRE(poly1.getTermKey(2) == 0);

        Polynom polynomial = poly1 * poly1;
        REQUIRE(polynomial.show() == "1 + 1*x + 1*x^2");

        /*it`s wrong but just for test*/
        Polynom poly2(3, 2, {1, 2});
        polynomial = poly2 * poly2;
        REQUIRE(polynomial.show() == "1 + 1*x + 1*x^2");

        //Polynom poly3(3, 2, { 1,1 });
        //polynomial = poly2 * poly3;
        //REQUIRE(polynomial.getTerm(0)->key == 2);

        polynomial = poly1 * 3;
        REQUIRE(polynomial.show() == "");
    }

    SUBCASE("GCD polynoms") {
	    Polynom pol1(3, 4, { 1,0,0,0,1 });
	    Polynom pol2(3, 3, { 1,1,0,1 });

	    Polynom res = pol1.gcd(pol2);

	    REQUIRE(res.show() == "1 + 2*x + 2*x^2");
    }
}
TEST_CASE("Division") {
    SUBCASE("/ operation")
    {
        SUBCASE("example 1") {
            Polynom polynom1(3, 3, { 3, 7, 10, 1, 0, 3, 4 });
            Polynom polynom2(3, 3, { 2,1,5 });
            Polynom result = polynom1 / polynom2;
            REQUIRE(result.show() == "2 + 2*x^3 + 2*x^4");
        }

        SUBCASE("example 2") {
            Polynom polynom1(3, 3, { 3, 7, 10, 1, 0, 3, 4 });
            Polynom polynom2(3, 3, { 2,1,5 });
            Polynom result = polynom2 / polynom1;
            REQUIRE(result.show() == "");
        }
        SUBCASE("example 3") {
            Polynom polynom1(17, 3, { 20, 34, 65, 43, 53 });
            Polynom polynom2(17, 3, { 37,56,67,27,14 });
            Polynom result = polynom1 / polynom2;
            REQUIRE(result.show() == "5");
        }
        SUBCASE("example 4") {
            Polynom polynom1(17, 3, { 20, 34, 65, 43, 53,43,51,60 });
            Polynom polynom2(17, 3, { 37,56,67,27,14 });
            Polynom result = polynom1 / polynom2;
            REQUIRE(result.show() == "14 + 10*x + 7*x^2 + 14*x^3");
        }
        SUBCASE("example 5") {
            Polynom polynom1(17, 3, { 20, 34, 65, 43, 53,43,51,60 });
            Polynom polynom2(17, 3, { 37,56,67,27,57,86,39 });
            Polynom result = polynom1 / polynom2;
            REQUIRE(result.show() == "1 + 12*x");
        }
    }
    SUBCASE("% operation")
    {
        SUBCASE("example 1") {
            Polynom polynom1(3, 3, { 3, 7, 10, 1, 0, 3, 4 });
            Polynom polynom2(3, 3, { 2,1,5 });
            Polynom result = polynom1 % polynom2;
            REQUIRE(result.show() == "2 + 2*x");
        }

        SUBCASE("example 2") {
            Polynom polynom1(3, 3, { 3, 7, 10, 1, 0, 3, 4 });
            Polynom polynom2(3, 3, { 2,1,5 });
            Polynom result = polynom2 % polynom1;
            REQUIRE(result.show() == "2 + 1*x + 2*x^2");
        }
        SUBCASE("example 3") {
            Polynom polynom1(17, 3, { 20, 34, 65, 43, 53 });
            Polynom polynom2(17, 3, { 37,56,67,27,14 });
            Polynom result = polynom1 % polynom2;
            REQUIRE(result.show() == "5 + 9*x + 2*x^2 + 10*x^3");
        }
        SUBCASE("example 4") {
            Polynom polynom1(17, 3, { 20, 34, 65, 43, 53,43,51,60 });
            Polynom polynom2(17, 3, { 37,56,67,27,14 });
            Polynom result = polynom1 % polynom2;
            REQUIRE(result.show() == "12 + 2*x + 8*x^2 + 6*x^3");
        }
        SUBCASE("example 5") {
            Polynom polynom1(17, 3, { 20, 34, 65, 43, 53,43,51,60 });
            Polynom polynom2(17, 3, { 37,56,67,27,57,86,39 });
            Polynom result = polynom1 % polynom2;
            REQUIRE(result.show() == "10*x + 6*x^2 + 11*x^3 + 12*x^4 + 4*x^5");
        }
    }
}
TEST_CASE("Derivation")
{
    SUBCASE("First example")
    {
        Polynom polynom(11, 3, {3, 7, 10, 1, 0, 3, 4});
        REQUIRE(polynom.derivative().show() == "7 + 9*x + 3*x^2 + 4*x^4 + 2*x^5");
    }
    SUBCASE("Second example")
    {
        Polynom polynom(23, 2, {1, 2, 3, 4, 5, 6, 7});
        REQUIRE(polynom.derivative().show() == "2 + 6*x + 12*x^2 + 20*x^3 + 7*x^4 + 19*x^5");
    }
    SUBCASE("Third example")
    {
        Polynom polynom(93, 1, {1, 3, 7, 8, 2, 5, 0, 0, 7});
        REQUIRE(polynom.derivative().show() == "3 + 14*x + 24*x^2 + 8*x^3 + 25*x^4 + 56*x^7");
    }
}

TEST_CASE("Normalization")
{
    SUBCASE("First example")
    {
        Polynom polynom(29, 3, {4, 5, 1, 3, 0, 9});
        polynom.normalization();
        REQUIRE(polynom.getTermKey(5) == 1);
    }
    SUBCASE("First example")
    {
        Polynom polynom(97, 2, {4, 5, 1, 3, 0, 9, 8, 6, 2, 0, 0, 0, 1, 15, 96});
        polynom.normalization();
        REQUIRE(polynom.getTermKey(14) == 1);
    }
    SUBCASE("First example")
    {
        Polynom polynom(71, 3, {4, 5, 1, 3, 0, 9, 72});
        polynom.normalization();
        REQUIRE(polynom.getTermKey(6) == 1);
    }
}

TEST_CASE("Definition valua at a point")
{
    SUBCASE("First example")
    {
        Polynom polynom(17, 2, {1, 2, 3, 4, 5});
        REQUIRE(polynom.valueAtPoint(1) == 15);
        REQUIRE(polynom.valueAtPoint(-1) == 3);
        REQUIRE(polynom.valueAtPoint(0) == 1);
    }
    SUBCASE("First example")
    {
        Polynom polynom(91, 2, {15, 2, 3, 4, 5, 87, 61, 8});
        REQUIRE(polynom.valueAtPoint(3) == 857);
    }
}

TEST_CASE("Roots amount")
{
    SUBCASE("First example")
    {
        Polynom polynomial(5, 1, {1, 3, 0, 2});
        REQUIRE(polynomial.rootsNumber() == 0);
    }

    SUBCASE("Second example")
    {
        Polynom polynomial(5, 1, {1, 1, 1, 1});
        REQUIRE(polynomial.rootsNumber() == 3);
    }

    SUBCASE("Third example")
    {
        Polynom polynomial(5, 1, {1, 2, 2, 1});
        REQUIRE(polynomial.rootsNumber() == 1);
    }
}

TEST_CASE("Cyclotomic polynomials")
{
    SUBCASE("n=1")
    {
        Polynom polynomial(131, 1, {130, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 1) == polynomial);
    }
    SUBCASE("n=2")
    {
        Polynom polynomial(131, 1, {1, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 2) == polynomial);
    }
    SUBCASE("n=3")
    {
        Polynom polynomial(131, 1, {1, 1, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 3) == polynomial);
    }
    SUBCASE("n=4")
    {
        Polynom polynomial(131, 1, {1, 0, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 4) == polynomial);
    }
    SUBCASE("n=5")
    {
        Polynom polynomial(131, 1, {1, 1, 1, 1, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 5) == polynomial);
    }
    SUBCASE("n=6")
    {
        Polynom polynomial(131, 1, {1, 130, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 6) == polynomial);
    }
    SUBCASE("n=7")
    {
        Polynom polynomial(131, 1, {1, 1, 1, 1, 1, 1, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 7) == polynomial);
    }
    SUBCASE("n=8")
    {
        Polynom polynomial(131, 1, {1, 0, 0, 0, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 8) == polynomial);
    }
    SUBCASE("n=9")
    {
        Polynom polynomial(131, 1, {1, 0, 0, 1, 0, 0, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 9) == polynomial);
    }
    SUBCASE("n=10")
    {
        Polynom polynomial(131, 1, {1, 130, 1, 130, 1});
        REQUIRE(Polynom::CyclotomicPolynomial(131, 10) == polynomial);
    }
    SUBCASE("n=105")
    {
        std::vector<long long> keys(49, 0);
        keys[0] = 1;
        keys[1] = 1;
        keys[2] = 1;
        keys[5] = 130;
        keys[6] = 130;
        keys[7] = 129;
        keys[8] = 130;
        keys[9] = 130;
        for (int i = 12; i <= 17; i++)
        {
            keys[i] = 1;
        }
        for (int i = 20; i <= 28; i += 2)
        {
            keys[i] = 130;
        }
        for (int i = 31; i <= 36; i++)
        {
            keys[i] = 1;
        }
        keys[39] = 130;
        keys[40] = 130;
        keys[41] = 129;
        keys[42] = 130;
        keys[43] = 130;
        keys[46] = 1;
        keys[47] = 1;
        keys[48] = 1;
        Polynom polynomial(131, 1, keys);
        REQUIRE(Polynom::CyclotomicPolynomial(131, 105) == polynomial);
    }
}

TEST_CASE("Factorization of cyclotomic using Ri")
{
	SUBCASE("n = 52, q = 3")
	{
		int n = 52;
		int q = 3;
		Polynom cyclotomic = Polynom::CyclotomicPolynomial(q, n);
		std::vector<Polynom> factors = cyclotomic.factorizeCyclotomicRi(n);

		Polynom product = Polynom(q, 1, std::vector<long long>{ 1 });
		for (Polynom& factor : factors) {
			product = product * factor;
		}
		REQUIRE(product == cyclotomic);
	}
	SUBCASE("n = 18, q = 7")
	{
		int n = 18;
		int q = 7;
		Polynom cyclotomic = Polynom::CyclotomicPolynomial(q, n);
		std::vector<Polynom> factors = cyclotomic.factorizeCyclotomicRi(n);

		Polynom product = Polynom(q, 1, std::vector<long long>{ 1 });
		for (Polynom& factor : factors) {
			product = product * factor;
		}
		REQUIRE(product == cyclotomic);
	}
}
