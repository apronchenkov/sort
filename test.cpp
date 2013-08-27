#include "InsertionSort.h"
#include "QuickSort.h"
#include "RadixSort.h"

#include <algorithm>
#include <random>
#include <stdexcept>
#include <vector>


template <class Integer, class SortAlgorithm>
void TestSortAlgorithm(const std::vector<Integer>& input, SortAlgorithm sort_algorithm)
{
    auto value = input;
    sort_algorithm(&value);

    auto expected = input;
    std::sort(expected.begin(), expected.end());

    if (value != expected) {
        throw std::runtime_error("test_sort: fail");
    }
}

template <class Integer, class Generator>
std::vector<Integer> GenerateVector(Generator& generator, size_t size)
{
    std::uniform_int_distribution<Integer> uniformDistribution;
    std::vector<Integer> result;
    result.reserve(size);
    for (size_t index = 0; index < size; ++index) {
        result.push_back(uniformDistribution(generator));
    }
    return result;
}

template <typename Integer, class SortAlgorithm>
void TestSortAlgorithmSmall(SortAlgorithm sort_algorithm)
{
    const int N = 20;
    for (int bitmap = 0; bitmap < (1 << N); ++bitmap) {
        std::vector<Integer> vector(N, 1);
        for (int i = 0; i < N; ++i) {
            if (bitmap & (1 << i)) {
                vector[i] = 1;
            }
        }
        TestSortAlgorithm(vector, sort_algorithm);
    }
}

template <typename Integer, class Generator, class SortAlgorithm>
void TestSortAlgorithm(Generator& generator, SortAlgorithm sort_algorithm)
{
    const size_t SIZE = 1000;
    for (int counter = 0; counter < 100; ++counter) {
        TestSortAlgorithm(GenerateVector<Integer>(generator, SIZE), sort_algorithm);
    }
}


template <class Integer>
void TestMedian3(Integer a, Integer b, Integer c, Integer expected)
{
    using namespace internal;
    if (expected != *Median3(&a, &b, &c, std::less<Integer>())) {
        throw std::runtime_error("test_median: fail");
    }
}


template <class Integer>
void TestMedian3()
{
    TestMedian3<Integer>(0, 0, 0,  0);
    TestMedian3<Integer>(0, 0, 1,  0);
    TestMedian3<Integer>(0, 1, 0,  0);
    TestMedian3<Integer>(1, 0, 0,  0);

    TestMedian3<Integer>(1, 1, 0,  1);
    TestMedian3<Integer>(1, 0, 1,  1);
    TestMedian3<Integer>(1, 1, 0,  1);
    TestMedian3<Integer>(1, 1, 1,  1);

    TestMedian3<Integer>(0, 1, 2,  1);
    TestMedian3<Integer>(0, 2, 1,  1);
    TestMedian3<Integer>(1, 0, 2,  1);
    TestMedian3<Integer>(1, 2, 0,  1);
    TestMedian3<Integer>(2, 0, 1,  1);
    TestMedian3<Integer>(2, 1, 0,  1);
}


struct InsertionSortWrapper {
    template <class Container>
    void operator() (Container* const container) const
    {
        InsertionSort(container->begin(), container->end(), std::less<typename Container::value_type>());
    }
};

struct QuickSortWrapper {
    template <class Container>
    void operator() (Container* const container) const
    {
        QuickSort(container->begin(), container->end(), std::less<typename Container::value_type>());
    }
};

struct RadixSortWrapper {
    template <class Container>
    void operator() (Container* const container) const
    {
        RadixSort(container);
    }
};

