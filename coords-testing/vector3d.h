/*
	file: 	vector3d.h
	author:	David Bourgault

	description: class declaration for 3-dimensional vectors
*/

/*
Copyright 2017 David Bourgault

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _vec3_h_
#define _vec3_h_

#include <iostream>

#include <cmath>

#include "constants.h"

// ======== 3-Dimensional Vector class ======== //
class Vector3D {
private:
	// Components. The same variables are used if the vector is used
	// as a Spheric coordinate tuple.
	double x_, y_, z_;

public:
	// ======== Constructor ======== //
	Vector3D(double x = 0, double y = 0, double z = 0);

	// ======== Conversions ======== //
	// Return a copy of this vector in spherical coordinates
	// Calling this on a cartesian vector will result in garbage values
	Vector3D Spheric();

	// Return a copy of this vector in cartesian coordinates
	// Calling this on a cartesian vector will result in garbage values
	Vector3D Cartesian();

	// ======== Vector algebra ======== //
	// Return the projection of this onto u
	Vector3D Project(Vector3D u);

	// Return the dot product of this vector and u
	double dotp(Vector3D u);

	// Return the cross-product of this vector and u
	Vector3D crossp(Vector3D u);

	// Angle between two vectors
	// NOTE: This should maybe be static, or renamed for clarity
	double angle(Vector3D u);

	// ======== Operator overloads ======== //
	// Vector addition
	Vector3D operator+(Vector3D u);
	void operator+=(Vector3D u);

	// Vector substraction
	Vector3D operator-(Vector3D u);
	void operator-=(Vector3D u);

	// Vector multiplication by a constant
	Vector3D operator*(double k);
	void operator*=(double k);

	// Vector dot product
	double operator*(Vector3D u);

	// Vector cross product
	// Reuses the % operator since it looks similar to a ⨯
	Vector3D operator%(Vector3D u);

	// Output vector as "[x y z]"
	friend std::ostream& operator<<(std::ostream& cout, Vector3D v);

	// ======== Getters ======== //
	// Get components
	double x() { return x_; }
	double y() { return y_; }
	double z() { return z_; }

	// Get spherical components, simply a rename of xyz for readability
	double lon() { return x_; }
	double lat() { return y_; }
	double alt() { return z_; }

	// Get the norm of the vector
	double norm_sq() { return (sq(x_) + sq(y_) + sq(z_)); }
	double norm() { return sqrt(norm_sq()); }

	// ======== Setters ======== //
	// Set components
	void x(double x) { x_ = x; }
	void y(double y) { y_ = y; }
	void z(double z) { z_ = z; }

	// Set spherical components, simply a rename of xyz for readability
	void lon(double lon) { x_ = lon; }
	void lat(double lat) { y_ = lat; }
	void alt(double alt) { z_ = alt; }

	// Set the norm of the vector
	void norm(double norm);
};

typedef Vector3D vec3;

#endif