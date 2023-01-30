/*
 * File: Circle.cc
 * By: James Yim
 */

//Includes
#include "Circle.h"

//---= Constructors =---//

Circle::Circle(const Point &c, double r)
{
	center = c;
	radius = r;
}

//---= Getter Functions =---//

//getCenter()
Point Circle::getCenter()
{
	return center;
}

//getRadius()
double Circle::getRadius()
{
	return radius;
}

