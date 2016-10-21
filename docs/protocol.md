# Spider protocol

## Client requests

### Client commands
Command | Parameters | Description
------- | ---------- | -----------
GREET | Username, Public_key | Asking connection when no ID is known by the client
HELLO | ID | Asking the connection with known ID
WORD | Len_title, Len_content, Title, Content | Sending logged data for a word
BREAK | Len_title, Len_content, Title, Content | Sending logged data for a breaking or special character
MPOS | Len_title, Len_content, Title, Content | Sending logged data for a cursor position when mouse is inactive for 1-2 second(s)
MBTN | Len_title, Len_content, Title, Content | Sending logged data for a mouse button click

### Upon connection:

#### GREET

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

#### HELLO

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

### Log transfer:

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

---
## Server requests

### Server commands:
Command | Parameters | Description
------- | ---------- | -----------
MSG | Message | Used when sending message to the client
START | Type | Used to start the logging of a specific data type
STOP | Type | Used to stop the logging of a specific data type

#### MSG

**Command:** MSG  
```
Code  Message
int   char*
```
**Description:**  
The server can use the MSG command to send informations to the client.

#### START

**Command:** START  
```
Code  Type
int   char
```
**Description:**  
The server can use the START command to tell the client to start logging a specific activity.

#### STOP

**Command:** STOP  
```
Code  Type
int   char
```
**Description:**  
The server can use the START command to tell the client to stop logging a specific activity.

---
## Types
Type | Format
---- | ------
WORD | "Word"
BREAK | "Enter"
MPOS | "x;y"
MBTN | "x;y;BTN"
ALL | /// Every other type \\\\\\

---
## Codes
Code | Short name | Description
---- | ---------- | -----------
100 | MSG | Used by the server when sending a message to the client
101 | START | Used by the server when asking the client to start specific logging tasks
102 | STOP | Used by the server when asking the client to stop specific logging tasks
---- | ---------- | -----------
200 | RPL_ID | Reply followed by a new ID and a key to be stored and use for future connection and message exchange
201 | RPL_ID_OK | Reply to a correct connection ID to engage data logging
202 | RPL_RECEIVED | Reply when a packet containing correct data format is received by the server
---- | ---------- | -----------
400 | ERR_BAD_ID | Error reply to a wrong connection ID
401 | ERR_BAD_MSG_FORMAT | Error reply to a wrong data format
---- | ---------- | -----------
500 | ERR_IO_ERROR | Server error reply when IO fails followed by connection closing
