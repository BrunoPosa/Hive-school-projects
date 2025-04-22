#include "Connection.hpp"

Connection::Connection() : sock_{},  {
	Socket		sock_;
	std::string	nick_;
	std::string	user_;
	bool		registered_;
}