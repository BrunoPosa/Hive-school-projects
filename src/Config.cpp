#include "../inc/Config.hpp"

Config::Config() : port_{6667}, password_{"4242"} {}

Config::Config(std::string port, std::string passw) : port_{-1}, portStr_{port}, password_{passw} {
	validate_();
	port_ = std::stoi(portStr_);
}

Config::Config(Config&& other) noexcept
:	port_(std::exchange(other.port_, -1)),
	portStr_(std::move(other.portStr_)),
	password_(std::move(other.password_)) {}

Config& Config::operator=(Config&& other) noexcept {
	if (this != &other) {
		port_ = std::exchange(other.port_, -1);
		portStr_ = std::move(other.portStr_);
		password_ = std::move(other.password_);
		other.portStr_.clear();
		other.password_.clear();
	}
	return *this;
}

void	Config::validate_() {
	if (!isValidPort_()) {
		throw std::invalid_argument("Invalid port number. Port must be between 1024 and 65535 "
									"(but check /etc/services for unavailable ones)");
	}
	if (!isValidPassword_()) {
		std::string	errmsg("Invalid password. Special chars allowed:" + allowedPassChars_.substr(62) + " and min pass length is " + std::to_string(minPassLen_));
		throw std::invalid_argument(errmsg);
	}
}

bool Config::isValidPort_() {
	if (portStr_.empty() || portStr_.at(0) == '0') {
		return false;
	}
	if (portStr_.find_first_not_of("0123456789") != std::string::npos) {
		return false;
	}
	try {
		int port = std::stoi(portStr_.data());
		return (port >= 1024 && port <= 65535);
	} catch (std::exception&) {
		return false;
	}
}

bool Config::isValidPassword_() {
	if (password_.empty()) {
		return false;
	}
	if (password_.find_first_not_of(allowedPassChars_) != std::string::npos) {
		return false;
	}
	if (password_.length() < minPassLen_ || password_.length() > maxPassLen_) {
		return false;
	}
	return true;
}
