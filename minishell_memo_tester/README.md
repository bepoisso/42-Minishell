# minishell_memo_tester

## Introduction
This folder contains a memory tester for the Minishell project. It is designed to detect memory leaks in the Minishell code.

## Installation
To use this tester, clone this folder directly to the root of the Minishell project.

## Execution
To run the tester, place yourself in the tester folder and execute the memory_check.sh script by passing a command file as an argument. For example:

```bash
./memory_check.sh commands.txt
```

You can customize the command files to test the commands you want.

## Results
If memory leaks are detected, Valgrind's output will be displayed on the standard output. It is important to check that the functions responsible for the leaks mentioned in the Valgrind output are not ignored.

## Warning
Although most leaks inherent to functions of the type cat, ls, grep, etc. are ignored, some leaks are not ignored. It is therefore important to check that the functions responsible for the leaks mentioned in the Valgrind output are not compromising.

## Valgrind Output
When a leak causes "definitely lost" leaks, Valgrind's output will be in red.

## Example Usage
To test the commands contained in the commands.txt file, run the following command:

```bash
./memory_check.sh commands.txt
```

If memory leaks are detected, Valgrind's output will be displayed on the standard output.
