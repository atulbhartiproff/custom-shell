# Custom Shell

A lightweight custom shell built purely in c++.

## Features

- Interactive REPL with a `$ ` prompt
- Built-in commands:
  - `echo`
  - `exit`
  - `pwd`
  - `cd`, including `cd ~`
  - `type`
- External command execution through the system `PATH`
- Current-directory fallback in `PATH` so local executables can be run easily
- Quote handling for single and double quoted arguments
- Backslash escaping for unquoted and double-quoted input
- Output redirection with `>`
- Append redirection with `>>`
- Error redirection with `2>`

## Project Structure

- `src/main.cpp` contains the shell loop and builtin command dispatch
- `src/echo_handler.hpp` parses `echo` input and handles redirection cases
- `src/exec_handler.hpp` runs external commands
- `src/type_handler.hpp` resolves command locations in `PATH`
- `src/arrow_handler.hpp` handles `>` redirection
- `src/append_stdout.hpp` handles `>>` redirection
- `src/stderr_redirect.hpp` handles `2>` redirection

## Run

Get the latest version from release. 

## Issues

- Windows testing still waiting.