# ft_irc# IRC 42 Project - Hive Helsinki

## Overview
This project is an **IRC server** built from scratch in **C++** as part of Hive Helsinki's curriculum. It follows the **IRC protocol** defined in RFC standards (**RFC 1459, RFC 2813**) and implements fundamental **networking concepts** without external libraries.

## Project Goals
- Develop a **fully functional IRC server** that can handle multiple clients.
- Implement **IRC commands** according to protocol specifications.
- Ensure **robust networking, efficient message parsing, and concurrency**.
- Write comprehensive **tests** for stability and performance.
- Collaborate using the **open-floor agenda/self-selection** principle.

---

## Collaboration Guidelines
### **1. Open-Floor Agenda & Self-Selection**
Instead of assigning fixed roles, we will operate based on **self-selection**:
- Team members **choose tasks** from the available TODO list.
- Work is done in **dedicated Git branches**.
- Code is reviewed through **pull requests** before merging into `main`.

### **2. Git Workflow**
- **Main Branch (`main`)**: Holds stable, tested code.
- **Feature Branches**: Each task or feature gets a separate branch.
- **Pull Requests**: Before merging, team members review each other's code.

### **3. Communication & Documentation**
- Use **GitHub Issues** to track tasks and discussions.
- Write **clear commit messages** (`[Feature] Implement JOIN command`).
- Maintain a well-structured **README & Wiki** for easy onboarding.

## TODO Task outline (choose and implement)
Basic IRC Server - Todo List
Phase 1: Core Server & Networking
    Server Setup
        Create a Server class
            Implement socket creation, binding, listening
            Set the server socket to non-blocking mode
            Use poll()/select() to manage connections
            Handle errors using errno and strerror()

    Client Management
        Develop a ClientHandler (or Connection) class with:
            Socket descriptor, input/output buffers, connection state
        Maintain active client connections in a container (e.g., std::vector)

Phase 2: IRC Protocol Parsing & Message Handling
    Message Parsing
        Create a Message class
            Store prefix, command, and parameters (using std::string_view)
            Develop a parsing routine with unit tests

    Command Dispatch
        Build a CommandParser module
            Map command strings (e.g., "NICK", "JOIN") to handler functions
            Optionally use std::variant for type-safe command representation

Phase 3: Core IRC Commands
    User Registration
        Implement a User class with attributes: nickname, username, etc.

        Create command handlers:
            handleNick() for the NICK command
            handleUser() for the USER command

    Channel Management
        Develop a Channel class to manage channel names and user lists
        Implement:
            handleJoin() for channel joining
            Optionally implement handlePart() for leaving channels
   
 Messaging & Disconnect
        Implement handlePrivmsg():
            Differentiate between channel and direct messages using efficient string handling

        Implement handleQuit() to cleanly disconnect clients and clean up resources

## How to Contribute
1. Pick a task from the TODO list.
2. Create a **feature branch** (`feature-join-command`).
3. Work on the implementation.
4. Submit a **pull request** for team review.

5. Discuss improvements, merge into `main`, and repeat!
