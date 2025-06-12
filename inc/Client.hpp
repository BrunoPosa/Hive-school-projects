#pragma once

#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <cassert>
#include "Socket.hpp"

#define IRC_BUFFER_SIZE 512
#define IRC_MAX_BUF 64000

class Client {
	private:
		Socket		so_;
		pollfd		*pfd_;
		std::string sendBuf_;
		std::string	recvBuf_;
		std::string nick_;
		std::string usrnm_;
		std::string realnm_;
		std::string	hostnm_;
		std::string	msgDelimiter_;
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
		
	public:
		Client();	//def. constructor on creation makes a new socket
		Client(Socket&& so, pollfd *pfd, std::string delimiter, std::string hostname); //constructor ties the new client instance to an existing socket
		Client(const Client& other)				= delete; //because sockets are unique and close on destruction (each client owns one) - we disallow copies
		Client& operator=(const Client& other)	= delete;
		Client(Client&& other) noexcept;				
		Client&	operator=(Client&& other) noexcept; 	
		~Client()								= default;
	
		//I/O
		bool	hasDataToSend() const { return !sendBuf_.empty();}
		void	toSend(const std::string& data);
		bool	send();
		bool	receive();

		int		getFd() const	{ return this->so_.getFd(); }
		std::string getIP() const {return so_.getIpStr();}
		uint16_t	getPort() const { return so_.getPortNum(); }
		std::string	getMsgs();
		std::string getFullId() const; 
		int	getAuthAttempts() const { return authAttempts_; }
		int getChannelCount () const { return channelCount_; }
		void addAuthAttempt() { ++authAttempts_; }
		std::string	getDelimiter() const { return msgDelimiter_; }

		bool	isInactive(std::chrono::seconds limit) { return (std::chrono::steady_clock::now() - lastActive_) >= limit; }
		bool 	isAuthenticated() const { return authenticated; }
		bool 	hasReceivedNick() const { return nickReceived; }
		bool 	hasReceivedUser() const { return userReceived; }
		bool 	hasReceivedPass() const { return passReceived; }
		bool 	hasReceivedMode() const { return modeReceived; }

		const 	std::string& getNick() const { return nick_; }
		const 	std::string& getUser() const { return usrnm_; }

		void	setPfdPtr(pollfd *pfd) { pfd_ = pfd; }
		pollfd*	getPfdPtr() { return pfd_; }
		void 	setNick(const std::string& nick) { nick_ = nick; }
		void 	setUser(const std::string& user) { usrnm_ = user; }
		void	setHostName(std::string hostnm) { hostnm_ = hostnm; }
		void 	setRealName(std::string& realName) { realnm_ = realName; }

		void 	setNickReceived() { nickReceived = true; }
		void 	setUserReceived() { userReceived = true; }
		void 	setPassReceived() { passReceived = true; }
		void 	setModeReceived() { modeReceived = true; }
		void 	setAuthenticated() { authenticated = true; }

		const 	std::map<std::string, bool>& getJoinedChannels() const { return joinedChannels; }
		void 	joinChannel(const std::string& channel, bool is_operator);
		void 	leaveChannel(const std::string& channel);
		bool 	isInChannel(const std::string& channel);

		bool 	isOperator(const std::string& channel);
		bool 	getOperator(const std::string& channel);
		void 	setOperator(const std::string& channel, bool is_operator);
	};
