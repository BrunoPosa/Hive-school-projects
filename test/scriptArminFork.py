import subprocess
import sys
import time
import random

# Name of the tmux session to create/use.
SESSION_NAME = "irssi_session"

def create_tmux_session(session_name):
    """Creates a new tmux session in detached mode."""
    subprocess.run(["tmux", "new-session", "-d", "-s", session_name])

def create_tmux_window(session, window_name, command):
    """
    Creates a new tmux window in the given session, running the specified command.
    """
    subprocess.run(["tmux", "new-window", "-t", session, "-n", window_name, command])

def send_tmux_command(window_name, command):
    """
    Sends a command to a specific tmux window.
    """
    subprocess.run(["tmux", "send-keys", "-t", f"{SESSION_NAME}:{window_name}", command, "C-m"])

def open_irssi_tmux(nickname, ip_address, port, password, channel="#ch1"):
    """
    Launches irssi in a new tmux window, joins a channel, and says hello.
    """
    window_name = nickname
    irssi_command = f"irssi -c {ip_address} -p {port} -w {password} -n {nickname}"
    create_tmux_window(SESSION_NAME, window_name, irssi_command)

    # time.sleep(2)  # Give irssi time to start
    send_tmux_command(window_name, f"/JOIN {channel}")
    # time.sleep(0.5)
    send_tmux_command(window_name, f"hello my name is \"{nickname}\"")
    return window_name

def mode1(ip_address, port, password):
    base_nickname = input("Enter base nickname: ")
    count = int(input("Enter number of clients: "))
    windows = [open_irssi_tmux(f"{base_nickname}{i+1}", ip_address, port, password)
               for i in range(count)]
    return windows

def mode2(ip_address, port, password):
    nicknames = input("Enter nicknames separated by spaces: ").split()
    windows = [open_irssi_tmux(nickname, ip_address, port, password)
               for nickname in nicknames]
    return windows

def simulate_chat(windows, duration=20):
    """
    Simulates random chat messages by picking random clients and sending messages.
    Runs for `duration` seconds.
    """
    messages = [
        "Hey everyone!",
        "What's up?",
        "Anyone working on something cool?",
        "I need coffee!",
        "Did you see the latest update?",
        "brb",
        "LOL that's hilarious",
        "No way that's true...",
        "Anyone play chess here?",
        "I miss the old IRC days.",
        "Check this out: https://example.com"
    ]
    
    end_time = time.time() + duration
    while time.time() < end_time:
        window = random.choice(windows)
        message = random.choice(messages)
        send_tmux_command(window, message)
        //time.sleep(random.uniform(0.03, 0.08))  # Random fast pace

def close_irssi(windows):
    """
    Sends the /exit command to each irssi client running in tmux,
    then kills the tmux session.
    """
    for win in windows:
        subprocess.run(["tmux", "send-keys", "-t", f"{SESSION_NAME}:{win}", "/exit", "C-m"])
    time.sleep(1)
    subprocess.run(["tmux", "kill-session", "-t", SESSION_NAME])

def main():
    ip_address = input("Enter IRC server IP address: ")
    port = input("Enter port: ")
    password = input("Enter password: ")

    create_tmux_session(SESSION_NAME)

    mode = input("Select mode (1 or 2): ")
    windows = []

    if mode == "1":
        windows = mode1(ip_address, port, password)
    elif mode == "2":
        windows = mode2(ip_address, port, password)
    else:
        print("Invalid mode selected.")
        sys.exit(1)

    print("\nAll clients started in tmux windows within the session 'irssi_session'.")
    print("You can attach to the session with: tmux attach -t irssi_session")

    # Simulate chat before allowing user to end
    print("\nSimulating chat for 60 seconds...")
    simulate_chat(windows, duration=60)

    input("\nPress Enter when you want to close all clients...")
    close_irssi(windows)
    print("All clients closed.")

if __name__ == "__main__":
    main()
