#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>
#include <queue>
#include <set>
#include <mutex>
using namespace std;
using namespace std::chrono;
typedef long long ll;

atomic<ll> sum(0);
atomic<ll> primecount(0);
mutex mtx;
priority_queue<ll, vector<ll>, greater<ll>> primes;

bool isPrime(int n)
{
    if (n == 1)
		return false;
	else if (n == 2)
		return true;

	ll jMin = sqrt(n) + 1;
	ll j;
    for (j = 3; j <= jMin; j+=2)
    {
		if (n % j == 0)
			break;         
	}

	if (j >= jMin)
		return true;
	else
		return false;
}

void countPrimes(ll start, ll end)
{
    ll pcount = 0, psum = 0;
    set<ll> pprimes;
    if (start == 1)
    {
        pcount++;
		psum += 2;
        pprimes.insert(2);
		start+=2;
	}
    else if (start % 2 == 0)
    {
        start++;
    }

    for (int i = start; i < end; i+=2)
    {
        if (isPrime(i))
        {
            pcount++;
            psum += i;
            pprimes.insert(i);

            if (pprimes.size() > 10)
            {
				pprimes.erase(pprimes.begin());
			}
        }
    }

    primecount += pcount;
    sum += psum;
    mtx.lock();
    while (!pprimes.empty())
    {
        primes.push(*pprimes.begin());
		pprimes.erase(pprimes.begin());
	}
    while (primes.size() > 10)
    {
        primes.pop();
    }
	mtx.unlock();
}

int main()
{
    const int numThreads = 8;
    ll start = 1, end = 1e8, step = (end - start) / numThreads;
    vector<thread> threads;

    ofstream of("primes.txt");

    auto startTime = high_resolution_clock::now();
    for (int i = 0; i < numThreads; i++)
    {
        if (i == numThreads - 1)
            threads.emplace_back(countPrimes, start, end);
        else
        {
            threads.emplace_back(countPrimes, start, start + step - 1);
            start = start + step;
        }
	}
	 
    for (auto &thread : threads)
    {
		thread.join();
	}
    auto stopTime = high_resolution_clock::now();

    // cout << "<" << duration_cast<milliseconds>(stopTime - startTime).count() << "ms> <" << primecount << "> <" << sum << ">" << endl;
    of << "<" << duration_cast<milliseconds>(stopTime - startTime).count() << "ms> <" << primecount << "> <" << sum << ">" << endl;

    while (primes.size() > 10)
    {
        primes.pop();
    }

    // cout << "<";
    of << "<";
    for (int i = 0; i < 10; i++)
    {
        ll tmp = primes.top();
        primes.pop();
        // cout << tmp;
        of << tmp;
        if (i == 9)
        {
            // cout << ">" << endl;
            of << ">" << endl;
        }
        else
        {
            // cout << ", ";
            of << ", ";
        }
    }

    of.close();
    return 0;
}
