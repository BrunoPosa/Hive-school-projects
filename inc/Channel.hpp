#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

#include "Client.hpp"

typedef std::unordered_map<int, Client> clientMap;

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
        clientMap* allClientsPtr_;

    public:
        Channel() = default;
        Channel(const std::string &name, clientMap* ptrToAllClients);
        Channel(const Channel &other);
        Channel &operator=(const Channel &src);
        ~Channel();

        const std::string& getName() const      { return this->name_; }

        const std::string& getTopic() const     { return this->topic_; }
        const std::string& getTopicSetter() const { return this->topicSetter_; }
        bool getTopicRestricted() const         { return this->topicRestrictedToOperators_; }
        std::chrono::system_clock::time_point getTopicSetTime() const { return this->topicSetTime_; }

        const std::string& getPwd() const       { return this->pwd_; }
        bool hasPassword() const                { return !this->pwd_.empty(); }

        std::vector<int>& getChClients()        { return chClients_;}
        bool hasUserLimit() const               { return this->userLimit_ > 0; }
        int  getUserLimit() const               { return this->userLimit_; }
        int  getClientFdByNick(const std::string& nickname, const clientMap& clients) const;
        bool getInviteOnly() const              { return this->inviteOnly_; }
        bool getIsUserInvited(const int& fd) const { return std::find(this->invitedUsers_.begin(), this->invitedUsers_.end(), fd) != this->invitedUsers_.end(); }
        int  getUserCount() const               { return this->chClients_.size(); }
        std::string getModeString() const;
        
        void setPassword(const std::string& newPassword) { this->pwd_ = newPassword; }
        void setUserLimit(int limit)            { this->userLimit_ = limit; }
        
        void removeOperator(int fd);
        bool isOperator(int fd) const { return std::find(this->operators_.begin(), this->operators_.end(), fd) != this->operators_.end(); } 
        void addOperator(int fd);
    
        void removeClient(int fd);
        void addClient(int fd);
        
        void setInviteOnly(bool inviteOnly)     { this->inviteOnly_ = inviteOnly; }
        void removeInvitedUser(const int& client_fd);
        void addInvitedUser(const int& client_fd);

        void setTopicRestrictedToOperators(bool restricted) { this->topicRestrictedToOperators_ = restricted; }
        void setTopic(const std::string& newTopic) { this->topic_ = newTopic; }
        void setTopicSetter(const std::string& setter_nick) { this->topicSetter_ = setter_nick; }
        void setTopicSetTime(const std::chrono::system_clock::time_point& time) { this->topicSetTime_ = time; }
        
        void broadcast(const std::string& message, const std::string& sender_nick, int except_fd);
        void broadcastToAll(const std::string& message); 

        bool isEmpty() const { return (chClients_.empty()); };
};
