// Copyright 2016 Virgilio Sanz <Virgilio.Sanz@gmail.com>

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

int main(int argc, const char** argv)
{
    unsigned num_cpus = std::thread::hardware_concurrency();
    std::cout << "Launching " << num_cpus << " threads\n";

    // std::cout is not guaranteed to be thread safe, so we protect it with a
    // mutex.
    std::mutex iomutex;
    std::vector<std::thread> threads(num_cpus);

    for (unsigned i = 0; i < num_cpus; ++i)
    {
        threads[i] = std::thread([&iomutex, i]
        {
            while (1)
            {
                {
                    // Use a lexical scope and lock_guard to safely lock the mutex only for
                    // the duration of std::cout usage.
                    std::lock_guard<std::mutex> iolock(iomutex);
                    std::cout << "Thread #" << i << " running" << std::endl;
                }

                // Simulate important work done by the tread by sleeping for a bit...
                std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            }

        });
    }

    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));

    return 0;
}
