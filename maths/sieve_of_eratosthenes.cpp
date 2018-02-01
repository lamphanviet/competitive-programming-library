#include <bits/stdc++.h>

using namespace std;

struct Eratosthenes {
	int n;
	vector<bool> isPrime;
	vector<int> primes;

	// constructor and run from here
	// n: apply for all numbers in [0:n]
	// collect: whether you want to collect all primes into a vector
	Eratosthenes(int n, bool collect) {
		isPrime.clear();
		primes.clear();
		this->n = n + 1;
		sieve();
		if (collect) collectPrimes();
	}

	void sieve() {
		isPrime = vector<bool>(n, true);

		isPrime[0] = isPrime[1] = false;
		for (int i = 4; i < n; i += 2)
			isPrime[i] = false;
		for (int i = 3; i * i < n; i += 2) if (isPrime[i])
			for (int j = i * i; j < n; j += i + i)
				isPrime[j] = false;
	}

	void collectPrimes() {
		primes.clear();
		primes.push_back(2);
		for (int i = 3; i < n; i += 2) if (isPrime[i])
			primes.push_back(i);
	}
};

Eratosthenes era(499, true);

int main() {
	for (int i = 0; i < era.primes.size(); i++)
		printf("%d ", era.primes[i]);
	return 0;
}

// Phan-Viet Lam - lamphanviet@gmail.com - http://blog.lamphanviet.com