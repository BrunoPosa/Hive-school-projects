#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

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

        const std::string& getName() const      { return this->name_; }
        const std::string& getTopic() const     { return this->topic_; }
        const std::string& getPwd() const       { return this->pwd_; }
        std::vector<int> getChClients() const   {return chClients_;}
        int  getUserLimit() const               { return this->userLimit_; }
        int  getClientFdByNick(const std::string& nickname, const std::map<int, Client>& clients) const;
        bool getIsUserInvited(const int& fd) const { return std::find(this->invitedUsers_.begin(), this->invitedUsers_.end(), fd) != this->invitedUsers_.end(); }
        const std::string& getTopicSetter() const { return this->topicSetter_; } // Gets nick of user who set the topic
        std::chrono::system_clock::time_point getTopicSetTime() const { return this->topicSetTime_; } // Get the time when the topic was set
        bool isOperator(int fd) const { return std::find(this->operators_.begin(), this->operators_.end(), fd) != this->operators_.end(); } // Check if a client is an operator in the channel
        bool hasClient(int fd) const            { return std::find(chClients_.begin(), chClients_.end(), fd) != chClients_.end(); } // Check if a client is in the channel

        std::string getModeString() const;

        bool getTopicRestricted() const         { return this->topicRestrictedToOperators_; }
        bool getInviteOnly() const              { return this->inviteOnly_; }
        bool hasPassword() const                { return !this->pwd_.empty(); } // returns true if password is set
        bool hasUserLimit() const               { return this->userLimit_ > 0; } // returns true if +l is set
        
        int  getUserCount() const               { return this->chClients_.size(); } // current number of clients

        void addOperator(int fd); // Add a client as an operator in the channel
        void removeOperator(int fd); // Remove a client as an operator in the channel
        void setPassword(const std::string& newPassword) { this->pwd_ = newPassword; }
        void setUserLimit(int limit)            { this->userLimit_ = limit; }
        void setInviteOnly(bool inviteOnly)     { this->inviteOnly_ = inviteOnly; }
        void setTopicRestrictedToOperators(bool restricted) { this->topicRestrictedToOperators_ = restricted; }
        void addInvitedUser(const int& client_fd);
        void removeInvitedUser(const int& client_fd);
        void setTopic(const std::string& newTopic) { this->topic_ = newTopic; }
        void setTopicSetter(const std::string& setter_nick) { this->topicSetter_ = setter_nick; } // Set the nickname of the user who set the topic
        void setTopicSetTime(const std::chrono::system_clock::time_point& time) { this->topicSetTime_ = time; } // Set the time when the topic was set
        void addClient(int fd);
        void removeClient(int fd);
        void broadcast(const std::string& message, const std::string& sender_nick, int except_fd);
        void broadcastToAll(const std::string& message); // Send a message to all clients in the channel including the sender
        bool isEmpty() const { return (chClients_.empty()); };
};
