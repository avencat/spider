# SQLite3 class
## 1. Attributes
### 1.1. db
**Type:**  
`sqlite3 *`

**Getter/Setter:**  
None.

**Description:**  
This attribute is the database pointer. This can only be edited by the SQLite3 class.

### 1.2. rc
**Type:**  
`int`

**Getter/Setter:**  
Getter only.

**Description:**  
This attribute contains the return value of the last SQL command execution.

### 1.3. zErrMsg
**Type:**  
`char *`

**Getter/Setter:**  
None.

**Description:**  
This attribute contains the last error message from SQL command execution.  
**ATTENTION, this attribute will always be either NULL or FREED. DO NOT ATTEMPT TO USE IT!**

### 1.4. sql
**Type:**  
`std::string`

**Getter/Setter:**  
Getter only.

**Description:**  
This attribute contains the last SQL query sent to the database.

### 1.5. message
**Type:**  
`std::string`

**Getter/Setter:**  
Getter only.

**Description:**  
This attribute will contain a custom message about the last SQL execution.

### 1.6. printMessage
**Type:**  
`bool`

**Getter/Setter:**  
Both.

**Description:**  
This attribute is for debug/info purposes. If set to true, it will print *"message"* at each SQL query execution.

### 1.7. printRequest
**Type:**  
`bool`

**Getter/Setter:**  
Both.

**Description:**  
This attribute is for debug/info purposes. If set to true, it will print *"sql"* at each SQL query execution.

## 2. Methods
### 2.1. Constructor/Destructor
#### 2.1.1. Constructor
**Prototype:**  
```c++
SQLite3(const std::string &name, const bool silent = false);
```

**Description:**  
Upon creation, the SQLite3 class needs the path of the database to open.  
Optional parameter silent can be provided as true for a silent initialization.

**Example:**  
```c++
SQLite3 db("test.db", true);
```

#### 2.1.2. Destructor
**Prototype:**  
```c++
~SQLite3();
```

**Description:**  
If any database has been successfully open, it will be automatically closed.

### 2.2. SQL commands
#### 2.2.1. Table
##### 2.2.1.1. Create
**Prototype:**  
```c++
int createTable(const std::string &name, const std::vector<std::string> &columns);
```

**Description:**  
The *createTable* method will create a table with the provided name and create corresponding columns provided in a SQLite way like.  
Return 0 on success.

**Example:**  
```c++
std::string name("COMPANY");
SQLite3 db("test.db", true);
std::vector<std::string> columns;

columns.push_back("ID INT PRIMARY KEY NOT NULL");
columns.push_back("NAME TEXT NOT NULL");
columns.push_back("AGE INT NOT NULL");
columns.push_back("ADDRESS CHAR(50)");
columns.push_back("SALARY REAL");

if (db.createTable(name, columns))
  return (1);
```

#### 2.2.2. Queries
##### 2.2.2.1. INSERT
**Prototype:**  
```c++
int insert(const std::string &name, const std::vector<std::string> &columns, const std::vector<std::string> &values);
```

**Description:**  
The *insert* method will make a INSERT query to the table *"name"* with provided columns *"columns"* and values *"values"*.  
Return 0 on success.

**Example:**
```c++
SQLite3 db("test.db", true);
std::string name("COMPANY");
std::vector<std::string> columns;
std::vector<std::string> values;

columns.push_back("ID");
columns.push_back("NAME");
columns.push_back("AGE");
columns.push_back("ADDRESS");
columns.push_back("SALARY");
values.push_back("1");

values.push_back("'Paul'");
values.push_back("32");
values.push_back("'California'");
values.push_back("20000.00");

if (db.insert(name, columns, values))
  return (1);
```

##### 2.2.2.2. SELECT
**Prototype:**  
```c++
int select(const std::string &name, std::vector<std::string> &columns);
```

**Description:**  
The *select* method will make a SELECT query to the table *"name"* by selecting the provided columns *"columns"*.

**Example:**  
```c++
SQLite3 db("test.db", true);
std::string name("COMPANY");
std::vector<std::string> columns;

columns.push_back("*");

if (db.select(name, columns))
  return (1);
```

#### 2.2.2.3. UPDATE
**Prototype:**  
```c++
int update(std::string &name, std::string &column, std::string &value, std::string &conditions);
```

**Description:**  
The *update* method will make a UPDATE query to the column *"column"* in table *"name"* with value *"value"* where conditions *"conditions"* are true.

**Example:**  
```c++
SQLite3 db("test.db", true);
std::string name("COMPANY");
std::string column("SALARY");
std::string value("25000.00");
std::string conditions("ID=1");

if (db.update(name, column, value, conditions))
  return (1);
```

#### 2.2.2.4 DELETE
**Prototype:**  
```c++
int deleteSQL(std::string &name, std::string &conditions);
```

**Description:**  
The *deleteSQL* method will make a DELETE query to the table *"name"* where conditions *"conditions"* are true.

**Example:**
```c++
SQLite3 db("test.db", true);
std::string name("COMPANY");
std::string conditions("ID=2");

if (db.delete(name, conditions))
  return (1)
```

### 2.2.3. Other
#### 2.2.3.1. callback
**Prototype:**  
```c++
static int callback(void *data, int ac, char **av, char **azColName);
```

**Description:**  
The callback will be used by the SQLite3 itself when needed (during, for example, a SELECT). It will print the contained data on screen.

## 3. Class requirement
### 3.1. Makefile
Following link flags must be added: `-lsqlite3 -lboost_thread -ldl`
