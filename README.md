# Python Native Extension Debugging Demo

Python provides `pdb` module to debug Python application, just
like `gdb` for native code (built from C/C++).

For Python application that have native extension,
is not trivial to break/step/continue in Python and in C code
at the same time.

Since that the control flow of Python native extension is not
managed by Python interpreter, we need another debugger to debug
the Python process it self (which run our application in `pdb` module).

## Install

The native extension CPython header files to be build,
installed the development files based on actual environment.

```sh
# for example, for Python 3.12 installed directly from apt in Ubuntu
apt install python3.12-dev
```

```sh
# (optional) setup virtual environment

pip install .  # install the extension
```

## Usage - CLI

```sh
gdb --args python -m pdb main.py
```

```text
(gdb) break add_func
(gdb) break sub_func
(gdb) run
...

(Pdb) break main
...

(Pdb) cont
...
-> c = calculator.add(2, 3)
(Pdb) step

Breakpoint 1, add_func ..
(gdb) step
(gdb) step
(gdb) step
(gdb) print c
$1 = 5

(gdb) cont
...
-> d = calculator.sub(c, 1)
(Pdb) step
...

(Pdb) quit
(gdb) quit
```

## Usage - VSCode

VSCode provides a friendlier UI interface for this debugging process.
(Install `Python` and `C/C++` extension from the marketplace.)

First, create a `Python Debugger > Python File` debug profile for `main.py`

Something like

```json
        {
            "name": "Python Debugger: Main",
            "type": "debugpy",
            "request": "launch",
            "program": "${workspaceFolder}/main.py",
            "console": "integratedTerminal"
        }
```

Create a `C/C++: (gdb) Attach` profile, and change the program to the Python interpreter.

Something like

```json
        {
            "name": "(gdb) Attach to Python",
            "type": "cppdbg",
            "request": "attach",
            "program": "${command:python.interpreterPath}",
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "Set Disassembly Flavor to Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ]
        },
```

After setting up this profiles, start the Python debugging session
(add some breakpoint or add a `input()` call so it won't exit immediately).
Then, we attach to this Python (debugger) process by the gdb debugging session.

VSCode will prompt a list of available processes for we to attach,
search for `main.py`, usually there will be two process, choose the most child one
(the one with larger PID).

Now we can debug the Python code and native extension at the same time.
Just remember to add the breakpoint. :D

## Appendix

If it turns out that gdb can not attach to the process, try

```sh
sysctl -w kernel.yama.ptrace_scope=0  # root permission required
```
