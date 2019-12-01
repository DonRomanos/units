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

#pragma once

#include <units/bits/fixed_string.h>
#include <units/bits/unit_concept.h>
#include <units/unit.h>
#include <type_traits>

namespace units {

/**
 * @brief A dimension of a base quantity
 *
 * Measurement unit that is adopted by convention for a base quantity (a quantity that can not be expressed in terms of
 * the other quantities within that subset) in a specific system of units.
 *
 * Pair of Name and Unit template parameter forms an unique identifier of the base dimension. The same identifiers can
 * be multiplied and divided which will result with an adjustment of its factor in an Exponent (in case of zero the
 * dimension will be simplified and removed from further analysis of current expresion). In case the Name is the same
 * but the Unit differs (i.e. mixing SI and CGS length), there is no automatic simplification but is possible to force
 * it with a quantity_cast.
 *
 * @tparam Name an unique identifier of the base dimension used to provide dimensional analysis support
 * @tparam U a base unit to be used for this base dimension
 */
template<basic_fixed_string Name, Unit U>
struct base_dimension {
  using base_type = base_dimension;
  static constexpr auto name = Name;
  using coherent_unit = U;
};

// BaseDimension
namespace detail {

template<typename T>
inline constexpr bool is_base_dimension = false;

template<basic_fixed_string Name, typename... Params>
inline constexpr bool is_base_dimension<base_dimension<Name, Params...>> = true;

}  // namespace detail

template<typename T>
concept BaseDimension = detail::is_base_dimension<typename T::base_type>;

// base_dimension_less
// TODO Remove the below when https://bugs.llvm.org/show_bug.cgi?id=32208 is fixed
// clang-format off
template<BaseDimension D1, BaseDimension D2>
struct base_dimension_less : std::bool_constant<D1::name < D2::name> {};
// clang-format on

}  // namespace units