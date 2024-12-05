# Simple TCP Socket Client-Server in C

This repository contains two simple C programs demonstrating the use of TCP sockets to implement basic client-server communication.

## Client (`client.c`)

- Creates a TCP socket using `socket()`.
- Connects to the server using `connect()` on port `777`.
- Sends a message (`"hello world!"`) to the server.
- Receives a response (`"ack!"`) from the server and prints it.
- Handles connection errors and closes the connection after exchanging messages.

## Server (`socket.c`)

- Creates a TCP socket and binds it to port `777` using `bind()`.
- Listens for incoming connections with `listen()`.
- Accepts client connections using `accept()` and spawns a new process (`fork()`) to handle each client.
- Receives the client's message, sends a response (`"ack!"`), and prints the received payload.
- Runs in an infinite loop to handle multiple clients.

## How to Run

1. **Compile the client and server:**

   ```bash
   gcc client.c -o client
   gcc socket.c -o socket

2. **Run the server:**

   ```bash
   ./socket

3. **Run the client (in another terminal):**

   ```bash
   ./client

