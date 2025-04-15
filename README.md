# 📁 Directory & File Management System (C Project)

A lightweight, terminal-based application in C that simulates basic file system operations. This program allows users to manage directories and files interactively through simple commands.

---

## 🚀 Features

Interact with a virtual file system using commands to:

- 📂 Create directories and files  
- 🗂️ Navigate between directories  
- 🧾 View directory contents  
- 🗑️ Delete files or directories  
- 🔍 Search for files  
- ✏️ Edit file contents  

All operations are performed within the program — this is a simulation and does not modify your actual system files.

---

## 🛠️ How to Run

1. **Compile the Program**  
   Use `gcc` or any C compiler:
   ```bash
   gcc file_system.c -o file_system
   ```

2. **Run the Executable**
   ```bash
   ./file_system
   ```

---

## 💡 Available Commands

| Command       | Description                                      |
|---------------|--------------------------------------------------|
| `createDir`   | Create a new directory in the current location   |
| `createFile`  | Create a new file and enter content              |
| `listDir`     | Show all directories and files recursively       |
| `changeDir`   | Navigate into a subdirectory                     |
| `deleteFile`  | Remove a specific file                           |
| `deleteDir`   | Remove the current directory and its contents    |
| `searchFile`  | Search for a file by name                        |
| `editFile`    | Modify the content of an existing file           |
| `quit`        | Exit the program                                 |

---

## 🧪 Sample Workflow

**Create a directory**
```
Enter command: createDir  
Enter directory name: Projects
```

**Add a file**
```
Enter command: createFile  
Enter file name: notes.txt  
Enter file content: Assignment notes for C project.
```

**View contents**
```
Enter command: listDir
```

**Navigate into a directory**
```
Enter command: changeDir  
Enter directory name: Projects
```

**Delete a file**
```
Enter command: deleteFile  
Enter file name: notes.txt
```

**Remove a directory**
```
Enter command: deleteDir
```

