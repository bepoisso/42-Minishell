<div align="center">
  <img height="200" src="https://raw.githubusercontent.com/Benjamin-poisson/My_image_bank/refs/heads/main/minishell.png"  />
</div>

# Minishell - Shell Simulation

Minishell is a project that involves creating a simple shell-like program. It will deepen your understanding of how shells work, including managing user input, executing commands, handling processes, and working with environment variables.

## Status
<div align="center">
  <img height="200" src="https://raw.githubusercontent.com/Benjamin-poisson/My_image_bank/refs/heads/main/minishell_success.png"  />
</div>

## Exemple
<div align="center">
  <img src="https://raw.githubusercontent.com/Benjamin-poisson/My_image_bank/refs/heads/main/minishell_exp.png"  />
</div>

## Objectives

The goal of this project is to create a shell program that can read user commands, parse them, execute the appropriate system calls, and manage processes, all while providing features like environment variable handling, input/output redirection, and command piping.

## Great Resources

<li><a href="https://www.gnu.org/software/bash/manual/bash.html">GNU Bash Manual</a></li>
<li><a href="https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html">Shell Syntax</a></li>
<li><a href="https://www.youtube.com/watch?v=yTR00r8vBH8">Basic shell by Oceano</a></li>

## Mandatory

<table>
  <tr>
    <th>Program name</th>
    <td>minishell</td>
  </tr>
  <tr>
    <th>Turn in files</th>
    <td>All necessary files to compile the program</td>
  </tr>
  <tr>
    <th>Makefile</th>
    <td>Yes</td>
  </tr>
  <tr>
    <th>External functions</th>
    <td>malloc, free, write, read, execve, fork, waitpid, dup, dup2, pipe, signal, exit, getenv, setenv, unsetenv</td>
  </tr>
  <tr>
    <th>Libft authorized</th>
    <td>No</td>
  </tr>
  <tr>
    <th>Description</th>
    <td>Simulate a Unix shell environment with process management and command execution.</td>
  </tr>
</table>

- The project must be written in C.
- Code must adhere to the Norm.
- No memory leaks are tolerated; all allocated memory must be freed.
- Provide a Makefile to compile the program with flags `-Wall -Wextra -Werror`.
- The Makefile must include rules for `all`, `clean`, `fclean`, and `re`.

## Functionality

The shell must:

- Parse and execute commands typed by the user.
- Handle simple commands (e.g., `ls`, `pwd`, `echo`).
- Support input and output redirection (`<`, `>`, `>>`).
- Handle piping between commands (`|`).
- Allow the use of environment variables (e.g., `echo $HOME`).
- Manage the current working directory using `cd`.
- Handle both foreground and background processes.

### Basic Features

- **Command Execution:** Use `execve` to execute commands with arguments.
- **Environment Variables:** Implement `getenv`, `setenv`, and `unsetenv` for managing environment variables.
- **Redirection:** Implement input (`<`), output (`>`), and append (`>>`) redirection.
- **Piping:** Implement the `|` operator to pipe the output of one command into the input of another.
- **Job Control:** Handle background processes using the `&` operator.
  
### Example Usage

```bash
$ ./minishell
minishell$ echo "Hello, World!"
Hello, World!
minishell$ ls -l
total 0
-rwxrwxrwx 1 user user 0 Jan 1 12:00 test_file
minishell$ cat < test_file
minishell$ echo "This is a test" > newfile
minishell$ cat newfile
This is a test
minishell$ exit
```

---

### Edge Cases to Handle

- **Empty Input:** Handle empty lines gracefully.
- **Invalid Commands:** Show an error message when a command is not found.
- **Multiple Piping:** Handle chains of commands connected with multiple pipes.
- **Variable Expansion:** Properly expand environment variables like `$HOME` or `$PATH`.

---

## Bonuses

If the mandatory part is completed perfectly, consider the following bonus features:

- **Signals Handling:** Properly handle signals like `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\).
- **Advanced Job Control:** Implement background processes with `&` and support for `fg`, `bg`, and `jobs` commands.
- **Wildcard Expansion:** Support wildcard characters like `*` and `?` in command arguments (e.g., `ls *.txt`).
- **History Management:** Implement a history feature that remembers previous commands and allows navigating through them.

Bonus files should be named with the `_bonus` suffix.

---

## Key Concepts to Master

- **Forking and Executing Processes:** Using `fork` to create child processes and `execve` to execute programs.
- **File Descriptors:** Handling redirection and piping using `dup` and `dup2`.
- **Environment Management:** Managing environment variables with `getenv`, `setenv`, and `unsetenv`.
- **Signal Handling:** Managing and catching signals like `SIGINT` or `SIGQUIT`.
- **Job Control:** Implementing background processes and handling process termination.

---

## Example Output

```bash
$ ./minishell
minishell$ echo $PATH
/usr/bin:/bin:/usr/sbin:/sbin
minishell$ ls | grep shell
minishell$ cat > output.txt
This is a new file
minishell$ cat output.txt
This is a new file
minishell$ exit
```

This log represents the correct behavior of the shell, where commands are parsed and executed, output is displayed, and files are created or modified.
