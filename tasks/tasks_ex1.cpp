#include <iostream>
#include <future>
#include <thread>

int compute_sum (int a, int b)
{
    // simulate some work
    std::this_thread::sleep_for (std::chrono::seconds (2));
    return a + b;
}

int main ()
{
    // start an asynchronous task
    std::future<int> result = std::async (compute_sum, 5, 3);

    // do some other work in the main thread
    std::cout << "main thread is continuing to execute..." << std::endl;

    // retrieve and print the result of the asynchronous task
    std::cout << "the sum is: " << result.get () << std:: endl;

    return 0;
}
