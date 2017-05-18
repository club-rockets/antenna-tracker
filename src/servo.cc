/*
	file: 	servo.h
	author:	David Bourgault

	description: implementation file for functions pertaining to servos
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

#include "servo.h"

#include "constants.h"

std::ostream& operator<<(std::ostream& os, servo_angle sa)
{
	return os << "[" << sa.azimuth << " " << sa.altitude << "]";
}

servo_angle servo_angle_resolve(vec3 here, vec3 target, vec3 reference)
{
	// Transform LatLonAlt spherical coordinates to cartesian space;
	here = here.Cartesian();
	target = target.Cartesian();
	reference = reference.Cartesian();

	// Find direction vector from here to reference
	// This vectors are parallel to the ground plane at "here"
	vec3 to_reference_flat = (reference - here) - ((reference - here).Project(here));

	// Find direction vector from here to target
	vec3 to_target = (target - here);

	// Find the direction vector that is parallel to the ground plane at "here"
	vec3 to_target_flat = to_target - to_target.Project(here);

	// Result is returned as vec3
	// x is azimuth
	// y is altitude
	// z is unused (0)
	servo_angle result = {
		(deg((here % to_reference_flat).Angle(to_target_flat)) <= 90 ? 1 : -1) * deg(to_reference_flat.Angle(to_target_flat)),
		(deg(here.Angle(to_target)) <= 90 ? 1 : -1) * deg(to_target_flat.Angle(to_target)),
	};

	return result;
}