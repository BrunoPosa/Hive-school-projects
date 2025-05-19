#pragma once

#include <iostream>
#include <string>
#include <map>
#include "Socket.hpp"

#define IRC_BUFFER_SIZE 1

class Client {
	private:
		Socket		so_;
		pollfd		pfd_;
		std::string sendBuf_;
		std::string	recvBuf_;
		std::string nick_;
		std::string usrnm_;
		std::map<std::string, bool> joinedChannels; // Set of channels the client has joined
		bool authenticated;
		bool nickReceived;
		bool userReceived;
		bool passReceived;
		bool modeReceived;
		bool whois; // Whois status
		
	public:
		Client();	//def. constructor on creation makes a new socket
		Client(Socket&& so, pollfd& pfd); //constructor ties the new client instance to an existing socket
		Client(const Client& other)				= delete; //because sockets are unique and close on destruction (each client owns one) - we disallow copies
		Client& operator=(const Client& other)	= delete;
		Client(Client&& other) noexcept;				//Move constructor
		Client&	operator=(Client&& other) noexcept; 	//Move assignment
		~Client()								= default;
		
		//I/O
		bool	hasDataToSend() const { return !sendBuf_.empty();}
		void	toSend(const std::string& data);
		bool	send();
		bool	receive();

		int		getFd() const	{ return this->so_.getFd(); }
		std::string getIP() const {return so_.getIpStr();}
		std::string	getMsgs();

		bool hasReceivedNick() const { return nickReceived; }
		bool hasReceivedUser() const { return userReceived; }
		bool hasReceivedPass() const { return passReceived; }
		bool hasReceivedMode() const { return modeReceived; }
		bool isAuthenticated() const { return authenticated; }

		const std::string& getNick() const { return nick_; }
		const std::string& getUser() const { return usrnm_; }

		void setNick(const std::string& nick) { nick_ = nick; }
		void setUser(const std::string& user) { usrnm_ = user; }

		void setNickReceived() { nickReceived = true; }
		void setUserReceived() { userReceived = true; }
		void setPassReceived() { passReceived = true; }
		void setModeReceived() { modeReceived = true; }
		void setAuthenticated() { authenticated = true; }

		const std::map<std::string, bool>& getJoinedChannels() const { return joinedChannels; }
		void joinChannel(const std::string& channel, bool is_operator);
		void leaveChannel(const std::string& channel);
		bool isInChannel(const std::string& channel);

		bool isOperator(const std::string& channel);
		bool getOperator(const std::string& channel);
		void setOperator(const std::string& channel, bool is_operator);
	};
