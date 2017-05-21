#include <iomanip>
#include <iostream>

#include "network.h"
#include "resolver.h"

void print_usage()
{
	std::cout << "Usage: tracker [-p port]" << std::endl;
}

int main(int argc, const char* argv[])
{
	uint16_t udp_port = 8112;

	// Parse arguments
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {

			// For all letters following the dash
			bool skip = false;
			for (uint j = 1; j < strlen(argv[i]) && !skip; j++) {
				switch (argv[i][j]) {

				// If the command is 'p', the next arg should be the port number.
				// Read the port number and skip to the following argument.
				// Else, warn the user about correct usage
				case 'p':
					if (argc > i + 1) {
						udp_port = atoi(argv[i + 1]);
						skip = true;
						i++;
					} else {
						print_usage();
					}
					break;

				// If the command is unknown, warn the user about correct usage
				default:
					print_usage();
					break;
				}
			}
		}
	}

	// Check udp port
	if (udp_port < 1024) {
		std::cout << "Cannot bind to port under 1024. Defaulting to port 8112." << std::endl;
		udp_port = 8112;
	}

	// Debug values, here is ETSMTL and reference is geographic north
	//Resolver resolver(vec3(45.4947, -73.5623, 216), vec3(90, 0, 0));
	Resolver resolver(vec3(43.896283333, -72.51835, 85), vec3(90, 0, 0));

	// Start network service
	boost::asio::io_service io_service;
	NetworkClient network(io_service, udp_port, resolver);
	io_service.run();
}
