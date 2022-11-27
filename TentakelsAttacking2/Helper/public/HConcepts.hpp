//
// PurpurTentakel
// 22.11.22
//

#pragma once
#include <concepts>

/**
 * concepts for a templateparameter to be only a arithmentic datatype.
 */
template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;
