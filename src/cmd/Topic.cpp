#include "../../inc/Server.hpp"

void Server::cmdTopic(int fd, const t_data data) {
    std::istringstream iss(data.fullMsg);
    std::string command, channel;
    iss >> command >> channel;

    std::string topic;
    std::getline(iss, topic);

    // Debugging output
    std::cerr << "Debug message: " << data.fullMsg << std::endl;
    std::cerr << "Debug command: " << command << std::endl;
    std::cerr << "Debug channel: " << channel << std::endl;
    std::cerr << "Raw topic string: " << topic << std::endl;

    if (channel.empty()) {
        ft_send(fd, ERR_NEEDMOREPARAMS(clients_[fd].getNick(), command));
        return;
    }

    Client &client = clients_[fd];

    if (channels_.find(channel) == channels_.end()) {
        ft_send(fd, ERR_NOSUCHCHANNEL(client.getNick(), channel));
        return;
    }

    Channel &ch = channels_[channel];

    if (!client.isInChannel(channel)) {
        ft_send(fd, ERR_NOTONCHANNEL(client.getNick(), channel));
        return;
    }

    // Clean topic string
    if (!topic.empty()) {
        if (topic[0] == ' ') topic = topic.substr(1);
        if (!topic.empty() && topic[0] == ':') topic = topic.substr(1);
    }

    if (topic.empty()) {
        // Viewing topic
        if (ch.getTopic().empty())
            ft_send(fd, RPL_NOTOPIC(client.getNick(), channel));
        else
        {
            ft_send(fd, RPL_TOPIC(client.getNick(), channel, ch.getTopic()));

            std::time_t topicSetTime = std::chrono::system_clock::to_time_t(ch.getTopicSetTime());
            ft_send(fd, RPL_TOPICWHOTIME(client.getNick(), channel, ch.getTopicSetter(), std::to_string(topicSetTime)));
        }


    } else {
        // Setting topic
        std::cerr << "gettopicrestricted: " << ch.getTopicRestricted() << std::endl;
        std::cerr << "isoperator: " << ch.isOperator(fd) << std::endl;
        if (ch.getTopicRestricted() && !ch.isOperator(fd)) {
            ft_send(fd, ERR_CHANOPRIVSNEEDED(client.getNick() ,channel));
            return;
        }

        ch.setTopic(topic);
        std::string broadcast = ":" + client.getNick() + " TOPIC " + channel + " :" + topic + "\r\n";
        ch.broadcastToAll(broadcast);
        std::cerr << "Set topic to: " << topic << std::endl;
    }
}
