# Stack Visualizer

A simple x86-64 stack and register visualizer written in C.

## Features

- Visual representation of a 10-slot stack
- 6 general-purpose registers (RAX, RBX, RCX, RDX, RSI, RDI)
- Stack pointer (RSP) and base pointer (RBP) tracking
- Real-time command execution

## Commands

### Stack Operations
- `push <value>` - Push a value onto the stack
- `pop <register>` - Pop from stack into a register
- `call <address>` - Push return address onto stack
- `ret` - Pop return address into RAX

### Register Operations
- `mov <register> <value>` - Move value into register
- `mov [rsp+offset] <value>` - Write to stack at RSP + offset
- `mov [rsp-offset] <value>` - Write to stack at RSP - offset

## Examples

```
push 10
push 20
pop rax
call deadbeef
ret
mov rbx ff
mov [rsp-1] 1234
```


## Usage

Run the executable and enter commands at the prompt. The stack and register state updates after each command.
