/*
	file:	network.cc
	author:	David Bourgault

	description: implementation class for a simple UDP server that listens on port 
	8112 for JSON data containing "lat" "lon" "alt" values
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

#include "network.h"

#include <exception>
#include <string>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "json.h"
#include "resolver.h"
#include "vector3d.h"

NetworkClient::NetworkClient(boost::asio::io_service& io_service, uint16_t udp_port, Resolver& resolver)
	: socket_(io_service, udp::endpoint(udp::v4(), udp_port))
	, resolver_(resolver)
{
	StartReceive();
}

void NetworkClient::StartReceive()
{
	socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
		boost::bind(&NetworkClient::HandleReceive, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void NetworkClient::HandleReceive(const boost::system::error_code& error,
	std::size_t bytes_transferred)
{
	nlohmann::json json;

	try {
		json = nlohmann::json::parse(recv_buffer_.begin(), recv_buffer_.begin() + bytes_transferred);

		if (json.count("lat") && json.count("lon") && json.count("alt")) {
			resolver_.target(vec3(json["lat"], json["lon"], json["alt"]));
			resolver_.Resolve();
		} else {
#ifdef _DEBUG
			std::cout << "[JSON] Incomplete JSON." << std::endl;
#endif
		}
	} catch (std::exception e) {
#ifdef _DEBUG
		std::cout << "[JSON] Parsing error. " << std::endl;
#endif
	}

	StartReceive();
}