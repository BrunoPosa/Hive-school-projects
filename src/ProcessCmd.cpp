#include "../inc/Server.hpp"

//processCommand function to handle incoming commands from clients
void Server::dispatchCommand(int fd, const std::string& message)
{
	std::cerr << "dispatchCmd() message: " << message << std::endl;
	std::istringstream iss(message);

	std::string command;
	if (iss) {
		iss >> command;
	}

	auto it = cmds_.find(command);//what does in case of QUIT iss reutrn if there is no vector words after 'quit'?
    if (it != cmds_.end()) {
        it->second(fd, t_data{message, tokenize(iss)});
    } else {
		std::cerr << "Unknown command received from FD: " << fd << " - " << command << std::endl;
    }
}
