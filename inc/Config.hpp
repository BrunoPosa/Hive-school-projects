#pragma once

#include <string>
#include <utility>//std::exchange, move
#include <chrono>
#include <stdexcept>

class Config {
	int					port_;
	std::string			portStr_;
	std::string			password_;
	const std::string	serverName_{"ft_irc, WB edition ®"};
	const std::string	allowedPassChars_{//validate_() needs '-' in this string as delimiter for printing special chars
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_!?#"
	};
	static constexpr unsigned int	maxAuthAttempts_{10};
	static constexpr unsigned int	minPassLen_{4};
	static constexpr unsigned int	maxPassLen_{400};
	static constexpr std::chrono::seconds	allowedInactivity_{300};

	void	validate_();
	bool	isValidPort_();
	
	public:
	Config();
	Config(std::string listenPort, std::string passw);
	Config(const Config&)				= delete;
	Config&	operator=(const Config&)	= delete;
	Config(Config&&) noexcept;
	Config&	operator=(Config&& other) noexcept;
	~Config()							= default;
	
	int					getPort() const noexcept {return port_;}
	const std::string&	getServName() const noexcept {return serverName_;}
	int					getMaxAuthAttempts() const noexcept {return maxAuthAttempts_;}
	unsigned short		getMinPassLen() const noexcept {return minPassLen_;}
	const std::string&	getAllowPassChars()	const noexcept {return allowedPassChars_;}
	bool				CheckPassword(const std::string& input) const noexcept {return input == password_;}
	std::chrono::seconds	getAllowedInactivity() { return allowedInactivity_; }
	bool				isValidPassword_(std::string pass);
};
