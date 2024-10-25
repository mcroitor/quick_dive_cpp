/*
 * up a thread, wait for it to finish a random amount of time, and then return this value.
 */

#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1, 10);

int do_work()
{
    int value = dist(gen);
    std::this_thread::sleep_for(std::chrono::seconds(value));
    return value;
}

int main()
{
    std::future<int> result = std::async(do_work);
    std::cout << "Waiting for the result...\n";
    std::cout << "Result: " << result.get() << '\n';
    return 0;
}