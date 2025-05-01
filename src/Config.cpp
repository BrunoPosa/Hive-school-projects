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
		throw std::invalid_argument("Invalid password. Password cannot be empty and must be made of: "
									+ allowedPassChars_);
	}
}

bool Config::isValidPort_() {
	if (portStr_.empty() || portStr_.at(0) == '0') {
		return false; // Port cannot start with '0'
	}
	if (portStr_.find_first_not_of("0123456789") != std::string::npos) {
		return false; // Not a valid integer
	}
	try {
		int port = std::stoi(portStr_.data()); // Convert string to int
		return (port >= 1024 && port <= 65535); // Check if port is in valid range
	} catch (const std::invalid_argument& e) {
		return false; // Not a valid integer
	} catch (const std::out_of_range& e) {
		return false; // Out of range for int
	} catch (std::exception&) {
		return false; // Catch any other exceptions
	}
}

bool Config::isValidPassword_() {
	if (password_.empty() || password_.find_first_not_of(allowedPassChars_) != std::string::npos) {
		return false;
	}
    if (password_.length() < minPassLen_) {
        return false;
    }
	return true;
}
