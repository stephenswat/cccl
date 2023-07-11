//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// UNSUPPORTED: c++98, c++03, c++11

// <chrono>
// class year_month_weekday_last;

// constexpr operator sys_days() const noexcept;
//  Returns: If ok() == true, returns a sys_days that represents the last weekday()
//             of year()/month(). Otherwise the returned value is unspecified.

#include <cuda/std/chrono>
#include <cuda/std/type_traits>
#include <cuda/std/cassert>

#include "test_macros.h"


int main(int, char**)
{
    using year                    = cuda::std::chrono::year;
    using month                   = cuda::std::chrono::month;
    using year_month_weekday_last = cuda::std::chrono::year_month_weekday_last;
    using sys_days                = cuda::std::chrono::sys_days;
    using days                    = cuda::std::chrono::days;
    using weekday                 = cuda::std::chrono::weekday;
    using weekday_last            = cuda::std::chrono::weekday_last;

    ASSERT_NOEXCEPT(                    static_cast<sys_days>(cuda::std::declval<const year_month_weekday_last>()));
    ASSERT_SAME_TYPE(sys_days, decltype(static_cast<sys_days>(cuda::std::declval<const year_month_weekday_last>())));

    auto constexpr January = cuda::std::chrono::January;
    auto constexpr Tuesday = cuda::std::chrono::Tuesday;

    { // Last Tuesday in Jan 1970 was the 27th
    constexpr year_month_weekday_last ymwdl{year{1970}, January, weekday_last{Tuesday}};
    constexpr sys_days sd{ymwdl};

    static_assert(sd.time_since_epoch() == days{26}, "");
    }

    { // Last Tuesday in Jan 2000 was the 25th
    constexpr year_month_weekday_last ymwdl{year{2000}, January, weekday_last{Tuesday}};
    constexpr sys_days sd{ymwdl};

    static_assert(sd.time_since_epoch() == days{10957+24}, "");
    }

    { // Last Tuesday in Jan 1940 was the 30th
    constexpr year_month_weekday_last ymwdl{year{1940}, January, weekday_last{Tuesday}};
    constexpr sys_days sd{ymwdl};

    static_assert(sd.time_since_epoch() == days{-10958+29}, "");
    }

    { // Last Tuesday in Nov 1939 was the 28th
    year_month_weekday_last ymdl{year{1939}, cuda::std::chrono::November, weekday_last{Tuesday}};
    sys_days sd{ymdl};

    assert(sd.time_since_epoch() == days{-(10957+35)});
    }

  return 0;
}
