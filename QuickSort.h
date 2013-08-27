#pragma once

#include "InsertionSort.h"
#include <algorithm>

namespace internal {

template <class Iterator, class Compare>
Iterator Median3(Iterator a, Iterator b, Iterator c, Compare compare)
{
    if (compare(*a, *b)) {
        if (compare(*b, *c)) {
            return b;
        } else if (compare(*a, *c))  {
            return c;
        } else {
            return a;
        }

    } else {
        if (compare(*a, *c)) {
            return a;
        } else if (compare(*b, *c))  {
            return c;
        } else {
            return b;
        }
    }
}

template <class Iterator, class Compare>
Iterator SelectPivot(Iterator begin, Iterator end, Compare compare)
{
    const auto size = std::distance(begin, end);
    return Median3(
        Median3(begin,
                begin + 1*size/8,
                begin + 2*size/8,
                compare),
        Median3(begin + 3*size/8,
                begin + 4*size/8,
                begin + 5*size/8,
                compare),
        Median3(begin + 6*size/8,
                begin + 7*size/8,
                std::prev(end),
                compare),
        compare);
}

template <class Iterator>
void ToggleSmallRange(Iterator begin, Iterator middle, Iterator end)
{
    if (std::distance(begin, middle) < std::distance(middle, end)) {
        std::swap_ranges(begin, middle, std::reverse_iterator<Iterator>(end));
    } else {
        std::swap_ranges(middle, end, begin);
    }
}

} // namespace internal

template <class Iterator, class Compare>
void QuickSort(Iterator begin, Iterator end, Compare compare)
{
    if (std::distance(begin, end) <= 64) {
        InsertionSort(begin, end, compare);
        return;
    }

    std::iter_swap(begin, internal::SelectPivot(begin, end, compare));
    const auto& pivot = *begin;

    Iterator frontIt = std::next(begin);
    Iterator backIt = std::prev(end);

    Iterator frontBufferIt = frontIt;
    Iterator backBufferIt = backIt;

    for (;;) {
        while (frontIt <= backIt && !compare(pivot, *frontIt)) {
            if (!compare(*frontIt, pivot)) {
                std::iter_swap(frontIt, frontBufferIt);
                ++frontBufferIt;
            }
            ++frontIt;
        }
        while (frontIt <= backIt && !compare(*backIt, pivot)) {
            if (!compare(pivot, *backIt)) {
                std::iter_swap(backIt, backBufferIt);
                --backBufferIt;
            }
            --backIt;
        }
        if (backIt < frontIt) {
            break;
        }
        std::iter_swap(frontIt, backIt);
        ++frontIt;
        --backIt;
    }

    if (frontBufferIt != frontIt) {
        internal::ToggleSmallRange(begin, frontBufferIt, frontIt);
        QuickSort(begin, begin + std::distance(frontBufferIt, frontIt), compare);
    }

    if (backIt != backBufferIt) {
        internal::ToggleSmallRange(std::next(backIt), std::next(backBufferIt), end);
        QuickSort(end - std::distance(backIt, backBufferIt), end, compare);
    }
}
