# Primes

For this approach I was mainly limited by not knowing what data storage I should use. i settled on vectors and a priority queue.

countPrimes() :

I had each thread run countPrimes() that iterated over each odd number and call isPrime() and push every prime numebr into a local list of primes.
I would then shorten the list to 10 values then push it to a global minHeap called primes, popping from the minheap after the minheap surpassed a size of 10
a mutex.lock() mutex.unlock() function surrounded only the manipulation of the global shared heap.

isPrime() :

I isPrime() so that it would check if it is divisible by two, then iterate over only the odds, since all even numbers have a lcd of 2.

main() :

after i joined the threads i popped the global minheap directly into the file


Experimenting:

When i first started coding this assignment i got stuck for a long time since i was using 1 billion instead of 100 million by accident. 
the majority of my testing was on just making sure the program was efficient. splitting both the prime iterator and the outer for loop over just the odds helped the best.
I could run the program in 9 seconds very consistently. I feel as though this is very efficient for how much i know of cpp

To compile this on windows from command prompt using MinGW
```
g++ -std=c++11 -o Primes Primes.cpp
```
Followed by
```
Primes.exe
```
