#pragma once

// class Server; // forward declare
#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

// 001 - RPL_WELCOME
#define RPL_WELCOME(nick) (":localhost 001 " + nick + " :Welcome to the server\r\n")
#define WELCOME_MSG(user) (":localhost 001 " + user + " :Welcome to the server\r\n")
// 315 - RPL_ENDOFWHO
#define RPL_ENDOFWHO(nick, chan) (":localhost 315 " + nick + " " + chan + " :End of /WHO list\r\n")
// 331 - RPL_NOTOPIC
#define RPL_NOTOPIC(nick, chan) (":localhost 332 " + nick + " " + chan + " :No topic is set\r\n")
// 332 - RPL_TOPIC
#define RPL_TOPIC(nick, chan, topic) (":localhost 332 " + nick + " " + chan + " :" + topic + "\r\n")
// 333 - RPL_ROPICWHOTIME
#define RPL_TOPICWHOTIME(nick, chan, setter, timestamp) \
	(":localhost 333 " + nick + " " + chan + " " + setter + " " + timestamp + "\r\n")
// 341 - RPL_INVITING
#define RPL_INVITING(senderNick, targetNick, channel) (":localhost 341 " + senderNick + " " + targetNick + " " + channel + "\r\n")
// 324 - RPL_MODESET
#define RPL_MODESET(nick, chan, mode) (":localhost 324 " + nick + " " + chan + " " + mode + "\r\n")
#define RPL_CHANNELMODEIS(nick, chan, modes, params) \
	(":localhost 324 " + nick + " " + chan + " " + modes + params + "\r\n")

// 401 - ERR_NOSUCHNICK
#define ERR_NOSUCHNICK(nick) (":localhost 401 " + nick + " :No such nick/channel\r\n")
// 404 - ERR_CANNOTSENDTOCHAN
#define ERR_CANNOTSENDTOCHAN(nick, chan) (":localhost 404 " + nick + " " + chan + " :Cannot send to channel\r\n")
// 403 - ERR_NOSUCHCHANNEL
#define ERR_NOSUCHCHANNEL(nick, chan) (":localhost 403 " + nick + " " + chan + " :No such channel\r\n")
// 409 - ERR_NO_PING_TARGET
#define ERR_NOORIGIN ":localhost 409 * :No origin specified\r\n"
// 411 - ERR_NORECIPIENT
#define ERR_NORECIPIENT ":localhost 411 :No recipient given\r\n"
// 412 - ERR_NOTEXTTOSEND
#define ERR_NOTEXTTOSEND ":localhost 412 :No text to send\r\n"
// 431 - ERR_NO_NICKNAME
#define ERR_NO_NICKNAME(nick) (":localhost 431 " + nick + " :No nickname given\r\n")
// 432 - ERR_ERRONONEOUS_NICKNAME
#define ERR_ERRONEOUS_NICKNAME(nick) (":localhost 432 " + nick + " :Erroneous nickname\r\n")
// 433 - ERR_NICK_IN_USE
#define ERR_NICK_IN_USE(nick) (":localhost 433 " + nick + " :Nickname is already in use\r\n")
// 441 - ERR_USERNOTINCHANNEL
#define ERR_USERNOTINCHANNEL(nick, chan) (":localhost 441 " + nick + " " + chan + " :They aren't on that channel\r\n")
// 442 - ERR_NOTONCHANNEL
#define ERR_NOTONCHANNEL(nick, chan) (":localhost 442 " + nick + " " + chan + " :You're not on that channel\r\n")
// 443 - ERR_USERONCHANNEL
#define ERR_USERONCHANNEL(nick, chan) (":localhost 443 " + nick + " " + chan + " :You are already on that channel\r\n")
// 461 - ERR_NEEDMOREPARAMS / ERR_NOT_ENOUGH_PARAMS
#define ERR_NEEDMOREPARAMS(nick, cmd) (":localhost 461 " + nick + " " + cmd + " :Not enough parameters\r\n")
#define ERR_NOT_ENOUGH_PARAMS ":localhost 461 USER :Not enough parameters\r\n"
// 462 - ERR_ALREADY_REGISTERED
#define ERR_ALREADYREGISTERED ":localhost 462 USER :You may not reregister\r\n"
// 471 - ERR_CHANNELISFULL
#define ERR_CHANNELISFULL(nick, chan) (":localhost 471 " + nick + " " + chan + " :Cannot join channel (+l)\r\n")
// 472 - ERR_UNKNOWNMODE
#define ERR_UNKNOWNMODE(mode) (":localhost 472 " + mode + " :is unknown mode char to me\r\n")
// 473 - ERR_INVITEONLYCHAN
#define ERR_INVITEONLYCHAN(nick, chan) (":localhost 473 " + nick + " " + chan + " :Cannot join channel (+i)\r\n")
// 475 - ERR_BADCHANNELKEY
#define ERR_BADCHANNELKEY(nick, chan) (":localhost 475 " + nick + " " + chan + " :Cannot join channel (+k)\r\n")
// 481 - ERR_NO_PRIVILEGES
#define ERR_NO_PRIVILEGES ":localhost 481 :Permission Denied- You're not an IRC operator\r\n"
// 482 - ERR_CHANOPRIVSNEEDED
#define ERR_CHANOPRIVSNEEDED(nick, chan) (":localhost 482 " + nick + " " + chan + " :You're not channel operator\r\n")
// 451 - ERR_NOTREGISTERED
#define ERR_NOTREGISTERED ":localhost 451 :You have not registered\r\n"


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

	// inline std::string	RPL_NAMREPLY(const std::string& nick, Channel *ch, std::map<int, Client> *allClientsPtr) {
	// 	std::string	msg = ":localhost 353 " + nick + " @ " + ch->getName() + " :";//should these messages be :localhost or name of the server?
 
	// 	std::vector	chClients = ch->getChClients();
	// 	for (int i = chClients.size() - 1; i >= 0; i--) {
	// 		msg += allClientsPtr->at(chClients[i]).getNick() + " ";
	// 	}
	// 	msg += "\r\n";
	// 	return (msg);
	// }

	inline std::string RPL_NAMREPLY(const std::string& nick, Channel *ch, std::map<int, Client> *allClientsPtr) {
		std::string msg = ":localhost 353 " + nick + " = " + ch->getName() + " :";

		std::vector<int> chClients = ch->getChClients();
		for (int i = 0; i < (int)chClients.size(); i++) {
			int clientFd = chClients[i];
			std::string clientNick = allClientsPtr->at(clientFd).getNick();

			// Check if the client is an operator in this channel
			if (ch->isOperator(clientFd)) {
				msg += "@";
				std::cerr << "found op" << std::endl;
			}
			msg += clientNick + " ";
		}
		msg += "\r\n";
		return msg;
	}

	inline std::string RPL_ENDOFNAMES(const std::string& nick, Channel *ch) {
		return (":localhost 366 " + nick + " " + ch->getName() + " :End of /NAMES list.\r\n");
	}
}