int main()
{
    std::mt19937 gen(4242);

    TestMedian3<int8_t>();
    TestMedian3<int16_t>();
    TestMedian3<int32_t>();
    TestMedian3<int64_t>();
    TestMedian3<uint8_t>();
    TestMedian3<uint16_t>();
    TestMedian3<uint32_t>();
    TestMedian3<uint64_t>();

    TestSortAlgorithmSmall<int8_t>(QuickSortWrapper());
    TestSortAlgorithmSmall<int16_t>(QuickSortWrapper());
    TestSortAlgorithmSmall<int32_t>(QuickSortWrapper());
    TestSortAlgorithmSmall<int64_t>(QuickSortWrapper());
    TestSortAlgorithmSmall<uint8_t>(QuickSortWrapper());
    TestSortAlgorithmSmall<uint16_t>(QuickSortWrapper());
    TestSortAlgorithmSmall<uint32_t>(QuickSortWrapper());
    TestSortAlgorithmSmall<uint64_t>(QuickSortWrapper());
    TestSortAlgorithm<int8_t>(gen, QuickSortWrapper());
    TestSortAlgorithm<int16_t>(gen, QuickSortWrapper());
    TestSortAlgorithm<int32_t>(gen, QuickSortWrapper());
    TestSortAlgorithm<int64_t>(gen, QuickSortWrapper());
    TestSortAlgorithm<uint8_t>(gen, QuickSortWrapper());
    TestSortAlgorithm<uint16_t>(gen, QuickSortWrapper());
    TestSortAlgorithm<uint32_t>(gen, QuickSortWrapper());
    TestSortAlgorithm<uint64_t>(gen, QuickSortWrapper());

    TestSortAlgorithmSmall<int8_t>(InsertionSortWrapper());
    TestSortAlgorithmSmall<int16_t>(InsertionSortWrapper());
    TestSortAlgorithmSmall<int32_t>(InsertionSortWrapper());
    TestSortAlgorithmSmall<int64_t>(InsertionSortWrapper());
    TestSortAlgorithmSmall<uint8_t>(InsertionSortWrapper());
    TestSortAlgorithmSmall<uint16_t>(InsertionSortWrapper());
    TestSortAlgorithmSmall<uint32_t>(InsertionSortWrapper());
    TestSortAlgorithmSmall<uint64_t>(InsertionSortWrapper());
    TestSortAlgorithm<int8_t>(gen, InsertionSortWrapper());
    TestSortAlgorithm<int16_t>(gen, InsertionSortWrapper());
    TestSortAlgorithm<int32_t>(gen, InsertionSortWrapper());
    TestSortAlgorithm<int64_t>(gen, InsertionSortWrapper());
    TestSortAlgorithm<uint8_t>(gen, InsertionSortWrapper());
    TestSortAlgorithm<uint16_t>(gen, InsertionSortWrapper());
    TestSortAlgorithm<uint32_t>(gen, InsertionSortWrapper());
    TestSortAlgorithm<uint64_t>(gen, InsertionSortWrapper());

    // TestSortAlgorithmSmall<int8_t>(RadixSortWrapper());
    // TestSortAlgorithmSmall<int16_t>(RadixSortWrapper());
    // TestSortAlgorithmSmall<int32_t>(RadixSortWrapper());
    // TestSortAlgorithmSmall<int64_t>(RadixSortWrapper());
    TestSortAlgorithmSmall<uint8_t>(RadixSortWrapper());
    TestSortAlgorithmSmall<uint16_t>(RadixSortWrapper());
    TestSortAlgorithmSmall<uint32_t>(RadixSortWrapper());
    TestSortAlgorithmSmall<uint64_t>(RadixSortWrapper());
    // TestSortAlgorithm<int8_t>(gen, RadixSortWrapper());
    // TestSortAlgorithm<int16_t>(gen, RadixSortWrapper());
    // TestSortAlgorithm<int32_t>(gen, RadixSortWrapper());
    // TestSortAlgorithm<int64_t>(gen, RadixSortWrapper());
    TestSortAlgorithm<uint8_t>(gen, RadixSortWrapper());
    TestSortAlgorithm<uint16_t>(gen, RadixSortWrapper());
    TestSortAlgorithm<uint32_t>(gen, RadixSortWrapper());
    TestSortAlgorithm<uint64_t>(gen, RadixSortWrapper());

    return 0;
}
