#include "SocketClient.h"

//using boost::asio::ip::tcp;

//boost::asio::io_service io_service;
//tcp::socket sock(io_service);
//tcp::resolver resolver(io_service);

SocketClient::SocketClient(boost::asio::io_service& io_service_):io_service(io_service_),
sock(io_service_),resolver(io_service_)
{
}

SocketClient::~SocketClient(void)
{
}

void SocketClient::startConnection()
{
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), ip, port);
	boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

	sock.connect(*iterator);
}


void SocketClient::closeConnection()
{
	sock.close();
}


void SocketClient::sendData()
{
	boost::asio::write(sock, boost::asio::buffer(sendBuff));
}

void SocketClient::recvData()
{
	size_t reply_length = sock.read_some(boost::asio::buffer(recvBuff));
	/*size_t reply_length = boost::asio::read(sock,
		boost::asio::buffer(recvBuff));*/
}