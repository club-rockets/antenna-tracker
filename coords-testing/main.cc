#include <iomanip>
#include <iostream>

#include "vector3d.h"

// XY Plan équatorial
// x positif lon -90 à 90
// y positif lon 0 à 180
// z positif pole nord lat 0 à 90


// Coordonnées de test
vec3 coord_ets = vec3(45.4947, -73.5623, 200);
vec3 coord_poly = vec3(45.5044, -73.6129, 400);
vec3 coord_nord = vec3(NORTH_MAGNETIC_POLE_LAT, NORTH_MAGNETIC_POLE_LON, 0);

/**
 *	servo_angle tuple
 *	Contains the pair of angles sent to the servos. 
 */
struct servo_angle {
	double azimuth;
	double altitude;
};

std::ostream& operator<<(std::ostream& os, servo_angle sa)
{
	return os << "[" << sa.azimuth << " " << sa.altitude << "]";
}

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
		(deg((here % reference).Angle(to_target_flat)) <= 90 ? 1 : -1) * deg(reference.Angle(to_target_flat)),
		(deg(here.Angle(to_target)) <= 90 ? 1 : -1) * deg(to_target_flat.Angle(to_target)),
	};

	return result;
}

int main(void)
{
	std::cout << servo_angle_resolve(coord_ets, coord_poly, coord_nord) << std::endl;
}
