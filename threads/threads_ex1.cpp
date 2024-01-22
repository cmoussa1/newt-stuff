/*
 * to compile a program like this, we need to link the pthread library:
 *
 * g++ -o threads_ex1 threads_ex1.cpp -pthread
 */

#include <iostream>
#include <thread>
#include <vector>

void print_even_nums (int limit)
{
    for (int i = 0; i <= limit; i += 2) {
        std::cout << "even: " << i << std::endl;
    }
}

void print_odd_nums (int limit)
{
    for (int i = 1; i <= limit; i += 2) {
        std::cout << "odd: " << i << std::endl;
    }
}

int main ()
{
    int limit = 10;

    // create threads for printing out different classes of numbers
    std::thread thread1 (print_even_nums, limit);
    std::thread thread2 (print_odd_nums, limit);

    // need to join multiple threads to the main thread
    thread1.join ();
    thread2.join ();

    return 0;
}
