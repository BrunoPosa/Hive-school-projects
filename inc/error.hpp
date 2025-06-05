#pragma once

// class Server; // forward declare
#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

// Common error
#define ERR_NOT_IN_CHANNEL(chan) (":localhost 442 " + chan + " :You're not on that channel\r\n")
#define ERR_NO_SUCH_CHANNEL(chan) (":localhost 403 " + chan + " :No such channel\r\n")
#define ERR_CHANOPRIVSNEEDED(chan) (":localhost 482 " + chan + " :You're not channel operator\r\n")
#define ERR_NOT_IN_CHANNEL(chan) (":localhost 442 " + chan + " :You're not on that channel\r\n")

// NICK
#define ERR_NO_NICKNAME(nick) (":localhost 431 " + nick + " :No nickname given\r\n")
#define ERR_NICK_IN_USE(nick) (":localhost 433 " + nick + " :Nickname is already in use\r\n")
#define RPL_WELCOME(nick)     (":localhost 001 " + nick + " :Welcome to the server\r\n")

// JOIN
#define ERR_NEEDMOREPARAMS ":localhost 461 JOIN :Not enough parameters\r\n"
#define ERR_USERONCHANNEL(chan) (":localhost 443 " + chan + " :You are already on that channel\r\n")
#define ERR_BADCHANNELKEY(chan) (":localhost 475 " + chan + " :Cannot join channel (+k)\r\n")
#define ERR_CHANNELISFULL(chan) (":localhost 471 " + chan + " :Cannot join channel (+l)\r\n")
#define ERR_INVITEONLYCHAN(chan) (":localhost 473 " + chan + " :Cannot join channel (+i)\r\n")

// PRIVMSG
#define ERR_NO_RECIPIENT ":localhost 411 :No recipient given\r\n"
#define ERR_NO_TEXT_TO_SEND ":localhost 412 :No text to send\r\n"


// USER
#define ERR_NOT_ENOUGH_PARAMS ":localhost 461 USER :Not enough parameters\r\n"
#define ERR_ALREADY_REGISTERED ":localhost 462 USER :You may not reregister\r\n"
#define WELCOME_MSG(user) (":localhost 001 " + user + " :Welcome to the server\r\n")

// PING
#define ERR_NO_PING_TARGET ":localhost 409 :No target for PING\r\n"

// TOPIC
#define RPL_NOTOPIC(nick, chan) (":localhost 331 " + nick + " " + chan + " :No topic is set\r\n")
#define RPL_TOPIC(nick, chan, topic) (":localhost 332 " + nick + " " + chan + " :" + topic + "\r\n")

// MODE
#define ERR_UNKNOWNMODE(mode) (":localhost 472 " + mode + " :is unknown mode char to me\r\n")
#define ERR_NO_PRIVILEGES ":localhost 481 :Permission Denied- You're not an IRC operator\r\n"
#define ERR_NOTREGISTERED ":localhost 451 :You have not registered\r\n"
#define ERR_NOSUCHNICK(nick) (":localhost 401 " + nick + " :No such nick/channel\r\n")

// KICK
#define ERR_USERNOTINCHANNEL(nick, chan) (":localhost 441 " + nick + " " + chan + " :They aren't on that channel\r\n")
#define RPL_MODESET(chan, mode) (":localhost 324 " + chan + " " + mode + "\r\n")

#define RPL_INVITING(senderNick, targetNick, channel) (":localhost 341 " + senderNick + " " + targetNick + " " + channel + "\r\n")

//Idk if macros or inline functions are better
namespace IrcMessages {

	inline std::string	askPass(std::string nick) {
		return (":localhost NOTICE " + nick + " :Enter password in format '/quote PASS <password>'\r\n");
	}

	inline std::string	wrongPass() {
		return ("ERROR :Incorrect password.\r\n");
	}

	inline std::string	attemptsLeft(int attempts, std::string nick) {
		return (":localhost NOTICE " + nick + " :Attempts left: " + std::to_string(attempts) + "\r\n");
	}

	inline std::string	disconnect() {
		return ("ERROR :Too many attempts. Connection closed.\r\n");
	}

	inline std::string	welcome(const std::string& nick, const std::string& servName) {
		return (":localhost 001 " + nick + " :Welcome to the " + servName + " Internet Relay Network\r\n"
			":localhost 002 " + nick + " :Your host is localhost\r\n"
			":localhost 003 " + nick + " :This server was created today\r\n"
			":localhost 004 " + nick + " :localhost 1.0\r\n");
	}

	inline std::string	motd() {
		return (":localhost 375 * :- Message of the Day -\r\n"
				":localhost 376 * :Another day another slay\r\n");
	}

	inline std::string	quit() {
		return ("QUIT :You have been disconnected by the server.\r\n");
	}

	inline std::string	clientQuit(const Client& client) {
		return (":" + client.getNick() + "!~" + client.getUser() + "@" + client.getIP() + " QUIT :Client Quit\r\n");
	}

	inline std::string	RPL_NAMREPLY(const std::string& nick, Channel *ch, std::map<int, Client> *allClientsPtr) {
		std::string	msg = ":localhost 353 " + nick + " @ " + ch->getName() + " :";//should these messages be :localhost or name of the server?
 
		std::vector	chClients = ch->getChClients();
		for (int i = chClients.size() - 1; i >= 0; i--) {
			msg += allClientsPtr->at(chClients[i]).getNick() + " ";
		}
		msg += "\r\n";
		return (msg);
	}

	inline std::string RPL_ENDOFNAMES(const std::string& nick, Channel *ch) {
		return (":localhost 366 " + nick + " " + ch->getName() + " :End of /NAMES list.\r\n");
	}
}
