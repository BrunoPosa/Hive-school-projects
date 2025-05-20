#include "../inc/irc.hpp"

void Server::handleClient(size_t index) {
	char buffer[1024];
	ssize_t bytesRead = recv(pollFds_[index].fd, buffer, sizeof(buffer) - 1, 0);
	if (bytesRead <= 0) {
		handleClientError(bytesRead == 0 ? 0 : errno, index);
		return;
	}
	
	buffer[bytesRead] = '\0'; // Null-terminate
	int fd = pollFds_[index].fd;
	// Split the input by \r\n and process each command
	std::string input(buffer);
	size_t pos = 0;
	std::string line;
	while ((pos = input.find("\r\n")) != std::string::npos) {
		line = input.substr(0, pos);
		processCommand(fd, line);
		input.erase(0, pos + 2); // Move past \r\n
	}
}

Client::~Client() {} // 

Client::Client(int fd) : fd(fd), nick("guest"), user("guest") // Constructor with fd
{
	this->authenticated = false;
	this->nickReceived = false;
	this->userReceived = false;
	this->passReceived = false;
	this->modeReceived = false;
	this->whois = false;
}

Client::Client() : fd(-1), nick("guest"), user("guest") // Constructor without fd
{
	this->authenticated = false;
	this->nickReceived = false;
	this->userReceived = false;
	this->passReceived = false;
	this->modeReceived = false;
	this->whois = false;
}

Client::Client(std::string nick, std::string user, int fd): fd(fd), nick(nick), user(user) {}

Client::Client(const Client &other)
{
	*this = other;
}

Client &Client::operator=(const Client &other)
{
	if (this != &other)
	{
		this->nick = other.nick;
		this->user = other.user;
		this->fd = other.fd;
		this->joinedChannels = other.joinedChannels;
	}
	return *this;
}

bool Client::isInChannel(const std::string &channel)
{
	if (joinedChannels.find(channel) != joinedChannels.end())
		return true;
	return false;
}

bool Client::getOperator(const std::string &channel)
{
	if(isInChannel(channel))
		return joinedChannels[channel];
	return false;
}

void Client::setNick(const std::string &nick)
{
	this->nick = nick;
}

void Client::setUser(const std::string &user)
{
	this->user = user;
}
void Client::setNickReceived()
{
	this->nickReceived = true;
}
void Client::setUserReceived()
{
	this->userReceived = true;
}
void Client::setPassReceived()
{
	this->passReceived = true;
}
void Client::setModeReceived()
{
	this->modeReceived = true;
}
void Client::setAuthenticated()
{
	this->authenticated = true;
}
void Client::joinChannel(const std::string &channel, bool is_operator)
{
	if (is_operator)
	{
		joinedChannels[channel] = true;
		std::cerr << "added operator" << std::endl;
	}
	else
	{
		joinedChannels[channel] = false;
		std::cerr << "not operator" << std::endl;
	}
}

void Client::leaveChannel(const std::string &channel)
{
	joinedChannels.erase(channel);
}
bool Client::isOperator(const std::string &channel)
{
	if (joinedChannels.find(channel) != joinedChannels.end())
		return true;
	return false;
}
void Client::setOperator(const std::string &channel, bool is_operator)
{
	if (isInChannel(channel))
		joinedChannels[channel] = is_operator;
}

std::string Client::getNick() const
{
	return this->nick;
}

std::string Client::getUser() const
{
	return this->user;
}

bool Client::hasReceivedNick() const
{
	return this->nickReceived;
}

bool Client::hasReceivedUser() const
{
	return this->userReceived;
}

bool Client::hasReceivedPass() const
{
	return this->passReceived;
}

bool Client::hasReceivedMode() const
{
	return this->modeReceived;
}

bool Client::isAuthenticated() const
{
	return this->authenticated;
}

int Client::getFd() const
{
	return this->fd;
}

const std::map<std::string, bool>& Client::getJoinedChannels() const
{
	return this->joinedChannels;
}

