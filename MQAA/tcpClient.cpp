#include <iostream>
#include <functional>
using namespace std;

#include "ec/loop.h"
#include "ec/tcpServer.h"
#include "ec/tcpClient.h"
#include "ec/timer.h"
#include "ec/singleton.h"

#include "index.h"
#include "ec/MQAA.pb.h"
#include <google/protobuf/message.h>

char tosend[1024];
class ExampleTcpClient : public ec::TcpClient
{
public:
	ExampleTcpClient(const ec::Loop &loop):
		ec::TcpClient(loop)
	{}

protected:
	virtual void onRead()
	{
		cout<<"ExampleTcpClient:=:"<<__FUNCTION__<<endl;
	}

	virtual void onDisconnected()
	{
		cout << "ExampleTcpClient::" << __FUNCTION__ << endl;
	}

	virtual void onConnected(int error)
	{
		
		ec::LoginRequest logreq; 
//		message.set_msg_type(ec::MSG::Login_Request);
//		message.set_sequence(0xffffffff);
//		message.set_session_id(2);
//		::ec::Request* request=message.mutable_request();
//		//request->mutable_login()->set_ttl(2);
//		::ec::LoginRequest* loginreq= request->mutable_login();
//		loginreq->set_username("wangmin");
//		loginreq->set_password("wangmin");
//		
//		int byte_size = message.ByteSize();
//		char* tosend;
//		//message.SerailzeToString(&tosend);
//		uint8_t* start = reinterpret_cast<uint8_t*>(tosend);
//		uint8_t* end= message.SerializeWithCachedSizesToArray(start);
//		long int  data_size=(long int)(end-start);
//
//
//		cout << "ExampleTcpClient::" << __FUNCTION__ << endl;
//		send(tosend, data_size);
		
		logreq.set_username("wangmin");
		logreq.set_password("Wangmin");
		int byte_size=logreq.ByteSize();
		uint8_t* start = reinterpret_cast<uint8_t*>(tosend);
		uint8_t* end= logreq.SerializeWithCachedSizesToArray(start);
		 int  data_size=strlen(tosend);
		// char temp[data_size+1];
		 
		//strcpy(temp,tosend);
		//temp[data_size]='\0';
	//	send(tosend, byte_size);
		tosend[data_size]='\0';
		send(tosend,(uint32_t)(data_size));
	//	send(tosend, (uint32_t)(strlen(tosend)));
//		int a=0;
//		cout<<a<<endl;
//		cout << "ExampleTcpClient::" << __FUNCTION__ << endl;
//		send("hellohello",10);
		
	}
};


class ExampleTcpClientManager : public ec::Loop
{
public:
	ExampleTcpClientManager():
		_client(*this),
		_timer(*this)
	{
		_timer.startForever(5000, std::bind(&ExampleTcpClientManager::tick, this));
	}

protected:
	void tick()
	{
		cout << "round " << _timer.getCurRound() << endl;
		if (!_client.isConnected())
		{
			_client.connect("127.0.0.1", 4567);
		}

//		if (_timer.getCurRound() >= 3)
//		{
//			ExampleTcpServerSingleton::instance().stop();
//			stop();
//		}
	}
private:
	ExampleTcpClient _client;
	ec::Timer _timer;
};

void tcpClient()
{

	ExampleTcpClientManager clientManager;
	
	clientManager.startThread();
	clientManager.waitThread();
//	clientManager.startThread();
//	clientManager.waitThread();
	
}


