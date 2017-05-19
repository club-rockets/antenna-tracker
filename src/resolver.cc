/*
	file:	resolver.cc
	author:	David Bourgault

	description: implementation class for the resolver class that gets notified 
	of any update to gps values, calculates the servo's angle and tells the 
	servo controller
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

#include "resolver.h"

#include "constants.h"
#include "servo.h"
#include "vector3d.h"

Resolver::Resolver(vec3 here, vec3 reference)
	: here_(here.Cartesian())
	, reference_(reference.Cartesian())
{
}

void Resolver::Resolve()
{
	// Find direction vector from here to reference
	// This vectors are parallel to the ground plane at "here"
	vec3 to_reference_flat = (reference_ - here_) - ((reference_ - here_).Project(here_));

	// Find direction vector from here to target
	vec3 to_target = (target_ - here_);

	// Find the direction vector that is parallel to the ground plane at "here"
	vec3 to_target_flat = to_target - to_target.Project(here_);

	// Result is returned as vec3
	// x is azimuth
	// y is altitude
	// z is unused (0)
	servo_angle result = {
		(deg((here_ % to_reference_flat).Angle(to_target_flat)) <= 90 ? 1 : -1) * deg(to_reference_flat.Angle(to_target_flat)),
		(deg(here_.Angle(to_target)) <= 90 ? 1 : -1) * deg(to_target_flat.Angle(to_target)),
	};

// servo_controler.update_angles(result);
#ifdef _DEBUG
	std::cout << result << std::endl;
#endif
}