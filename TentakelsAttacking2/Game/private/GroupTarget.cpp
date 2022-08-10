//
// PurpurTentakel
// 08.08.22
//

#include "GroupTarget.h"

GroupTarget::GroupTarget(int id, double x, double y)
	: id(id),position(x,y) {}

bool operator==(GroupTarget const& lhs, GroupTarget const& rhs) {
	return lhs.id == rhs.id;
}
