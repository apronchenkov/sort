#pragma once

#include <iterator>

template <class Iterator, class Compare>
void InsertionSort(Iterator begin, Iterator end, Compare compare)
{
    for (auto it = std::next(begin); it != end; ++it) {
        for (auto jt = it; jt != begin && compare(*jt, *std::prev(jt)); --jt) {
            std::iter_swap(jt, std::prev(jt));
        }
    }
}
