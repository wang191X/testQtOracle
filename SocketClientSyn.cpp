#include "SocketClientSyn.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

CSocketClientSyn::CSocketClientSyn():sock(ios),t(ios,boost::posix_time::seconds(3))
{
	//boost::asio::io_service ios;
	ip="127.0.0.1";
	//std::string ip1="11.39.109.125";
	port=6688;
	connStatus=0;
}

CSocketClientSyn::~CSocketClientSyn(void)
{
}

void CSocketClientSyn::conn_handler(const boost::system::error_code& error)
{
	if(error)
	{
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(ip),port);
		sock.async_connect(ep,bind(&CSocketClientSyn::conn_handler,this,boost::asio::placeholders::error));
		return;
	}

	//normal conn
	t.cancel();

	//recv data
}

void CSocketClientSyn::time_expired(const boost::system::error_code& error,boost::asio::ip::tcp::socket *sock)
{
	ios.stop();

	if (error != boost::asio::error::operation_aborted)
	{
		// Timer was not cancelled, take necessary action.
		sock->close();
		//std::cout<<"time expired"<<std::endl;
		connStatus=-1;
		return;
	}

	connStatus=1;
}

void CSocketClientSyn::startConnection()
{
	try
	{
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(ip),port);
		sock.async_connect(ep,bind(&CSocketClientSyn::conn_handler,this,boost::asio::placeholders::error));
		t.async_wait(bind(&CSocketClientSyn::time_expired,this,boost::asio::placeholders::error,&sock));
		ios.run();
		return;
	}
	catch (std::exception& e)
	{
		std::cout<<e.what()<<std::endl;
	}
}

void CSocketClientSyn::closeConnection()
{
	sock.close();
}

std::string CSocketClientSyn::sendData(char* pSendBuff,int len)
{
	try
	{
		sock.write_some(boost::asio::buffer(pSendBuff,len));
	}
	catch (std::exception& e)
	{
		//std::cout<<e.what()<<std::endl;
		return e.what();
	}

	return "";
}

std::string CSocketClientSyn::recvData(char* pRecvBuff,int len)
{
	try
	{
		sock.read_some(boost::asio::buffer(pRecvBuff,len));
	}
	catch (std::exception& e)
	{
		//std::cout<<e.what()<<std::endl;
		return e.what();
	}

	return "";
}

