#include "../../inc/Server.hpp"

void Server::cmdInvite(int sender_fd, const t_data data) {
	std::vector<std::string> params = data.cmdParams;
	if (params.size() < 2) {
		ft_send(sender_fd, ERR_NEEDMOREPARAMS(clients_[sender_fd].getNick(), params[0]));
		return;
	}

	const std::string& targetNick = params[0];
	const std::string& channelName = params[1];

	// Check if target client exists
	int target_fd = getClientFdByNick(targetNick);
	if (target_fd == -1) {
		ft_send(sender_fd, ERR_NOSUCHNICK(targetNick, channelName));
		return;
	}

	Client& sender = clients_[sender_fd];
	// Check if channel exists
	if (channels_.find(channelName) == channels_.end()) {
		ft_send(sender_fd, ERR_NOSUCHCHANNEL(sender.getNick(), channelName));
		return;
	}

	Channel& channel = channels_[channelName];

	// Check if sender is in the channel
	if (!sender.isInChannel(channelName)) {
		std::cerr << "user is in channel\n";
		ft_send(sender_fd, (channelName));
		return;
	}

	// Check if sender is a channel operator (for invite-only channels)
	if (channel.getInviteOnly() && !channel.isOperator(sender_fd)) {
		ft_send(sender_fd, ERR_CHANOPRIVSNEEDED(clients_[sender_fd].getNick(), channelName));
		return;
	}

	// Check if target is already on the channel
	if (clients_[target_fd].isInChannel(channelName)) {
		ft_send(sender_fd, ERR_USERONCHANNEL(targetNick, channelName));
		return;
	}

	// Add to invite list
	channel.addInvitedUser(target_fd);

	// Notify sender that the invite was sent
	ft_send(sender_fd, RPL_INVITING(sender.getNick(), targetNick, channelName));

	// Send invite to the target client
	std::string inviteMsg = ":" + sender.getNick() + " INVITE " + targetNick + " :" + channelName + "\r\n";
	ft_send(target_fd, inviteMsg);
}

