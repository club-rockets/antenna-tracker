/*
	file:	network-testing/main.cc
	author:	David Bourgault

	description: simple program that sends debug GPS coordinates to the UDP 
	listener of the main program.
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

/* 
original file: client.cpp
original author: Christopher M. Kohlhoff

Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include <iostream>
#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::udp;

void print_usage()
{
	std::cout << "Usage: nettest [-p port]" << std::endl;
}


int main(int argc, char* argv[])
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

	// Start network service
	boost::asio::io_service io_service;

	udp::resolver resolver(io_service);
	udp::resolver::query query(udp::v4(), "127.0.0.1", std::to_string(udp_port));
	udp::endpoint receiver_endpoint = *resolver.resolve(query);

	udp::socket socket(io_service);
	socket.open(udp::v4());

	// Debug values, coordinates are for polymtl and should give an angle of ~75 with the north pole
	std::string data = "{\"lat\":45.4947,\"lon\":-73.5623,\"alt\":216}";

	// Start loop, send every time player hits enter
	while (true) {
		fflush(stdin);
		getc(stdin);

		socket.send_to(boost::asio::buffer(data), receiver_endpoint);
	}
}