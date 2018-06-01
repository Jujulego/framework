#pragma once

// Importations
//#include <type_traits>

// Namespace
namespace meta {

// Métaalgorithme ;)
template<class list, template<class> class fonction, template<class,class> class fusion, bool fin = list::fin>
struct for_each {
	// Alias
	using type = typename fusion<
		typename for_each<typename list::suivant, fonction, fusion, list::suivant::fin>::type,
		typename fonction<typename list::valeur>::type
	>::type;
};

template<class list, template<class> class fonction, template<class,class> class fusion>
struct for_each<list,fonction,fusion,true> {
	// Alias
	using type = typename fonction<typename list::valeur>::type;
};

} // meta
