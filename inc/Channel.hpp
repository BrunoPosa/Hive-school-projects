#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "Client.hpp"

class Channel
{
    private:
        std::string name_;
        std::string topic_;
        std::string pwd_;
        std::vector<int> invitedUsers_;
        std::vector<int> chClients_; // List of client file descriptors in the channel
        
        std::string topicSetter_; // Nickname of the user who set the topic
        std::chrono::system_clock::time_point topicSetTime_; // Time when the topic was set
        std::vector<int> operators_; // List of operator file descriptors in the channel
        int userLimit_;
        bool inviteOnly_; // i
        bool topicRestrictedToOperators_;  // t
        bool hasPassword_; // k
        bool hasUserLimit_; // l
        std::map<int, Client>* allClientsPtr_;

    public:
        Channel() = default;
        Channel(std::map<int, Client>* ptrToAllClients);
        Channel(const std::string &name, std::map<int, Client>* ptrToAllClients);
        Channel(const Channel &other);
        ~Channel();

        Channel &operator=(const Channel &src);

        const std::string& getName() const;
        const std::string& getTopic() const;
        const std::string& getPwd() const;
        std::vector<int> getChClients() const {return chClients_;}
        int  getUserLimit() const;
        int  getClientFdByNick(const std::string& nickname, const std::map<int, Client>& clients) const;
        bool getIsUserInvited(const int& fd) const;
        const std::string& getTopicSetter() const; // Get the nickname of the user who set the topic
        std::chrono::system_clock::time_point getTopicSetTime() const; // Get the time when the topic was set
        bool isOperator(int fd) const; // Check if a client is an operator in the channel
        bool hasClient(int fd) const; // Check if a client is in the channel

        std::string getModeString() const;
        // Channel.hpp

        bool getTopicRestricted() const;
        bool getInviteOnly() const;
        bool hasPassword() const; // returns true if password is set
        bool hasUserLimit() const;     // returns true if +l is set
        
        int  getUserCount() const;      // current number of clients

        void addOperator(int fd); // Add a client as an operator in the channel
        void removeOperator(int fd); // Remove a client as an operator in the channel
        void setPassword(const std::string& newPassword);    
        void setUserLimit(int limit);
        void setInviteOnly(bool inviteOnly);
        void setTopicRestrictedToOperators(bool restricted);
        void addInvitedUser(const int& client_fd);
        void removeInvitedUser(const int& client_fd);
        void setTopic(const std::string& newTopic);
        void setTopicSetter(const std::string& setter_nick); // Set the nickname of the user who set the topic
        void setTopicSetTime(const std::chrono::system_clock::time_point& time); // Set the time when the topic was set
        void addClient(int fd);
        void removeClient(int fd);
        void broadcast(const std::string& message, const std::string& sender_nick, int except_fd);
        bool isEmpty() const { return (chClients_.empty()); };
        void broadcastToAll(const std::string& message); // Send a message to all clients in the channel including the sender
};
