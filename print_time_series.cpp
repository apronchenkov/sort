#include "InsertionSort.h"
#include "QuickSort.h"
#include "RadixSort.h"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>


template <class Integer, class Generator>
std::vector<Integer> GenerateVector(Generator& generator, size_t size)
{
    std::uniform_int_distribution<Integer> uniform_distribution;
    std::vector<Integer> result;
    result.reserve(size);
    for (size_t index = 0; index < size; ++index) {
        result.push_back(uniform_distribution(generator));
    }
    return result;
}


typedef std::chrono::high_resolution_clock::duration ChronoDuration;

template <class Integer, class Generator, class SortAlgorithm>
ChronoDuration MesureTime(Generator& generator, size_t size, SortAlgorithm sort_algorithm)
{
    std::vector<Integer> input = GenerateVector<Integer>(generator, size);

    const auto start = std::chrono::high_resolution_clock::now();
    sort_algorithm(&input);
    const auto stop = std::chrono::high_resolution_clock::now();

    return stop - start;
}


template <class Integer, class Generator, class SortAlgorithm>
ChronoDuration MedianTime(Generator& generator, size_t size, SortAlgorithm sort_algorithm)
{
    std::vector<ChronoDuration> durations;
    for (size_t index = 0; index < 501; ++index) {
        durations.push_back(
            MesureTime<Integer>(generator, size, sort_algorithm));
    }
    std::nth_element(durations.begin(), durations.begin() + durations.size() / 2, durations.end());
    return durations[durations.size() / 2];
}


size_t ToNanos(const ChronoDuration& duration)
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}


template <class Integer, class Generator>
void PrintTimes(Generator& generator, size_t size, const std::vector<std::string>& sort_algorithm_names)
{
    std::cout << size;
    for (const auto& algorithm_name : sort_algorithm_names) {
        if (algorithm_name == "QuickSort") {
            std::cout << '\t' << ToNanos( MesureTime<Integer>(generator, size,
                [](std::vector<uint32_t>* input) {
                    QuickSort(input->begin(), input->end(), std::less<uint32_t>());
                }));

        } else if (algorithm_name == "RadixSort") {
            std::cout << '\t' << ToNanos( MesureTime<Integer>(generator, size,
                [](std::vector<uint32_t>* input) {
                    RadixSort(input);
                }));

        } else if (algorithm_name == "InsertionSort") {
            std::cout << '\t' << ToNanos( MesureTime<Integer>(generator, size,
                [](std::vector<uint32_t>* input) {
                    InsertionSort(input->begin(), input->end(), std::less<uint32_t>());
                }));

        } else if (algorithm_name == "StdSort") {
            std::cout << '\t' << ToNanos( MesureTime<Integer>(generator, size,
                [](std::vector<uint32_t>* input) {
                    std::sort(input->begin(), input->end(), std::less<uint32_t>());
                }));

        } else {
            throw std::runtime_error("Unknown algorithm: " + algorithm_name);
        }
    }
    std::cout << '\n';
}



template <class Integer, class Generator>
void PrintTimeSeries(Generator& generator, const std::vector<std::string>& sort_algorithm_names)
{
    for (size_t size = 2; size < 20; size += 1) {
        PrintTimes<Integer>(generator, size, sort_algorithm_names);
    }
    for (size_t size = 20; size < 200; size += 5) {
        PrintTimes<Integer>(generator, size, sort_algorithm_names);
    }
    for (size_t size = 200; size < 2000; size += 50) {
        PrintTimes<Integer>(generator, size, sort_algorithm_names);
    }
    for (size_t size = 2000; size < 20000; size += 500) {
        PrintTimes<Integer>(generator, size, sort_algorithm_names);
    }
}


void Usage()
{
    std::cerr << "usage: QuickSort | RadixSort | InsertionSort | StdSort\n\n";
    std::exit(-1);
}


int main(int argc, char** argv)
{
    if (argc == 1) {
        Usage();
    }

    try {
        std::mt19937 gen(4242);
        std::cout << "Size";
        for (int index = 1; index < argc; ++index) {
            std::cout << '\t' << argv[index];
        }
        std::cout << '\n';
        PrintTimeSeries<uint32_t>(gen, {argv + 1, argv + argc});
        return 0;

    } catch (const std::exception& ex) {
        std::cerr << ex.what() << '\n';
        return -1;
    }
}
