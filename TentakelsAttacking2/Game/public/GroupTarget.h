//
// PurpurTentakel
// 08.08.22
//

#pragma once
#include "Vec2.hpp"

struct GroupTarget {
	int id;
	Vec2<double> position;

	GroupTarget(int id, double x, double y);
	friend bool operator== (GroupTarget const& lhs, GroupTarget const& rhs);
};
