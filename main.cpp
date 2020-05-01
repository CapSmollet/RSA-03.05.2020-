#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <stdlib.h>
#include <ctime>

using namespace std;

unsigned long long key, p, n, q, f, e, d;

bool prime_check(unsigned long long s){
	for (unsigned long long i = 2; i <= sqrt(s); i++)
		if (s % i == 0)
			return false;
	return true;
}

int gcdex(unsigned long long a, unsigned long long b, unsigned long long &x, unsigned long long &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    unsigned long long x1, y1;
    unsigned long long d1 = gcdex(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d1;
}

int gcd(unsigned long long a, unsigned long long b) {
   if (b == 0)
      return a;
   return gcd(b, a % b);
}

unsigned long long prime_gen(){
    unsigned long long k = rand() % 100000 + 10000;
    while (prime_check(k) == false)
        k = rand() % 100000 + 10000;
    return k;
}

void keys_creat()
{
    srand((unsigned)time(0));
    p = prime_gen();
    q = prime_gen();
    while (p == q)
    {
        q = prime_gen();
    }
    n = p * q;
    f = (p - 1) * (q - 1);
    e = rand();
    while (e > f || gcd(e, f) != 1)
    {
        e = rand();
    }
    unsigned long long x, y, e1 = e, m = f;
    unsigned long long g = gcdex(e1, m, x, y);
    d = (x % m + m) % m;
}

unsigned long long powerFast(unsigned long long num, unsigned long long deg)
{
    unsigned long long result = 1;
    while (deg)
    {
        if (deg % 2 == 0)
        {
            deg /= 2;
            num = ((num % n) * (num % n));
            num %= n;

        }
        else
        {
            deg--;
            result *= num;
            result %= n;
        }
    }

    return result % n;
}

unsigned long long encryption(unsigned long long e1, unsigned long long n1, unsigned long long m)
{
    return (powerFast(m, e1) % n1);
}

unsigned long long decryption(unsigned long long d1, unsigned long long n1, unsigned long long c)
{
    return(powerFast(c, d1) % n1);
}

int main()
{
    unsigned long long number, out;
    keys_creat();
    //cout << n << ' ' << e << ' ' << d << '\n';
    cin >> number;
    out = decryption(d, n, encryption(e, n, number));
    while (out != number)
    {
        keys_creat();
        out = decryption(d, n, encryption(e, n, number));
    }
    cout << out << " Successful";
    return 0;
}
