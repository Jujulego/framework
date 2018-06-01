#pragma once

// Importations
#include "meta.hpp"

// Namespace
namespace physics {
namespace meta {

// Méta-algo
template<class L1, class L2, template<class,class> class op, bool FIN = L1::fin>
struct apply_each {
	// Alias
	using type = typename meta::liste<
		typename op<
			typename L1::valeur,
			typename L2::valeur
		>::type,
		typename apply_each<
			typename L1::suivant,
			typename L2::suivant,
			op,
			res,
			L1::suivant::fin
		>::type
	>::type;
};

template<class L1, class L2, template<class,class> class op>
struct apply_each<L1,L2,op,true> {
	// Alias
	using type = meta::liste<typename op<
		typename L1::valeur,
		typename L2::valeur
	>::type>;
};

// Métafonctions
template<class L1, class L2>
struct mul : apply_each<L1,L2,meta::add>;

template<class L1, class L2>
struct div : apply_each<L1,L2,meta::sub>;

} // meta
} // physicis
