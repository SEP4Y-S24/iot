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

# Message Formats

## Clock Messages

### TM - request for time

Device sends a request to receive the current time. Requires a response.

**Request:**

| Action type | TM\| |
| --- | --- |
| Body length | 0\| |

**Response:**

The body of the response should contain the time in format HHMM

| Action type | TM\| |
| --- | --- |
| Response status code | 1\| |
| Body length | 4\| |
| Body | 1230\| |

### CK - clock public key

Message sent during key exchange contains the public key of the clock.

**Example:**

CK\|64\|1FF601B55B0C7499EE6FADA40DFFAE60477F1A1EFC55A8EDBD4A2850C71E6571A00CFF26602ADEC9F37207509D04839B79BA153001019F8B3A28B9030B986552\|

### TH - Send Humidity & Temperature

This action will happen periodically and will send the Humidity and Temperature Data to the server.

**Request:**

| Action type | TH\| |
| ------------ | -------- |
| Body length | 16\| |
| Body | H-XX.YY-T-AA.BB\| |

**Response:**

Not mandatory. The response does not have to have a body.

| Action type | TH\| |
| --- | --- |
| Status code | 1\| |

### AU - authentication

Message sent during authentication after the clock connects to the server. The body of the message contains the unique key of the clock or nothing if the clock does not have a key yet.

**Request:**

| Action type | AU\| |
| --- | --- |
| Length | 20\| |
| Body | qwertyuiopasdfghjklz\| |

**Response:**

If the server recognizes the authentication key of the clock, it should respond with status code 1. If it does not know the key or no key was sent, the response must have a status code of 3 and a new auth key in the body.

| Action type | AU\| |
| --- | --- |
| Status code | 3\| |
| Length | 0\| |
| Body | 0\| |

| Action type | AU\| |
| --- | --- |
| Status code | 3\| |
| Length | 20\| |
| Body | zxcrtyuiopasdfghjkla\| |

## Cloud Messages

### MS - Message

Cloud sends a message to the device telling it to display a new message. Requires a response.

**Request:**

| Action type | MS\| |
| --- | --- |
| Body length | 5\| |
| Body | Hello\| |

**Response:**

Doesn’t have a body

| Action type | MS\| |
| --- | --- |
| Status code | 1\| |

### CA - request to set up the alarm

Cloud sends the request to the device to create an alarm

**Request:**

| Action type | CA\| |
| --- | --- |
| Body length | 4\| |
| Body | 1510\| |

**Response:**

| Action type | CA\| |
| --- | --- |
| Response status code | 1\| |

### DA - request to delete the alarm

Cloud sends the request to the device to delete an alarm

**Request:**

| Action type | DA\| |
| --- | --- |
| Body length | 4\| |
| Body | 1510\| |

**Response:**

| Action type | DA\| |
| --- | --- |
| Response status code | 1\| |

### SK - server key

Message sent during key exchange contains the public key of the server.

**Example:**

SK\|64\|1FF601B55B0C7499EE6FADA40DFFAE60477F1A1EFC55A8EDBD4A2850C71E6571A00CFF26602ADEC9F37207509D04839B79BA153001019F8B3A28B9030B986552\|

### KV - key verified

A message sent at the end of the authentication process - telling the clock that it is authenticated and can proceed to a working state.

| Action Type | KV\| |
| --- | --- |
| Body | 0\| |



