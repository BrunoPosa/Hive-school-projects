
#ifndef CONFIG_HPP
# define CONFIG_HPP

#include <string>
#include <system_error>
#include <utility>//std::exchange
#include <cctype>//std::isalnum
#include <chrono>

class Config {
	int					port_;
	std::string					portStr_;
	std::string					password_;
	const std::string			msgDelimiter_{"\n"};//for netcat partial command sending
	const std::string			serverName_{"ft_irc, WB edition ®"};
	const std::string			allowedPassChars_{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_!?#"};//validate_() specifies minimum 62 chars
	static constexpr unsigned int	maxAuthAttempts_{10};
	static constexpr unsigned int	minPassLen_{4};
	static constexpr unsigned int	maxPassLen_{400};
	static constexpr std::chrono::seconds	allowedInactivity_{300};

	void	validate_();
	bool	isValidPort_();
	bool	isValidPassword_();

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
	std::string			getMsgDelimiter() const noexcept { return msgDelimiter_; }
};

#endif
