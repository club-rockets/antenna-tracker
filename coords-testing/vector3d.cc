/*
	file: 	vector3d.cc
	author:	David Bourgault

	description: class implementation for 3-dimensional vectors
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

#include "vector3d.h"

#include <iostream>

#include <cmath>

#include "constants.h"

Vector3D::Vector3D(double x, double y, double z)
	: x_(x)
	, y_(y)
	, z_(z)
{
}

Vector3D Vector3D::Spheric()
{
	Vector3D v;
	double r = sqrt(sq(x_) + sq(y_) + sq(z_));

	v.lon(deg(atan2(y_, x_)));
	v.lat(deg(asin(z_ / r)));
	v.alt(r - EARTH_RADIUS);

	return v;
}

Vector3D Vector3D::Cartesian()
{
	Vector3D v;

	v.x((EARTH_RADIUS + z_) * cos(rad(x_)) * cos(rad(y_)));
	v.y((EARTH_RADIUS + z_) * sin(rad(x_)) * cos(rad(y_)));
	v.z((EARTH_RADIUS + z_) * sin(rad(y_)));

	return v;
}

Vector3D Vector3D::Project(Vector3D u)
{
	return u * (dotp(u) / u.norm_sq());
}

double Vector3D::dotp(Vector3D u)
{
	return (x_ * u.x() + y_ * u.y() + z_ * u.z());
}

Vector3D Vector3D::crossp(Vector3D u)
{
	return Vector3D(
		+(y_ * u.z() - u.y() * z_),
		-(x_ * u.z() - u.x() * z_),
		+(x_ * u.y() - u.x() * y_));
}

double Vector3D::angle(Vector3D u)
{
	return acos((dotp(u)) / (norm() * u.norm()));
}

Vector3D Vector3D::operator+(Vector3D u)
{
	return Vector3D(x_ + u.x(), y_ + u.y(), z_ + u.z());
}

void Vector3D::operator+=(Vector3D u)
{
	x_ += u.x();
	y_ += u.y();
	z_ += u.z();
}

Vector3D Vector3D::operator-(Vector3D u)
{
	return Vector3D(x_ - u.x(), y_ - u.y(), z_ - u.z());
}

void Vector3D::operator-=(Vector3D u)
{
	x_ -= u.x();
	y_ -= u.y();
	z_ -= u.z();
}

Vector3D Vector3D::operator*(double k)
{
	return Vector3D(k * x_, k * y_, k * z_);
}

void Vector3D::operator*=(double k)
{
	x_ *= k;
	y_ *= k;
	z_ *= k;
}

double Vector3D::operator*(Vector3D u)
{
	return dotp(u);
}

Vector3D Vector3D::operator%(Vector3D u)
{
	return crossp(u);
}

std::ostream& operator<<(std::ostream& cout, Vector3D v)
{
	cout << "[" << v.x_ << " " << v.y_ << " " << v.z_ << "]";
	return cout;
}

void Vector3D::norm(double norm)
{
	double current = Vector3D::norm();
	x_ = norm * (x_ / current);
	y_ = norm * (y_ / current);
	z_ = norm * (z_ / current);
}