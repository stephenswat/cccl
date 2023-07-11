//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES.
//
//===----------------------------------------------------------------------===//

// <cuda/std/iterator>

// move_iterator

// template <RandomAccessIterator Iter1, RandomAccessIterator Iter2>
//   requires HasMinus<Iter1, Iter2>
//   auto
//   operator-(const move_iterator<Iter1>& x, const move_iterator<Iter2>& y)
//   -> decltype(x.base() - y.base());
//
//  constexpr in C++17

#include <cuda/std/iterator>
#include <cuda/std/cassert>

#include "test_macros.h"
#include "test_iterators.h"

template <class It>
__host__ __device__
void
test(It l, It r, typename cuda::std::iterator_traits<It>::difference_type x)
{
    const cuda::std::move_iterator<It> r1(l);
    const cuda::std::move_iterator<It> r2(r);
    assert(r1 - r2 == x);
}

int main(int, char**)
{
    char s[] = "1234567890";
    test(random_access_iterator<char*>(s+5), random_access_iterator<char*>(s), 5);
    test(s+5, s, 5);

#if TEST_STD_VER > 14
    {
    constexpr const char *p = "123456789";
    typedef cuda::std::move_iterator<const char *> MI;
    constexpr MI it1 = cuda::std::make_move_iterator(p);
    constexpr MI it2 = cuda::std::make_move_iterator(p+1);
    static_assert( it1 - it2 == -1, "");
    static_assert( it2 - it1 ==  1, "");
    }
#endif

  return 0;
}
