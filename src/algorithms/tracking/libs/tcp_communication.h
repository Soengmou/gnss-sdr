/*!
 * \file tcp_communication.h
 * \brief Library with the definition of the TCP communication class
 * \author David Pubill, 2011. dpubill(at)cttc.es
 *
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2012  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#ifndef TCP_COMMUNICATION_H_
#define TCP_COMMUNICATION_H_

#include <boost/asio.hpp>
#include "tcp_packet_data.h"

class tcp_communication
{
public:

	tcp_communication();
	~tcp_communication();

	int listen_tcp_connection(size_t d_port_);
	void send_receive_tcp_packet(boost::array<float, 7> buf, tcp_packet_data *tcp_data_);
	void close_tcp_connection(size_t d_port_);

private:
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::socket tcp_socket_;
};

#endif