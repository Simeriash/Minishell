*This project has been created as part of the 42 curriculum by dlanehar & julauren*

# **Description**

The goal of this project is to create a "simple" shell based on Bash.

The idea is to write a program that allows communication with the computer in a human-readable language using command lines.

The shell has been made with these instructions in mind:

	Display a prompt when waiting for a new command.
	Have a working history.
	Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
	Use at most one global variable to indicate a received signal. Consider the implications: this approach ensures that your signal handler will not access you main data structures.

	Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).

	Handle ’ (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.

	Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).

	Implement the following redirections:
	< should redirect input.
	\> should redirect output.
	<< should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
	\>> should redirect output in append mode.

	Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.

	Handle environment variables ($ followed by a sequence of characters) which should expand to their values.

	Handle $? which should expand to the exit status of the most recently executed foreground pipeline.

	Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
	In interactive mode:

	ctrl-C displays a new prompt on a new line.
	ctrl-D exits the shell.
	ctrl-\ does nothing.

	Your shell must implement the following built-in commands:
	echo with option -n
	cd with only a relative or absolute path
	pwd with no options
	export with no options
	unset with no options
	env with no options or arguments
	exit with no options

# **Instructions**

Clone the repository:
```
git clone "repo goes here"
```

Build with make:
```
make
```

To run the program, you can either launch the executable using valgrind and your preferred flags, or use this command to simply launch the program with valgrind and some selected flags.

```
Launch with executable:
./minishell

Launch using valgrind:
valgrind ./minishell

Launch using make, with the valgrind rule:
make valgrind
```

The makefile includes the following rules: all clean fclean re valgrind

# **Ressources**

Bash manual: <br>
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/

Code Vault youtube videos. Notably, videos about using pipes and redirection with dup and dup2.<br>
https://www.youtube.com/@CodeVault

Medium article for further help understanding pipes:<br>
https://medium.com/@omimouni33/pipex-the-42-project-understanding-pipelines-in-c-71984b3f2103

Stack overflow for stat:<br>
https://stackoverflow.com/questions/3138600/correct-use-of-stat-on-c

ChatGPT was used to help further understand concepts such as pipes and forks.
