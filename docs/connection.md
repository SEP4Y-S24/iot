First-time connection:
1) A clock connects to a server and handles encryption setup
2) The clock sends to the server an empty message with action type - AU(authentication)
example: AU|0||
3) The server generates a unique key and sends it as a response with status code 3 Unauthenticated 
Example: AU|20|x14sfpun6ldpgt1l6p82|
4) The clock displays the unique key on a display
5) A user logs in to the web app and inputs the unique key.
6) The web app sends the unique key to the server
7) The server compares the received code with the one it sent to the clock and if it matches it associates the clock with the user.
8) The server sends the clock a message with action type KV (Key verified).
example: KV|0||
9) The clock saves the key and starts to work as normal.
    
Next time connection:
1) The clock connects to the server and handles encryption setup
2) The clock sends to the server the saved unique key in the message with action type - AU(authentication)
example: AU|20|x14sfpun6ldpgt1l6p82|
3) The server knowing the clock answers with status code 1 - OK AU|1|0||
4) The clock starts to work as normal.
