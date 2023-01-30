/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#pragma once

#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Containable.h"
#include "Point.h"
//This pretty much just said that Circle is a containable
class Circle : public Containable 
{
	Point center;
	double radius;


  public:
    // do not modify or remove this constructor
    Circle(const Point &center, double radius);

    // do not modify or remove these functions
    bool ContainedBy(Circle &circle);
    bool ContainedBy(Polygon &polygon);
    bool ContainedBy(ReuleauxTriangle &rt);

    //Getter Functions
    Point getCenter();
    double getRadius();

    //Manipulator Functions
    void moveCircle(const Point); //moves the circle to that point
    void setRadius(double radius); //sets the radius of a circle
	





};

#endif
