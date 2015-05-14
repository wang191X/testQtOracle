#pragma once
#include <string>
#include <vector>
#include <boost/asio.hpp>





class SocketClient
{
public:
	SocketClient(boost::asio::io_service& io_service_);
	virtual ~SocketClient(void);

//protected:
	std::string ip;
	std::string port;
	enum { header_length = 8 };
	std::string sendBuff;
	std::vector<char> recvBuff;

	boost::asio::io_service& io_service;
	boost::asio::ip::tcp::socket sock;
	boost::asio::ip::tcp::resolver resolver;

	virtual void startConnection();
	virtual void closeConnection();
	virtual void sendData();
	virtual void recvData();

private:

};

