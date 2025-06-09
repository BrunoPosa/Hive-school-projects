#include "../../inc/Server.hpp"

void Server::cmdJoin(int fd, const t_data data) {
	std::istringstream iss(data.fullMsg);
	std::string command, channelList, keyList;
	iss >> command >> channelList >> keyList;

	if (channelList.empty()) {
		ft_send(fd, ERR_NEEDMOREPARAMS(clients_[fd].getNick(), command));
		return;
	}

	std::istringstream chStream(channelList);
	std::istringstream keyStream(keyList);
	std::string channel, key;

	while (std::getline(chStream, channel, ',')) {
		std::getline(keyStream, key, ','); // will be empty if not enough keys

		if (clients_[fd].isInChannel(channel)) {
			ft_send(fd, ERR_USERONCHANNEL(clients_[fd].getNick(),channel));
			continue;
		}

		Channel* chanPtr = nullptr;

		// Check invite-only and other conditions *before* creating channel
		if (channels_.find(channel) != channels_.end()) {
			chanPtr = &channels_[channel];
			
			if (chanPtr->getInviteOnly() && !chanPtr->getIsUserInvited(fd)) {
				ft_send(fd, ERR_INVITEONLYCHAN(clients_[fd].getNick(), channel));
				continue;
			}

			if (chanPtr->hasPassword()) {
				if (key.empty() || key != chanPtr->getPwd()) {
					ft_send(fd, ERR_BADCHANNELKEY(clients_[fd].getNick(), channel));
					return;
				}
			}

			if (chanPtr->hasUserLimit() && chanPtr->getUserCount() >= chanPtr->getUserLimit()) {
				ft_send(fd, ERR_CHANNELISFULL(clients_[fd].getNick(),channel));
				return;
			}
		}

		// All checks passed, now create the channel if it doesn't exist
		if (chanPtr == nullptr) {
			channels_[channel] = Channel(channel, &clients_);
			chanPtr = &channels_[channel];
			chanPtr->addOperator(fd);
			std::cerr << "Created channel and added operator: " << channel << std::endl;
		}

		// All checks passed
		clients_[fd].joinChannel(channel, false);
		chanPtr->addClient(fd);


		std::string prefix = ":" + clients_[fd].getNick() + "!" + clients_[fd].getUser() + "@localhost";
		std::string joinMsg = prefix + " JOIN :" + channel + "\r\n";
		chanPtr->broadcast(joinMsg, clients_[fd].getNick(), -1);

		clients_[fd].toSend(IrcMessages::RPL_NAMREPLY(clients_[fd].getNick(), chanPtr, &clients_) +
		                    IrcMessages::RPL_ENDOFNAMES(clients_[fd].getNick(), chanPtr));
		if (!chanPtr->getTopic().empty()) {
			// Send the numeric (optional, mostly for logging or completeness)
			ft_send(fd, RPL_TOPIC(clients_[fd].getNick(), channel, chanPtr->getTopic()));
			
			// Also send a standard message to trigger display in the channel window
			// std::string topicMsg = ":" + clients_[fd].getFullId() + " TOPIC " + channel + " :" + chanPtr->getTopic() + "\r\n";
			// ft_send(fd, topicMsg);
		} else {
			ft_send(fd, RPL_NOTOPIC(clients_[fd].getNick(), channel));
		}
	}
}
