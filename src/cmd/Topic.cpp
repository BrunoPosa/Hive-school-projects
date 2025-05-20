#include "../../inc/irc.hpp"

void Server::cmdTopic(int fd, const std::string& message) {
    std::istringstream iss(message);
    std::string command, channel;
    iss >> command >> channel;

    std::string topic;
    std::getline(iss, topic); // gets the rest of the line

    // Debugging output
    std::cerr << "Debug message: " << message << std::endl;
    std::cerr << "Debug command: " << command << std::endl;
    std::cerr << "Debug channel: " << channel << std::endl;
    std::cerr << "Raw topic string: " << topic << std::endl;

    if (channel.empty()) {
        ft_send(fd, ERR_NEEDMOREPARAMS);
        return;
    }

    Client &client = clients_[fd];

    if (channels_.find(channel) == channels_.end()) {
        ft_send(fd, ERR_NO_SUCH_CHANNEL(channel));
        return;
    }

    Channel &ch = channels_[channel];

    if (!client.isInChannel(channel)) {
        ft_send(fd, ERR_NOT_IN_CHANNEL(channel));
        return;
    }

    // Clean topic string
    if (!topic.empty()) {
        if (topic[0] == ' ') topic = topic.substr(1);      // strip leading space
        if (!topic.empty() && topic[0] == ':') topic = topic.substr(1); // strip leading colon
    }

    if (topic.empty()) {
        // Viewing topic
        if (ch.getTopic().empty())
            ft_send(fd, RPL_NOTOPIC(client.getNick(), channel));
        else
            ft_send(fd, RPL_TOPIC(client.getNick(), channel, ch.getTopic()));
    } else {
        // Setting topic
        std::cerr << "gettopicrestricted: " << ch.getTopicRestricted() << std::endl;
        std::cerr << "isoperator: " << client.isOperator(channel) << std::endl;
        if (ch.getTopicRestricted() && !client.isOperator(channel)) {
            ft_send(fd, ERR_CHANOPRIVSNEEDED(channel));
            return;
        }

        ch.setTopic(topic);
        std::string broadcast = ":" + client.getNick() + " TOPIC " + channel + " :" + topic + "\r\n";
        ch.broadcastToAll(broadcast);
        std::cerr << "Set topic to: " << topic << std::endl;
    }
}
