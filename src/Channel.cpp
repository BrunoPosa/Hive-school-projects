#include "../inc/Server.hpp"

Channel::Channel(const std::string &name, clientMap* ptrToAllClients)
: name_(name), topic_(""), pwd_(""), userLimit_(-1), inviteOnly_(false), topicRestrictedToOperators_(true), allClientsPtr_(ptrToAllClients) {}

Channel::~Channel() {
	allClientsPtr_ = nullptr;
}

Channel::Channel(const Channel &other)
	: name_(other.name_),
	  topic_(other.topic_),
	  pwd_(other.pwd_),
	  invitedUsers_(other.invitedUsers_),
	  chClients_(other.chClients_),
	  operators_(other.operators_),
	  userLimit_(other.userLimit_),
	  inviteOnly_(other.inviteOnly_),
	  topicRestrictedToOperators_(other.topicRestrictedToOperators_),
	  allClientsPtr_(other.allClientsPtr_)
{}

Channel &Channel::operator=(const Channel &other)
{
	if (this != &other)
	{
		this->name_ = other.name_;
		this->topic_ = other.topic_;
		this->pwd_ = other.pwd_;
		this->invitedUsers_ = other.invitedUsers_;
		this->chClients_ = other.chClients_;
		this->operators_ = other.operators_;
		this->userLimit_ = other.userLimit_;
		this->inviteOnly_ = other.inviteOnly_;
		this->topicRestrictedToOperators_ = other.topicRestrictedToOperators_;
		this->allClientsPtr_ = other.allClientsPtr_;
	}
	return *this;
}

////////////////////////////////////////////////////////////////////////////

// In Channel.cpp
int Channel::getClientFdByNick(const std::string &nickname, const clientMap& clients) const
{
	for (clientMap::const_iterator it = clients.begin(); it != clients.end(); ++it){
		int fd = it->first;
		clientMap::const_iterator cit = clients.find(fd);
		if (cit != clients.end() && cit->second.getNick() == nickname) {
			return fd;
		}
	}
	return -1; // Not found
}

////////////////////////////////////////////////////////////////

void Channel::addInvitedUser(const int& client_fd)
{
	if (std::find(this->invitedUsers_.begin(), this->invitedUsers_.end(), client_fd) == this->invitedUsers_.end())
		this->invitedUsers_.push_back(client_fd);
}

void Channel::removeInvitedUser(const int& client_fd)
{
	std::vector<int>::iterator it = std::find(this->invitedUsers_.begin(), this->invitedUsers_.end(), client_fd);
	if (it != this->invitedUsers_.end())
		this->invitedUsers_.erase(it);
}

void Channel::addClient(int fd)
{
	if (std::find(this->chClients_.begin(), this->chClients_.end(), fd) == this->chClients_.end())
		this->chClients_.push_back(fd);
}

void Channel::removeClient(int fd)
{
	std::vector<int>::iterator it = std::find(this->chClients_.begin(), this->chClients_.end(), fd);
	if (it != this->chClients_.end())
		this->chClients_.erase(it);
}

void Channel::broadcast(const std::string& message, const std::string& sender_nick, int except_fd) // send to all clients except the except_fd
{
(void)sender_nick;
	int cliFd = 0;
	for (unsigned long i = chClients_.size(); i-- > 0;)
	{
		cliFd = chClients_.at(i);
		if (cliFd != except_fd && allClientsPtr_ != nullptr) {
			allClientsPtr_->at(cliFd).toSend(message.c_str());
		}
	}
}

void Channel::broadcastToAll(const std::string& message) {
    for (std::vector<int>::iterator it = this->chClients_.begin(); it != this->chClients_.end(); ++it) {
        allClientsPtr_->at(*it).toSend(message.c_str());
    }
}

void Channel::addOperator(int fd) {
	if (!isOperator(fd))
		this->operators_.push_back(fd);
}

void Channel::removeOperator(int fd) {
	std::vector<int>::iterator it = std::find(this->operators_.begin(), this->operators_.end(), fd);
	if (it != this->operators_.end())
		this->operators_.erase(it);
}
