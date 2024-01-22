#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>

void worker (std::promise<void> promise)
{
    try {
        // just simulate that some work throws an exception
        throw std::runtime_error ("an error occured here!");
    } catch (...) {
        // store the exception in the promise
        promise.set_exception (std::current_exception ());
    }
}


int main ()
{
    /*
     * a promise is an object that stores a value or exception that's retrieved
     * asynchronously at a later point in time through a std::future object
     * 
     * std::promise is like a channel through which a value or an exception can
     * be sent, typically used in a producer thread
     * 
     * std::future is the counterpart to the promise object and is used to
     * retrieve the value or exception set in the promise. It is kind of like a
     * handle to a future result that a promise will provide
     * 
     * the future.get () call will block until the promise sets a value or an
     * exception; if a vlaue is set, get () returns the value. If an exception
     * is set, it rethrows the exception
     */

    //
    std::promise<void> promise;
    std::future<void> future = promise.get_future ();

    // start a thread and pass the promise to it
    std::thread t (worker, std::move (promise));

    try {
        // wait for the exception from the thread
        //
        // this will either return successfully if the thread completes without
        // throwing an exception or throw an exception if one was set in the
        // promise within the thread
        future.get ();
    } catch (const std::exception &e) {
        // handle the exception from the thread here in the main thread
        std::cout << "an exception was caught in the main thread: " << e.what () << std::endl;
    }

    // ensure that thread execution is complete
    t.join ();

    return 0;
}
