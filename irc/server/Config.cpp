#include "Config.hpp"

Config::Config() : listenPort_{"6667"}, password_{"42"} {}

Config::Config(std::string& port, std::string& passw) : listenPort_{port}, password_{passw} {}

void	Config::validate() {
	if (!isValidPort(listenPort_)) {
		throw std::invalid_argument("Invalid port number. Port must be between 1024 and 65535.");
	}
	if (!isValidPassword(password_)) {
		throw std::invalid_argument("Invalid password. Password must be alphanumeric and cannot be empty.");
	}
}

bool isValidPort(std::string_view portStr) {
	if (portStr.at(0) == '0') {
		return false; // Port cannot start with '0'
	}
	if (portStr.find_first_not_of("0123456789") != std::string::npos) {
		return false; // Not a valid integer
	}    
	try {
		int port = std::stoi(portStr.); // Convert string to int
		return (port >= 1024 && port <= 65535); // Check if port is in valid range
	} catch (const std::invalid_argument& e) {
		return false; // Not a valid integer
	} catch (const std::out_of_range& e) {
		return false; // Out of range for int
	} catch (...) {
		return false; // Catch any other exceptions
	}
}
bool isValidPassword(const std::string& password) {

	if (password.empty() || password.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos) {
		return false;
	}
	return true;
}