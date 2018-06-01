#pragma once

// Importations
#include <type_traits>

// Namespace
namespace meta {

// Métaclasses
template<bool V>
using bool_ = std::conditional<V, std::true_type, std::false_type>;

template<int V>
using int_ = std::integral_constant<int,V>;

template<size_t V>
using size_ = std::integral_constant<size_t,V>;

} // meta
