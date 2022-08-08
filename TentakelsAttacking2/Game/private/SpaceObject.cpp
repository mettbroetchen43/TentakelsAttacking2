//
// PurpurTentakel
// 08.08.22
//

#include "SpaceObject.h"

SpaceObject::SpaceObject(double x, double y) 
	: m_position(x,y) { }

Vec2<double> SpaceObject::GetPosition() const {
	return m_position;
}
