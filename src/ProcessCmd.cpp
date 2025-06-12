#include "../inc/Server.hpp"

//processCommand function to handle incoming commands from clients
void Server::dispatchCommand(int fd, const std::string& message)
{
	std::cout << "dispatchCmd() message: " << message << std::endl;
	std::istringstream iss(message);

	std::string command;
	if (iss) {
		iss >> command;
	}
	if (iss.bad()) {
		iss.clear();
		return;
	}
	for (size_t i = 0; i < command.length(); ++i) {
		command[i] = std::toupper(command[i]);
	}

	auto it = cmds_.find(command);
	if (it != cmds_.end()) {
		it->second(fd, t_data{message, tokenize(iss)});
	} else {
		std::cerr << "Unknown command received from FD: " << fd << " - " << command << std::endl;
	}
}
