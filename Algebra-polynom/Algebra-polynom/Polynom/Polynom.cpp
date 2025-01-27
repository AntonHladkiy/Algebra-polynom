/*!
 * @file Polynom.cpp
 * @brief Implementation of class Polynom
 * @details Functional of polynomial
 */

#include "Polynom.h"
#include "utils.h"
#include <list>

using std::cout;
using std::cin;
using std::endl;

Polynom::Polynom() {
    head = nullptr;
    power = 1;
    prime = 1;
}

Polynom::Polynom(long long _prime, long long _power, std::vector<long long> keys) : prime(_prime), power(_power) {
    head = nullptr;
    for (int i = 0; i < keys.size(); i++) {
        addItem(makeItem(i, keys[i]));
    }
}

Polynom::Polynom(long long _prime, long long _power, std::vector<std::vector<long long>> keys) : prime(_prime), power(_power) {
    head = nullptr;
    for (int i = 0; i < keys.size(); i++) {
        addItem(makeItem(keys[i][0], keys[i][1]));
    }
}

Polynom::PolyTerm *Polynom::makeItem(long long pow, long long value) {
    auto *el = new PolyTerm;
    el->key = value;
    el->pow = pow;
    el->next = nullptr;
    return el;
}

void Polynom::addItem(Polynom::PolyTerm *el) {
    el->key = el->key % prime;
    if (el->key < 0) el->key += prime;
    if (el->key != 0) {
        //checks if polinom is empty
        if (head == nullptr) {
            head = el;
            return;
        }
        PolyTerm *t = head;
        //checks if polinoms head
        if (t->pow == el->pow) {
            t->key = (t->key + el->key) % prime;
            if (t->key == 0) {
                head = t->next;
                //delete t;
            }
            return;
        } else if (t->pow > el->pow) {
            el->next = t;
            head = el;
            return;
        }
        //checks the rest terms of polinom
        PolyTerm *t1 = t->next;
        while (t1) {
            if (t1->pow == el->pow) {
                t1->key = (t1->key + el->key) % prime;
                if (t1->key == 0) {
                    //delete t->next;
                    t->next = t1->next;
                }
                return;
            } else if (t1->pow > el->pow) {
                t->next = el;
                el->next = t1;
                return;
            }
            t = t1;
            t1 = t1->next;
        }
        t->next = el;
        el->next = nullptr;

    }
}

std::string Polynom::show() const {
    std::string answer;
    PolyTerm *tmp = head;
    bool isFirst = true;
    while (tmp != nullptr) {
        if (!isFirst) { answer += " + "; }
        else { isFirst = false; }
        answer += std::to_string(tmp->key);
        if (tmp->pow != 0) 
            (tmp->pow == 1) 
            ? answer += "*x" 
            : answer += "*x^" + std::to_string(tmp->pow);
        tmp = tmp->next;
    }
    return answer;
}

/*1     operation +       */
Polynom Polynom::addPoly(Polynom const &pol1, Polynom const &pol2) {
    Polynom pol3;
    pol3.copy(pol1);
    PolyTerm *tmp = pol2.getHead();
    while (tmp) {
        pol3.addItem(makeItem(tmp->pow, tmp->key));
        tmp = tmp->next;
    }
    return pol3;
}

/*1     operation +       */
Polynom operator+(Polynom const &pol1, Polynom const &pol2) {
    Polynom c = c.addPoly(pol1, pol2);
    return c;
}

/*1     operation -       */
Polynom Polynom::diffPoly(Polynom const &pol1, Polynom const &pol2) {
    Polynom pol3;
    pol3.copy(pol1);
    PolyTerm *tmp = pol2.getHead();
    while (tmp) {
        pol3.addItem(makeItem(tmp->pow, -tmp->key));
        tmp = tmp->next;
    }
    return pol3;
}

/*1     operation -       */
Polynom operator-(Polynom const &pol1, Polynom const &pol2) {
    Polynom c = c.diffPoly(pol1, pol2);
    return c;
}

/*1     operation *       */
Polynom Polynom::multPoly(Polynom const &pol1, Polynom const &pol2) {

    if (power == 1) {
        return multSimple(pol1, pol2);
    } else {
        //TODO: mult when power>1
        Polynom result = multSimple(pol1, pol2);
        // result % irredus pol with power of result pol
        return result;
    }

}

