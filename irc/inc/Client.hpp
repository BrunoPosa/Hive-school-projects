#pragma once

#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <cassert>
#include <cstring>//strerror
#include <cerrno>
#include <poll.h>
#include "Socket.hpp"

#define IRC_BUFFER_SIZE 4096
#define IRC_MAX_BUF 16384 //16kb

// #define IRC_BUF_PRINTS //for netcat testing

class Client {
	private:
		Socket		so_;
		pollfd		*pfd_;
		std::string sendBuf_;
		std::string	recvBuf_;
		std::string nick_;
		std::string usrnm_;
		std::string realnm_;
		std::string	delimiter_;
		std::map<std::string, bool> joinedChannels; // Set of channels the client has joined and bool if the client is operator
		bool authenticated;
		bool nickReceived;
		bool userReceived;
		bool passReceived;
		bool modeReceived;
		bool whois; // Whois status
		int	authAttempts_;
		int channelCount_ = 1;
		std::chrono::steady_clock::time_point	lastActive_;

		void	resolveDelimiter();
		
	public:
		Client();	//def. constructor on creation makes a new socket
		Client(Socket&& so, pollfd *pfd); //constructor ties the new client instance to an existing socket
		Client(const Client& other)				= delete; //because sockets are unique and close on destruction (each client owns one) - we disallow copies
		Client& operator=(const Client& other)	= delete;
		Client(Client&& other) noexcept;				
		Client&	operator=(Client&& other) noexcept; 	
		~Client()								= default;

		//I/O
		bool		hasDataToSend() const { return !sendBuf_.empty();}
		void		toSend(const std::string& data);
		bool		send();
		bool		receive();
		std::string	getMsgs();
		
		//util
		bool			isInactive(std::chrono::seconds limit) { return (std::chrono::steady_clock::now() - lastActive_) >= limit; }
		std::string&	getDelimiter()		{ return delimiter_; }
		pollfd*		getPfdPtr()				{ return pfd_; }
		void		setPfdPtr(pollfd *pfd)	{ pfd_ = pfd; }

		//identity
		int			getFd() const		{ return this->so_.getFd(); }
		std::string getIP() const		{ return so_.getIpStr(); }
		uint16_t	getPort() const		{ return so_.getPortNum(); }
		std::string	fetchHost()			{ return so_.resolveHost(); }
		std::string	getFullId() const	{ return this->getNick() + "!" + this->getUser() + "@localhost"; }

		//get-set nick/user/mode/pass
		void 	setRealName(std::string& realName)	{ realnm_ = realName; }
		const 	std::string& getNick() const		{ return nick_; }
		void 	setNick(const std::string& nick)	{ nick_ = nick; }
		const 	std::string& getUser() const		{ return usrnm_; }
		void 	setUser(const std::string& user)	{ usrnm_ = user; }
		bool 	hasReceivedNick() const	{ return nickReceived; }
		void 	setNickReceived()		{ nickReceived = true; }
		bool 	hasReceivedUser() const	{ return userReceived; }
		void 	setUserReceived()		{ userReceived = true; }
		bool 	hasReceivedPass() const	{ return passReceived; }
		void 	setPassReceived()		{ passReceived = true; }
		bool 	hasReceivedMode() const	{ return modeReceived; }
		void 	setModeReceived()		{ modeReceived = true; }

		//auth
		bool 	isAuthenticated() const	{ return authenticated; }
		void 	setAuthenticated()		{ authenticated = true; }
		int		getAuthAttempts() const	{ return authAttempts_; }
		void	addAuthAttempt()		{ ++authAttempts_; }

		//channel utils
		const	std::map<std::string, bool>& getJoinedChannels() const { return joinedChannels; }
		int		getChannelCount() const { return channelCount_; }
		void 	joinChannel(const std::string& channel, bool is_operator);
		void 	leaveChannel(const std::string& channel);
		bool 	isInChannel(const std::string& channel);
		bool 	isOperator(const std::string& channel);
		bool 	getOperator(const std::string& channel);
		void 	setOperator(const std::string& channel, bool is_operator);
	};
