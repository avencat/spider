# Spider protocol

## 1. Client requests

### 1.1. Client commands
Command | Parameters | Description
------- | ---------- | -----------
SYN | NumberA | First part of the three-way handshake
ACK | NumberB + 1 | Last part of the three-way handshake
GREET | Username, Public_key | Asking connection when no ID is known by the client
HELLO | ID | Asking the connection with known ID
WORD | Len_title, Len_content, Title, Content | Sending logged data for a word
BREAK | Len_title, Len_content, Title, Content | Sending logged data for a breaking or special character
MPOS | Len_title, Len_content, Title, Content | Sending logged data for a cursor position when mouse is inactive for 1-2 second(s)
MBTN | Len_title, Len_content, Title, Content | Sending logged data for a mouse button click
PING | | Used to keep connection alive
QUIT | | Used to close connection

### 1.2. Upon connection:

#### 1.2.1. HANDSHAKE

##### 1.2.1.1. SYN

**Command:** SYN
```
Type  NumberA
char  int
```

**Reply:**  
SYN-ACK

**Description:**  
The client **MUST** send a SYN command when connecting to the server. Otherwise, the server will refuse connection and close it.  
NumberA is a randomly generated number.  
The server will reply this number + 1 and another random number. If the NumberA returned by the server is not NumberA+1, connection **MUST BE CLOSE IMMEDIATLY**.

##### 1.2.1.2. ACK

**Command:** ACK
```
Type  NumberB+1
char  int
```

**Reply:**  
RPL_OK

**Description:**  
The client **MUST** send a SYN-ACK when receiving SYN-ACK command from the server.  
NumberB is a number sent by the server with SYN-ACK command.  
The server will reply RPL_OK and the client will be authorize to send a GREET or HELLO command.

#### 1.2.2. GREET

**Command:** GREET
```
Timestamp Type  Len_username  Len_key Username  Public_key
long      char  int           int     char*     char*
```
**Reply:**  
RPL_ID  

**Description:**  
The client send a GREET command when no ID is found in the registry. A Username and a public key generated client-side must be sent.  
The server should reply with a new ID and a public key which should be stored in client registry along to the client private key.

#### 1.2.3. HELLO

**Command:** HELLO
```
Timestamp Type  ID
long      char  int
```
**Reply:**  
RPL_ID_OK  
ERR_BAD_ID  

**Description:**  
The client send a HOME command when an ID is found in the registry.  
The server should reply with a RPL_OK if the ID is correct.  
If the ID is not correct the server will send a ERR_BAD_ID and wait for a GREET command.

### 1.3. Log transfer:

#### 1.3.1. WORD | BREAK | MPOS | MBTN

**Command:** WORD | BREAK | MPOS | MBTN
```
Timestamp Type  Len_title Len_content Title   Content
long      char  int       int         char*   char*
```
**Reply:**  
RPL_RECEIVED  
ERR_BAD_MSG_FORMAT  
ERR_IO_ERROR

**Description:**  
The client send a WORD, BREAK, MPOS or MBTN command when it sends the logged data.  
The title corresponds to the foreground window and content is relative to the type of data transferred.  

* WORD will log the word typed by the user.  
* BREAK will log any special or breaking character.  
* MPOS will log the following format: "x;y" when cursor is inactive for 1-2 second(s) where:
  * x and y stands for an integer position relative to x and y axis.  
* MBTN will log the following format: "x;y;BTN" where:
  * x and y are position on the axis
  * BTN is the mouse button pressed

The server should reply with a RPL_RECEIVED. If data format is wrong, the server will send a ERR_BAD_MSG_FORMAT to the client.  
A ERR_IO_ERROR can be send by the server if the data takes more space than it can store. In that case, the server will close the connection. The client should keep the data stored locally and try connecting again later.

### 1.4. Other:

#### 1.4.1. PING

**Command:** PING
```
Timestamp Type
long      char
```

**Reply:**  
RPL_PONG

**Description:**  
The client **MUST** send a ping command from time to time in order to keep connection alive. Otherwise, connection is subject to be closed by server.

#### 1.4.2. QUIT

**Command:** QUIT
```
Timestamp Type
long      char
```

**Reply:**  
RPL_QUIT_OK

**Description:**  
The client send the QUIT command when he wants to disconnect from the server.  
The client should wait for a RPL_QUIT_OK before closing connection.

---
## 2. Server requests

### 2.1. Server commands:
Command | Parameters | Description
------- | ---------- | -----------
SYN-ACK | NumberA + 1, NumberB | Used for handshake upon connection
MSG | Message | Used when sending message to the client
START | Type | Used to start the logging of a specific data type
STOP | Type | Used to stop the logging of a specific data type
CLOSE |  | Used to ask local logging when server closes

#### 2.1.1. SYN-ACK

**Command:** SYN-ACK
```
Code  NumberA+1 NumberB
int   int       int
```

#### 2.1.2. MSG

**Command:** MSG  
```
Code  Message
int   char*
```
**Description:**  
The server can use the MSG command to send informations to the client.

#### 2.1.3. START

**Command:** START  
```
Code  Type
int   char
```
**Description:**  
The server can use the START command to tell the client to start logging a specific activity.

#### 2.1.4. STOP

**Command:** STOP  
```
Code  Type
int   char
```
**Description:**  
The server can use the STOP command to tell the client to stop logging a specific activity.

#### 2.1.5. CLOSE

**Command:** CLOSE  
```
Code
int
```
**Description:**  
The server will send a CLOSE command to all user in order to tell them to start logging locally.

---
## 3. Types
Type | Format
---- | ------
WORD | "Word"
BREAK | "Enter"
MPOS | "x;y"
MBTN | "x;y;BTN"
ALL | /// Every other type \\\\\\

---
## 4. Codes
Code | Short name | Description
---- | ---------- | -----------
100 | SYN-ACK | Handshake used by the server upon client connection
101 | MSG | Used by the server when sending a message to the client
102 | START | Used by the server when asking the client to start specific logging tasks
103 | STOP | Used by the server when asking the client to stop specific logging tasks
104 | CLOSE | Used by the server when the server will close
---- | ---------- | -----------
200 | RPL_ID | Reply followed by a new ID and a key to be stored and use for future connection and message exchange
201 | RPL_ID_OK | Reply to a correct connection ID to engage data logging
202 | RPL_RECEIVED | Reply when a packet containing correct data format is received by the server
203 | RPL_OK | Used to tell last command is OK
204 | RPL_PONG | Used when a client send a PING. Connection should be keep alive
205 | RPL_QUIT_OK | Used when a client send a QUIT command
---- | ---------- | -----------
400 | ERR_BAD_ID | Error reply to a wrong connection ID
401 | ERR_BAD_MSG_FORMAT | Error reply to a wrong data format
---- | ---------- | -----------
500 | ERR_IO_ERROR | Server error reply when IO fails followed by connection closing