/*1     operation * (for n=1)      */
Polynom Polynom::multSimple(Polynom const &pol1, Polynom const &pol2) {
    long long pow = pol1.getPolyPower() + pol2.getPolyPower() + 1;
    std::vector<long long> num(pow, 0);
    PolyTerm *tmp1 = pol1.getHead();
    PolyTerm *tmp2 = pol2.getHead();

    while (tmp1) {
        while (tmp2) {
            num[tmp1->pow + tmp2->pow] = num[tmp1->pow + tmp2->pow] + (tmp1->key * tmp2->key);
            tmp2 = tmp2->next;
        }
        tmp1 = tmp1->next;
        tmp2 = pol2.getHead();
    }

    return Polynom(pol1.getPrime(), 1, num);
}

/*1     operation *       */
Polynom operator*(Polynom const &pol1, Polynom const &pol2) {
    Polynom c = c.multPoly(pol1, pol2);
    return c;
}

/*1     operation * (number)      */
Polynom Polynom::multNumber(Polynom const &p, long long const &number) {
    Polynom result;
    result.setPower(p.getPower());
    result.setPrime(p.getPrime());
    PolyTerm *tmp = p.getHead();
    while (tmp) {
        result.addItem(makeItem(tmp->pow, (tmp->key * number)));
        tmp = tmp->next;
    }
    return result;
}

/*2    derivative */

Polynom Polynom::derivative() const {
    Polynom answer;
    answer.copy(*this);
    auto node = answer.getHead();
    if (node->pow == 0) {
        answer.setHead(node->next);
        auto tmp = node->next;
        delete node;
        node = tmp;
    }
    while (node) {
        node->key *= node->pow;
        node->key %= answer.getPrime();
        --node->pow;
        node = node->next;
    }
    return answer;

}

/*2     Define value of polynom at a point */
long long Polynom::valueAtPoint(long long x) const {
    long long answer{0};
    auto node = this->head;
    while (node) {
        long long addition{node->key};
        for (int i = 0; i < node->pow; ++i) {
            addition *= x;
            addition %= long(std::pow(this->prime, this->power));
        }
        answer += addition;
        answer %= long(std::pow(this->prime, this->power));
        //std::cout << answer << std::endl;
        node = node->next;
    }
    return answer;
}

/* 2  normalization of polynomial*/

std::vector<long long> euclideanAlgorithm(long long a, long long b, int prime) {
    std::vector<long long> answer;
    answer.push_back(0);
    answer.push_back(0);
    answer.push_back(0);
    if (b > a) {
        long long pocket = a;
        a = b;
        b = pocket;
    }
    if (b == 0) {
        answer[0] = a;
        answer[1] = 1;
        answer[2] = 0;
        return answer;
    }
    long long x2 = 1, x1 = 0,
            y2 = 0, y1 = 1;
    while (b >= 1) {
        long long q{0};
        q = a / b;
        long long r = a - q * b;
        answer[1] = x2 - q * x1;
        answer[2] = y2 - q * y1;
        a = b;
        b = r;
        x2 = x1;
        x1 = answer[1];
        y2 = y1;
        y1 = answer[2];
    }
    a %= prime;
    x2 %= prime;
    y2 %= prime;
    if (a < 0) a += prime;
    if (x2 < 0) x2 += prime;
    if (y2 < 0) y2 += prime;
    answer[0] = a;
    answer[1] = x2;
    answer[2] = y2;
    return answer;
}

void Polynom::normalization() {
    auto node = this->head;
    while (node->next) node = node->next;
    long long inv = euclideanAlgorithm(node->key, this->prime, this->prime)[2];
    node = this->head;
    while (node) {
        node->key *= inv;
        node->key %= prime;
        node = node->next;
    }
}

/*6 divisions for numbers in field*/
long long Polynom::division_for_numbers(long long a, long long b, long long prime) {
    a *= inverse(b, prime);
    return a;
}

long long Polynom::inverse(long long number, long long prime) {
    long long a = number;
    long long b = prime;
    long long a_1 = 1;
    long long b_1 = 0;
    long long result = 0;
    while ((a != 1) && (b != 1)) {
        if ((a == 0) || (b == 0)) {
            return 0;
        }
        if (a >= b) {
            while (a >= b) {
                a-= b;
                a_1 -= b_1;
            }
        } else {
            while (b >= a) {
                b -= a;
                b_1 -= a_1;
            }
        }
    }
    if (a == 1) {
        result = a_1;
    } else {
        result = b_1;
    }
    result %= prime;
    if (result < 0) {
        result += prime;
    }
    return result;
}

