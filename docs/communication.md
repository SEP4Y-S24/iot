# Clock Communication Protocol (CCP)

**CCP** is a communication protocol defined to communicate with the clock. It is based on sending TCP messages and follows a request-reply model. Both communicators act as server and client.

## Protocol Layers

| **Layer**           | **Protocol** |
|---------------------|--------------|
| Application Layer   | CCP          |
| Transport Layer     | TCP          |
| Network Layer       | IP           |

## Messages

The current agreed encoding for the messages is **ASCII**. There are specific messages for the clock and server, with slightly different formats for requests and responses.

Messages are formatted using lines, with a pipe character ("|") separating adjacent data in a segment. [Message delimiters](https://learn.microsoft.com/pl-pl/biztalk/adapters-and-accelerators/accelerator-hl7/message-delimiters) are used to structure the messages.

### Request Format

| Line Number | Explanation                                    | Example      |
| ----------- | ---------------------------------------------- | ------------ |
| 1           | Action type - 2 char                           | MS\|         |
| 2           | Number of characters in the body (excluding the last pipe character) | 10\|         |
| 3           | Body                                           | Hello Mama\| |

### Response Format

| Line Number | Explanation                                    | Example      |
| ----------- | ---------------------------------------------- | ------------ |
| 1           | Action type - 2 char                           | MS\|         |
| 2           | Status code                                    | 1\|          |
| 3           | Number of characters in the body (excluding the last pipe character) | 8\|          |
| 4           | Body                                           | Received\|   |

## Request-Response Model

Not all requests receive responses, as sometimes it is simply unnecessary.


