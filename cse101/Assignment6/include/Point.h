/*
 * Copyright (C) 2018-2022 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#ifndef _POINT_H_
#define _POINT_H_

class Point {
  public:
    double x;
    double y;

    Point() { x = 0.0, y = 0.0; }
    Point(double dx, double dy) { x = dx; y = dy; }
};

#endif