/*9 Function to check if n is prime or not*/
bool Polynom::isPrime(int n) {
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

/*9 Mobius Function */
int Polynom::mobius(int N) {
    // Base Case
    if (N == 1)
        return 1;
    // For a prime factor i check if i^2 is also
    // a factor.
    int p = 0;
    for (int i = 1; i <= N; i++) {
        if (N % i == 0 && isPrime(i)) {
            // Check if N is divisible by i^2
            if (N % (i * i) == 0)
                return 0;
            else
                // i occurs only once, increase p
                p++;
        }
    }
    // All prime factors are contained only once
    // Return 1 if p is even else -1
    return (p % 2 != 0) ? -1 : 1;
}

/*6 operation for division*/
Polynom Polynom::multPolyforDivide(Polynom const &pol1, Polynom const &pol2) {
    long long pow = pol1.getPolyPower() + pol2.getPolyPower() + 1;
    std::vector<long long> num(pow, 0);
    PolyTerm *tmp1 = pol1.getHead();
    PolyTerm *tmp2 = pol2.getHead();

    while (tmp1) {
        while (tmp2) {
            num[tmp1->pow + tmp2->pow] = num[tmp1->pow + tmp2->pow] + (tmp1->key * tmp2->key);
            tmp2 = tmp2->next;
        }
        tmp1 = tmp1->next;
        tmp2 = pol2.getHead();
    }

    return Polynom(pol1.getPrime(), pow, num);
}

/*1     operation * (number)      */
Polynom operator*(Polynom const &p, long long const &number) {
    Polynom c = c.multNumber(p, number);
    return c;
}

/*1     operation * (number)      */
Polynom operator*(long long const &number, Polynom const &p) {
    Polynom c = c.multNumber(p, number);
    return c;
}

std::pair<Polynom, Polynom> Polynom::simple_division(Polynom const &p1, Polynom const &p2) const {
    Polynom result(p1.getPrime(), p1.getPower(), std::vector<long long>{0});
    Polynom rest;
    Polynom temp_1 = p1;
    Polynom temp_2 = p2;
    while (temp_1.getPolyPower() >= temp_2.getPolyPower()) {
        Polynom multiply(p1.getPrime(), p1.getPower(), std::vector<long long>{0});
        multiply.addItem(multiply.makeItem(temp_1.getPolyPower() - temp_2.getPolyPower(),
                                           temp_1.division_for_numbers(temp_1.getTermKey(temp_1.getPolyPower()),
                                                                       temp_2.getTermKey(temp_2.getPolyPower()),
                                                                       p2.getPrime())));
        temp_2 = temp_2.multPolyforDivide(temp_2, multiply);
        temp_1 = temp_1 - temp_2;
        temp_2 = p2;
        result = result + multiply;
    }
    rest = temp_1;
    return std::pair<Polynom, Polynom>(result, rest);
}

/*1     operation / (number)      */
Polynom operator/(Polynom const &p1, Polynom const &p2) {
    return p1.simple_division(p1, p2).first;
}

/*1     operation % (number)      */
Polynom operator%(Polynom const &p1, Polynom const &p2) {
    return p1.simple_division(p1, p2).second;
}

/*9 Equal operator*/
bool operator==(Polynom const &p1, Polynom const &p2) {
    Polynom::PolyTerm *cur1 = p1.getHead();
    Polynom::PolyTerm *cur2 = p2.getHead();
    while (cur1 != nullptr && cur2 != nullptr) {
        if (cur1->key != cur2->key)
            return false;
	if (cur1->pow != cur2->pow)
	    return false;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    if (cur1 != nullptr || cur2 != nullptr)
	    return false;
    return true;
}


/**/

/*4     Number of roots       */
long long Polynom::rootsNumber() {
    long long pow = getPolyPower() + 1;
    Matrix AMatrix(pow, pow);

    for (long long i = 0, shift = 0; i < pow; i++, shift++) {
        for (long long j = 0; j < pow; j++) {
            AMatrix.setElement(i, j, getTermKey((j + shift) % pow));
        }
    }

    long long matrixRank = AMatrix.rank();
    return (pow - matrixRank);
}

Polynom Polynom::gcd(Polynom p2) {
    Polynom p1(*this);
    while (p1.getPolyPower() != 0 && p2.getPolyPower() != 0) {
        if (p1.getPolyPower() > p2.getPolyPower()) {
            p1 = p1 % p2;
        } else {
            p2 = p2 % p1;
        }
    }

    if (p1.getPolyPower() == 0 && p1.getTermKey(0) == 0) {
        return p2;
    }

    return p1;
}

/*9 This method calculates nth Cyclotomic polynomial*/
Polynom Polynom::CyclotomicPolynomial(int prime, int n) {
    // if (n % prime == 0) return Polynom();
    std::vector<long long> keys{1};
    Polynom result(prime, 1, keys);
    int mob;
    if (isPrime(n))
        return Polynom(prime, 1, std::vector<long long>(n, 1));
    for (int d = 1; d <= n; d++) {
        if (n % d == 0 && mobius(n / d) == 1) {
            std::vector<long long> keys(d + 1, 0);
            keys[d] = 1;
            keys[0] = -1;
            Polynom multiplier(prime, 1, keys);
            result = result * multiplier;
        }
    }
    for (int d = 1; d <= n; d++) {
        if (n % d == 0 && mobius(n / d) == -1) {
            std::vector<long long> keys(d + 1, 0);
            keys[d] = 1;
            keys[0] = -1;
            Polynom divider(prime, 1, keys);
            result = result / divider;
        }
    }
    return result;
}

/* 10 Factorization using Ri */
std::vector<Polynom> Polynom::factorizeCyclotomicRi(size_t n) {
	//Find number of factors
	size_t d = 1;
	size_t dPow = prime;
	do {
		//std::cout << "d = " << d << std::endl;
		//std::cout << ((long long)(std::pow(prime, d)) % n) << std::endl;
		d++;
		dPow = (dPow * prime) % n;
	} while (dPow != 1);
	

	std::vector<Polynom> factors;
	std::list<Polynom> polysToFactorize;
	polysToFactorize.emplace_back();
	polysToFactorize.back().copy(*this);

	size_t factorsCount = utils::euler(n) / d;	
	size_t factorPower = getPolyPower() / factorsCount;		
	if (factorsCount == 1) {
		factors.emplace_back();
		factors[0].copy(*this);
		return factors;
	}
	//std::cout << "Factors count: " << factorsCount << std::endl;
	//std::cout << "Factors power: " << factorPower << std::endl;

	size_t i = 1;
	while (factors.size() < factorsCount) {
		//std::cout << "Trying R" << i << std::endl;
		Polynom riPolynomial = Polynom(prime, 1, std::vector<long long>());
		long long j = 1;

		PolyTerm* currentTerm = makeItem(i, 1);
		riPolynomial.head = currentTerm;

		long long mod = n / utils::gcd(n, i);
		while ((long long)std::pow(prime, j) % mod != 1) {
			currentTerm->next = makeItem(i * (long long)std::pow(prime, j), 1);

			currentTerm = currentTerm->next;
			j++;
		}
		currentTerm->next = nullptr;

		bool factorized = false;
		j = 0;
		while (j < prime) {
			//std::cout << "====\n";
			//std::cout << polysToFactorize.front().show() << std::endl;
			//std::cout << riPolynomial.show() << std::endl;

			Polynom gcdRi = polysToFactorize.front().gcd(riPolynomial);

			//std::cout << gcdRi.show() << std::endl;
			//std::cout << "====\n";

			//check if Ri = 0 (mod Q)
			if (j == 0 && gcdRi == polysToFactorize.front()) {
				factorized = false;
				break;
			}

			long long gcdPower = gcdRi.getPolyPower();
			if (gcdPower == factorPower) {
				factorized = true;
				gcdRi.normalization();
				factors.push_back(gcdRi);
			} else if (gcdPower % factorPower == 0) {
				factorized = true;
				polysToFactorize.push_back(gcdRi);
			}

			riPolynomial = riPolynomial + Polynom(prime, 1, std::vector<long long>(1, 1));
			j++;
		}
		if (factorized) {
			polysToFactorize.pop_front();
		}
		i++;

	}

	return factors;
}

/*5 Inverse of a polynomial in field
Знаходження оберненого многочлена*/
/*
{
  Polynom tar;
  Polynom irr;
  Polynom div;
  Polynom rem;
  Polynom res;
  int i = 1;
  tar.copy(pol1);
  irr.copy(pol2);
  while (rem == 1)
  {
    div = irr / tar;
    rem = irr % tar;
    irr.copy(tar);
    tar.copy(rem);
    if (i % 2)
      res = res + div;
    else
      res = res + 1;
  }
  return res;
}
*/
/*long long Polynom::gcdforinvers(long long a, long long b, long long* x, long long* y)
{
    if (a == 0)
    {
        *x = 0, * y = 1;
        return b;
    }

    long long x1, y1;
    long long gcd = gcdExtended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}*/

/*Polynom Polynom::inversPoly(long long number, Polynom const& pol1)
{
    int x, y;
    int g = gcdforinvers(number, pol1, int & x, int & y);

    if (g != 1)
        return -1;
    else
        return (x % pol1 + pol1) % pol1;
}*/

