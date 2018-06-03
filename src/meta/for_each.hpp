#pragma once

// Importations
#include <type_traits>

// Namespace
namespace meta {

// Métaalgorithme ;)
namespace liste {

template<template<class> class fonction, template<class,class> class fusion, class list, bool fin = list::fin>
struct for_each : fusion<
	typename fonction<typename list::valeur>::type,
	typename for_each<fonction, fusion, typename list::suivant, list::suivant::fin>::type
> {};

template<template<class> class fonction, template<class,class> class fusion, class list>
struct for_each<fonction,fusion,list,true> : fonction<
	typename list::valeur
> {};

} // liste

namespace tableau {

template<template<class> class fonction, template<class,class> class fusion, class I, I v, I... vals>
struct for_each : fusion<
	typename fonction<std::integral_constant<I, v>>::type,
	typename for_each<fonction, fusion, I, vals...>::type
> {};

template<template<class> class fonction, template<class,class> class fusion, class I, I v>
struct for_each<fonction,fusion,I,v> : fonction<
	std::integral_constant<I,v>
> {};

} // tableau
} // meta
