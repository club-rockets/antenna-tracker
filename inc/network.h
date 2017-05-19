/*
	file:	network.h
	author:	David Bourgault

	description: header class for a simple UDP server that listens on port 8112
	for JSON data containing "lat" "lon" "alt" values
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

#ifndef _network_h_
#define _network_h_

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "resolver.h"

using boost::asio::ip::udp;

class NetworkClient {
private:
	udp::socket socket_;
	udp::endpoint remote_endpoint_;
	boost::array<char, 100> recv_buffer_;

	Resolver& resolver_;

public:
	NetworkClient(boost::asio::io_service& io_service, Resolver& resolver);

	void StartReceive();
	void HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);
};

#endif