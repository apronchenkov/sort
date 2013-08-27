#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <vector>

namespace internal {

template <int DIGIT_SIZE, int DIGIT_OFFSET, typename Integer>
void RadixSortImpl(const std::vector<Integer>& source, std::vector<Integer>* const destination)
{
    const auto digit = [](Integer integer) {
        return (integer >> DIGIT_OFFSET) & ((1 << DIGIT_SIZE) - 1);
    };

    std::array<size_t, 1 + (1<<DIGIT_SIZE)> counter = {{0, }};
    for (const auto& integer : source) {
        ++counter[ 1 + digit(integer) ];
    }

    std::partial_sum(counter.begin(), counter.end(), counter.begin());

    destination->resize(source.size());
    for (const auto& integer : source) {
        (*destination)[ counter[digit(integer)]++ ] = integer;
    }
}

} // namespace internal

inline void RadixSort(std::vector<uint8_t>* const input)
{
    std::vector<uint8_t> buffer;
    internal::RadixSortImpl<8, 0>(*input, &buffer);
    input->swap(buffer);
}


inline void RadixSort(std::vector<uint16_t>* const input)
{
    std::vector<uint16_t> buffer;
    internal::RadixSortImpl<8, 0>(*input, &buffer);
    internal::RadixSortImpl<8, 8>(buffer, input);
}


inline void RadixSort(std::vector<uint32_t>* const input)
{
    std::vector<uint32_t> buffer;
    internal::RadixSortImpl<8, 0>(*input, &buffer);
    internal::RadixSortImpl<8, 8>(buffer, input);
    internal::RadixSortImpl<8, 16>(*input, &buffer);
    internal::RadixSortImpl<8, 24>(buffer, input);
}

inline void RadixSort(std::vector<uint64_t>* const input)
{
    std::vector<uint64_t> buffer;
    internal::RadixSortImpl<8, 0>(*input, &buffer);
    internal::RadixSortImpl<8, 8>(buffer, input);
    internal::RadixSortImpl<8, 16>(*input, &buffer);
    internal::RadixSortImpl<8, 24>(buffer, input);
    internal::RadixSortImpl<8, 32>(*input, &buffer);
    internal::RadixSortImpl<8, 40>(buffer, input);
    internal::RadixSortImpl<8, 48>(*input, &buffer);
    internal::RadixSortImpl<8, 56>(buffer, input);
}
