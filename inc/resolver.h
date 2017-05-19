/*
	file:	resolver.h
	author:	David Bourgault

	description: header class for the resolver class that gets notified of any
	update to gps values, calculates the servo's angle and tells the servo
	controller
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

#ifndef _resolver_h_
#define _resolver_h_

#include "servo.h"
#include "vector3d.h"

class Resolver {
private:
	vec3 here_;
	vec3 target_;
	vec3 reference_;

public:
	Resolver(vec3 here, vec3 target);

	void Resolve();

	// Getters
	vec3 here() { return here_.Spheric(); }
	vec3 target() { return target_.Spheric(); }
	vec3 reference() { return reference_.Spheric(); }

	// Setters
	void here(vec3 here) { here_ = here.Cartesian(); }
	void target(vec3 target) { target_ = target.Cartesian(); }
	void reference(vec3 reference) { reference_ = reference.Cartesian(); }
};

#endif