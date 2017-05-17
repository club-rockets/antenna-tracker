/*
	file:	constants.h
	author:	David Bourgault

	description: defines mathematical and physical constants, along with some 
	useful math shorcuts
*/

#ifndef _constants_h_
#define _constants_h_

#define EARTH_RADIUS 63710088 //meters, according to wolfram alpha

#define rad(deg) 	(deg * M_PI / 180.0)
#define deg(rad) 	(rad * 180.0 / M_PI)

#define sq(x) 		(x * x)

#endif