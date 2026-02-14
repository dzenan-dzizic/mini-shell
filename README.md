# Mini Shell – C Project

A *feature-rich*, interactive command-line shell written in C, designed for file and directory management, process execution, and system inspection. Built from scratch (with extensive research and experimentation) by a self-taught programmer.

# Features

## File Operations
-Create, delete, copy, move, and rename files.

--Directory Operations
-Create, delete, rename, and list directories and their contents.

## Process Management

-Run arbitrary system commands using fork() and execvp().
-You can launch another program.

## System Utilities

-Display current working directory (pwd), uptime, and local time.

## Interactive CLI

Custom command prompt (mini-shell>), input trimming, and argument parsing.

## Screen Management
Clear terminal screen with the clear command, exit the shell with exit command.

## Note

Some commands such as copying will sometimes require root privileges due to file permissions.

| Command                      | Description                                     |
| -----------------------------| ----------------------------------------------- |
| `pwd`                        | Display current working directory               |
| `list`                       | List files and directories in the current path  |
| `chdir <dir>`                | Change the current working directory            |
| `create <file>`              | Create a new empty file                         |
| `remove <file>`              | Delete a file                                   |
| `makedir <dir>`              | Create a new directory                          |
| `removedir <dir>`            | Delete a directory and its contents             |
| `rename <file>`              | Rename a file                                   |
| `rnmdir <dir>`               | Rename a directory                              |
| `copy <file> <dest>`         | Copy a file to a destination directory          |
| `move <file> <dest>`         | Move a file to a destination directory          |
| `uptime`                     | Display system uptime and current date/time     |
| `clear`                      | Clear the terminal screen                       |
| `exit`                       | Exit the shell                                  |
| `<any system command>`       | Execute system commands like `ls`, `echo`, `sudo su` etc. |

# Clone

```bash
git clone https://github.com/dzenan-dzizic/mini-shell.git
```

# Disclaimer

This software is provided **as-is**, for educational purposes only.  
The author is not responsible for any data loss, system damage, or other consequences resulting from its use.  
Use at your own risk.

