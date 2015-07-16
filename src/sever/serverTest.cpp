#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
using namespace boost;
int main(int argc, char* argv[]){
	boost::asio::io_service io_service;
	while(1){
		tcp::socket socket(io_service);
		tcp::endpoint end_point(boost::asio::ip::address::from_string("127.0.0.1"), 3200);
		socket.connect(end_point);
		std::array<char, 1000> buf;
		boost::system::error_code error;
		system::error_code ignored_error;

		std::string cmd;
		std::cin>>cmd;
		socket.write_some(asio::buffer(cmd), error);
		size_t len = socket.read_some(boost::asio::buffer(buf), error);
		std::cout<<"result:";
		std::cout.write(buf.data(), len);
		std::cout<<"\n";
	}
}