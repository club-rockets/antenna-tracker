/*
	file: 	servo.h
	author:	David Bourgault

	description: header file for functions pertaining to servos
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

#ifndef _servo_h_
#define _servo_h_

#include "vector3d.h"

/**
 *	servo_angle tuple
 *	Contains the pair of angles sent to the servos. 
 */
struct servo_angle {
	double azimuth;
	double altitude;
};

std::ostream& operator<<(std::ostream& os, servo_angle sa);

/**
 * servo_angle_resolve()
 *
 * TODO: Document me
 * FIXME: Using Vector3D for Spherical, Cartesian and Servo's angles seems confusing
 *		Maybe use a different data struct for each. Only cartesian coordinates need
 *		operator overload and algebra...
 *
 *	param:
 *		here: 		GPs coordinates of the antenna tracker
 *		target:		GPS coordinates of the target/rocket
 *		reference:	GPS coordinates of a point in front of the antenna tracker
 *
 *	return: a struct containing azimuth and altitude angles
 */
servo_angle servo_angle_resolve(vec3 here, vec3 target, vec3 reference);

#endif