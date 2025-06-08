#include "../inc/Server.hpp"

Channel::Channel(std::map<int, Client>* ptrToAllClients)
: name_(""), topic_(""), pwd_(""), userLimit_(-1), inviteOnly_(false), topicRestrictedToOperators_(true), allClientsPtr_(ptrToAllClients) {}

Channel::Channel(const std::string &name, std::map<int, Client>* ptrToAllClients)
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

const std::string& Channel::getName() const
{
	return this->name_;
}

const std::string& Channel::getTopic() const
{
	return this->topic_;
}

const std::string& Channel::getTopicSetter() const
{
	return this->topicSetter_;
}

std::chrono::system_clock::time_point Channel::getTopicSetTime() const
{
	return this->topicSetTime_;
}

const std::string& Channel::getPwd() const
{
	return this->pwd_;
}

int Channel::getUserLimit() const
{
	return this->userLimit_;
}

bool Channel::getInviteOnly() const
{
	return this->inviteOnly_;
}

bool Channel::getIsUserInvited(const int& fd) const
{
	return std::find(this->invitedUsers_.begin(), this->invitedUsers_.end(), fd) != this->invitedUsers_.end();
}

bool Channel::getTopicRestricted() const
{
	return this->topicRestrictedToOperators_;
}

bool Channel::hasClient(int fd) const {
    return std::find(chClients_.begin(), chClients_.end(), fd) != chClients_.end();
}

// In Channel.cpp
int Channel::getClientFdByNick(const std::string& nickname, const std::map<int, Client>& clients) const {
std::cout << "getCLientFDbyNick" << std::endl;
	for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it){
		int fd = it->first;
		std::map<int, Client>::const_iterator cit = clients.find(fd);
		if (cit != clients.end() && cit->second.getNick() == nickname) {
			return fd;
		}
	}
	return -1; // Not found
}

/////////////////////////////////////////////////////////////////////////

void Channel::setPassword(const std::string& newPassword)
{
	this->pwd_ = newPassword;
}

void Channel::setUserLimit(int limit)
{
	this->userLimit_ = limit;
}

void Channel::setInviteOnly(bool inviteOnly)
{
	this->inviteOnly_ = inviteOnly;
}

void Channel::setTopicRestrictedToOperators(bool restricted)
{
	this->topicRestrictedToOperators_ = restricted;
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

void Channel::setTopic(const std::string& newTopic)
{
	this->topic_ = newTopic;
}

void Channel::setTopicSetter(const std::string& setter_nick)
{
	this->topicSetter_ = setter_nick;
}

void Channel::setTopicSetTime(const std::chrono::system_clock::time_point& time)
{
	this->topicSetTime_ = time;
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
		if (cliFd != except_fd && allClientsPtr_ != nullptr)
		{
			try {
				allClientsPtr_->at(cliFd).toSend(message.c_str());
			} catch (std::exception& e) {
				std::cerr << "channel broadcast - accessing Client map at key: " << cliFd << " failed." << e.what() << std::endl;
			}
		}
	}
}

void Channel::broadcastToAll(const std::string& message) {
    for (std::vector<int>::iterator it = this->chClients_.begin(); it != this->chClients_.end(); ++it) {
        allClientsPtr_->at(*it).toSend(message.c_str());
    }
}

bool Channel::isOperator(int fd) const {
	return std::find(this->operators_.begin(), this->operators_.end(), fd) != this->operators_.end();
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

bool Channel::hasPassword() const {
    return !this->pwd_.empty();
}

bool Channel::hasUserLimit() const {
    return this->userLimit_ > 0;
}

int Channel::getUserCount() const {
    return this->chClients_.size();
}
