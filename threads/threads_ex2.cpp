/*
 * in this program:
 *
 * - we define a worker () function that simulates some work being done by
 * printing a message
 * - we create a vector of std::thread objects in main () and spawn each of
 * them to execute the worker () function with a unique ID
 * - the main thread will perform its task by printing out the "main thread is
 * executing" statement
 * - we then join each worker thread with the main thread using the join ()
 * function (remember; order is not guaranteed!!!)
 */

#include <iostream>
#include <thread>
#include <vector>
#include <string>

void worker (int id)
{
    std::cout << "worker thread: " << id << " is executing\n";
}

/*
 * the data passed to a thread is copied *by value* when the thread is created;
 * this means each thread works with a copy of the data, ensuring that the
 * original data in the main thread remains unaffected and free from
 * concurrency-related issues
 * 
 * for larger data structures, consider passing pointers or references
 */

void process_str (const std::string &str)
{
    std::cout << "processing this string: " << str << std::endl;
}

void process_str_vector (const std::vector<std::string> &vec)
{
    for (const auto &str : vec)
        std::cout << "processing vector string: " << str << std::endl;
}

int main ()
{
    std::vector<std::thread> threads;

    // let's create five worker threads
    for (int i = 0; i < 5; ++i)
        threads.push_back (std::thread  (worker, i));
    
    std::cout << "main thread is executing\n";

    // let's join all of the threads back with the main thread
    for (auto &th : threads)
        th.join ();

    // let's create some strings
    std::string my_string = "hello, world!";
    std::vector<std::string> my_string_vector = {"hello",
                                                 "from",
                                                 "the",
                                                 "other",
                                                 "thread"};

    // create the threads for the strings
    std::thread thread1 (process_str, my_string);
    std::thread thread2 (process_str_vector, my_string_vector);

    // join the two threads
    thread1.join ();
    thread2.join ();

    return 0;
}
