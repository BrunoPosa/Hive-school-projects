// main.cpp
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Config.hpp"

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

int test_count = 0;
int success_count = 0;

void run_test(void (*test)(), const std::string& name) {
	std::cout << "Test: " << name << "\n";
	try {
		test();
		std::cout << GREEN << "  ✓ Passed" << RESET << "\n";
		success_count++;
	} catch (const std::exception& e) {
		std::cout << RED << "  ✗ Failed: " << e.what() << RESET << "\n";
	}
	test_count++;
}

void expect(bool condition, const std::string& message) {
	if (!condition) throw std::runtime_error(message);
}

// ==================== Test Cases ====================
void test_default_construction() {
	Config cfg;
	expect(cfg.getPort() == 6667, "Default port should be 6667");
	expect(cfg.CheckPassword("4242"), "Default password should be '4242'");
	expect(!cfg.CheckPassword(""), "Empty password should fail");
}

void test_valid_port_construction() {
	struct TestCase { std::string input; int expected; };
	std::vector<TestCase> cases = {
		{"1024", 1024},
		{"65535", 65535},
		{"12345", 12345},
	};
	
	for (const auto& tc : cases) {
		Config cfg(tc.input, "validPass123");
		expect(cfg.getPort() == tc.expected, "Port mismatch: " + tc.input);
	}
}

void test_invalid_port_construction() {
	std::vector<std::string> cases = {
		"0", "01234", "1000", "65536", "-4",
		"notanumber", "1234a", "inf", "", " 1234",
		"12345.6", "2147483648" // Last one is > INT_MAX
	};

	for (const auto& port : cases) {
		bool threw = false;
		try {
			Config cfg(port, "validPass123");
		} catch (const std::invalid_argument&) {
			threw = true;
		}
		expect(threw, "Should reject invalid port: " + port);
	}
}

void test_password_validation() {
	// First get the allowed characters from Config (requires getter)
	const std::string allowedChars = Config().getAllowPassChars();
	
	// Test cases now only need the password string
	std::vector<std::string> test_passwords = {
		"ValidPass123",
		"",
		"space pass",
		"special!",
		"UPPERCASE123",
		"lowercase42",
		"aaa",
		"123456",
		"with_underscore",
		"with-dash"
	};

	for (const auto& password : test_passwords) {
		bool should_be_valid = true;

		// Check against allowed characters
		if (password.empty()) {
			should_be_valid = false;
		} else {
			for (char c : password) {
				if (allowedChars.find(c) == std::string::npos || password.length() < Config().getMinPassLen()) {
					should_be_valid = false;
					break;
				}
			}
		}

		// Test against Config class
		bool config_says_valid = true;
		try {
			Config cfg("1234", password);
		} catch (const std::invalid_argument&) {
			config_says_valid = false;
		}

		expect(config_says_valid == should_be_valid, 
			"Password '" + password + "': Config validation mismatch");
	}
}

void test_move_operations() {
	// Test move constructor
	{
		Config cfg1("1234", "mypass");
		Config cfg2(std::move(cfg1));
		
		expect(cfg2.getPort() == 1234, "Move constructor port");
		expect(cfg2.CheckPassword("mypass"), "Move constructor password");
		expect(cfg1.getPort() == -1, "Moved-from port should be -1");
	}

	// Test move assignment
	{
		Config cfg1("4321", "pass1");
		Config cfg2;
		cfg2 = std::move(cfg1);
		
		expect(cfg2.getPort() == 4321, "Move assignment port");
		expect(cfg2.CheckPassword("pass1"), "Move assignment password");
		expect(cfg1.getPort() == -1, "Move-assigned-from port should be -1");
	}
}

int main() {
	std::cout << "=== Config Class Test Suite ===\n";
	
	run_test(test_default_construction, "Default Construction");
	run_test(test_valid_port_construction, "Valid Port Construction");
	run_test(test_invalid_port_construction, "Invalid Port Handling");
	run_test(test_password_validation, "Password Validation");
	run_test(test_move_operations, "Move Operations");

	std::cout << "\nResults: "
			  << success_count << "/" << test_count 
			  << " tests passed (" 
			  << (success_count * 100 / test_count) << "%)\n";
	
	return success_count == test_count ? 0 : 1;
}