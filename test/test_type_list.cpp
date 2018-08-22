// The MIT License (MIT)
//
// Copyright (c) 2018 Mateusz Pusz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "units/dimension.h"
#include <gtest/gtest.h>
#include <utility>

using namespace mp;
using namespace units;

// type_list_push_front

static_assert(std::is_same_v<type_list_push_front_t<type_list<>, int>, type_list<int>>);
static_assert(std::is_same_v<type_list_push_front_t<type_list<>, int, long, double>, type_list<int, long, double>>);
static_assert(std::is_same_v<type_list_push_front_t<type_list<double>, int, long>, type_list<int, long, double>>);

// type_list_split_half

static_assert(std::is_same_v<type_list_split_half<type_list<int>>::first_list, type_list<int>>);
static_assert(std::is_same_v<type_list_split_half<type_list<int>>::second_list, type_list<>>);

static_assert(std::is_same_v<type_list_split_half<type_list<int, long>>::first_list, type_list<int>>);
static_assert(std::is_same_v<type_list_split_half<type_list<int, long>>::second_list, type_list<long>>);

static_assert(std::is_same_v<type_list_split_half<type_list<int, long, double>>::first_list, type_list<int, long>>);
static_assert(std::is_same_v<type_list_split_half<type_list<int, long, double>>::second_list, type_list<double>>);

static_assert(
    std::is_same_v<type_list_split_half<type_list<int, long, double, float>>::first_list, type_list<int, long>>);
static_assert(
    std::is_same_v<type_list_split_half<type_list<int, long, double, float>>::second_list, type_list<double, float>>);

// type_list_merge_sorted

static_assert(std::is_same_v<type_list_merge_sorted_t<type_list<dim_id<0>>, type_list<dim_id<1>>, dim_id_less>,
                             type_list<dim_id<0>, dim_id<1>>>);
static_assert(std::is_same_v<type_list_merge_sorted_t<type_list<dim_id<1>>, type_list<dim_id<0>>, dim_id_less>,
                             type_list<dim_id<0>, dim_id<1>>>);

static_assert(std::is_same_v<type_list_merge_sorted_t<type_list<dim_id<27>, dim_id<38>>,
                                                      type_list<dim_id<3>, dim_id<43>>, dim_id_less>,
                             type_list<dim_id<3>, dim_id<27>, dim_id<38>, dim_id<43>>>);
static_assert(
    std::is_same_v<type_list_merge_sorted_t<type_list<dim_id<9>, dim_id<82>>, type_list<dim_id<10>>, dim_id_less>,
                   type_list<dim_id<9>, dim_id<10>, dim_id<82>>>);

// type_list_sort

static_assert(std::is_same_v<type_list_sort_t<type_list<dim_id<0>>, dim_id_less>, type_list<dim_id<0>>>);
static_assert(
    std::is_same_v<type_list_sort_t<type_list<dim_id<0>, dim_id<1>>, dim_id_less>, type_list<dim_id<0>, dim_id<1>>>);
static_assert(
    std::is_same_v<type_list_sort_t<type_list<dim_id<1>, dim_id<0>>, dim_id_less>, type_list<dim_id<0>, dim_id<1>>>);
static_assert(
    std::is_same_v<
        type_list_sort_t<type_list<dim_id<38>, dim_id<27>, dim_id<43>, dim_id<3>, dim_id<9>, dim_id<82>, dim_id<10>>,
                         dim_id_less>,
        type_list<dim_id<3>, dim_id<9>, dim_id<10>, dim_id<27>, dim_id<38>, dim_id<43>, dim_id<82>>>);