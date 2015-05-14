#include "SocketClient1.h"
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/serialization/vector.hpp>

SocketClient1::SocketClient1(boost::asio::io_service& io_service_):SocketClient(io_service_)
{
	ip="127.0.0.1";
	port="4096";
	startConnection();
}

SocketClient1::~SocketClient1(void)
{
	closeConnection();
}

void SocketClient1::sendData1()
{
	// Create the data to be sent to each client.
//	SACL s;
//	sacls_.push_back(s);
//	sacls_.push_back(s);
	toSerialize();
	sendBuff=outbound_data_;
	sendData();
}

int SocketClient1::recvData1()
{
	// Create the data to be sent to each client.
	recvBuff.resize(1024);
	recvData();
	inbound_data_=recvBuff;
	fromSerialize();

	return sacls_[0].cmdType;
}

void SocketClient1::toSerialize()
{
	// Serialize the data first so we know how large it is.
	/*std::ostringstream archive_stream;
	boost::archive::text_oarchive archive(archive_stream);
	archive << sacls_;
	outbound_data_ = archive_stream.str();*/
}

void SocketClient1::fromSerialize()
{
	/*std::string archive_data(&inbound_data_[0], inbound_data_.size());
	std::istringstream iarchive_stream(archive_data);
	boost::archive::text_iarchive iarchive(iarchive_stream);
	iarchive >> sacls_;*/
}