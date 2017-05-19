#include <iomanip>
#include <iostream>

#include "network.h"
#include "resolver.h"

int main(int argc, const char* argv[])
{
	// Debug values, here is ETSMTL and reference is geographic north
	Resolver resolver(vec3(45.4947, -73.5623, 216), vec3(90, 0, 0));
	boost::asio::io_service io_service;
	NetworkClient network(io_service, resolver);
	io_service.run();


	fflush(stdin);
	getc(stdin);
}
