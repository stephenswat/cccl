//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// type_traits

// member_function_pointer

#include <cuda/std/type_traits>

#include "test_macros.h"

template <class T>
__host__ __device__
void test_member_function_pointer_imp()
{
    static_assert(!cuda::std::is_reference<T>::value, "");
    static_assert(!cuda::std::is_arithmetic<T>::value, "");
    static_assert(!cuda::std::is_fundamental<T>::value, "");
    static_assert( cuda::std::is_object<T>::value, "");
    static_assert( cuda::std::is_scalar<T>::value, "");
    static_assert( cuda::std::is_compound<T>::value, "");
    static_assert( cuda::std::is_member_pointer<T>::value, "");
}

template <class T>
__host__ __device__
void test_member_function_pointer()
{
    test_member_function_pointer_imp<T>();
    test_member_function_pointer_imp<const T>();
    test_member_function_pointer_imp<volatile T>();
    test_member_function_pointer_imp<const volatile T>();
}

class Class
{
};

int main(int, char**)
{
    test_member_function_pointer<void (Class::*)()>();
    test_member_function_pointer<void (Class::*)(int)>();
    test_member_function_pointer<void (Class::*)(int, char)>();

  return 0;
}
