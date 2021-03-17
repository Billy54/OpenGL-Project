#pragma once

#ifndef CLIPPING_H
#define CLIPPING_H
#include "triangulate.h"
#include <vector>
#include <assert.h>

class Cliping {

public:

	static int x_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	static int y_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	static void clip(Vector2dVector &poly_points, int &poly_size, int x1, int y1, int x2, int y2);

	static void suthHodgClip(Vector2dVector &p, int poly_size, int clipper_points[][2], int clipper_size);
};
#endif