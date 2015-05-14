#pragma once
#include "socketclient.h"

class CSocketClientSyn
{
public:
	std::string ip;
	short port;
	std::string sendBuff;
	std::vector<char> recvBuff;
	int connStatus;

	boost::asio::io_service ios;
	//typedef boost::shared_ptr<boost::asio::ip::tcp::socket> sock_pt;
	//sock_pt sock;
	boost::asio::ip::tcp::socket sock;
	boost::asio::deadline_timer t;

	CSocketClientSyn();
	virtual ~CSocketClientSyn(void);

	void startConnection();
	void closeConnection();
	std::string sendData(char* pSendBuff,int len);
	std::string recvData(char* pRecvBuff,int len);
	void conn_handler(const boost::system::error_code& error);
	void time_expired(const boost::system::error_code&,boost::asio::ip::tcp::socket *sock);
};
