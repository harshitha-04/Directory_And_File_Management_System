# Directory & File Management System (Python Version)

A lightweight, terminal-based application in Python that simulates basic file system operations using Binary Search Trees for file management and a doubly linked list for directory navigation. This project is a direct port of its C-based counterpart, implemented fully in Python.

---

## Features

Interact with a virtual file system using commands to:

* Create directories and files
* Navigate between directories
* View contents of directories
* Delete files or directories
* Search for files
* Edit file contents
* Show specific file content

All operations are performed in memory and do not affect actual system files.

---

## How to Run

1. **Save the Script**

   Save the provided code in a file, for example:

   ```
   file_system.py
   ```

2. **Run the Program**

   Make sure you have Python 3.6 or higher installed, then execute:

   ```bash
   python file_system.py
   ```

---

## Available Commands

| Command      | Description                                    |
| ------------ | ---------------------------------------------- |
| `createDir`  | Create a new directory in the current location |
| `createFile` | Create a new file and enter content            |
| `listDir`    | Show all directories and files recursively     |
| `changeDir`  | Navigate into a subdirectory                   |
| `deleteFile` | Remove a specific file                         |
| `deleteDir`  | Remove the current directory and its contents  |
| `searchFile` | Search for a file by name                      |
| `editFile`   | Modify the content of an existing file         |
| `showFile`   | Display the content of a specific file         |
| `quit`       | Exit the program                               |

---

## Sample Workflow

**Create a directory**

```
Enter command: createDir
Enter directory name: Projects
```

**Add a file**

```
Enter command: createFile
Enter file name: notes.txt
Enter file content: Assignment notes for Python project.
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

**Show file content**

```
Enter command: showFile
Enter file name: notes.txt
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

---

## Notes

* This is a simulation only. All data is lost when the program exits.
* Designed for practicing data structures such as trees and linked lists in Python.
* Ideal for educational use and small command-line interface experiments.

