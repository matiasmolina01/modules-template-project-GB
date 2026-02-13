# Project Template README

## Overview

This project template is designed to facilitate modular C development with CMake and VS Code 
with github source control and testing with actions. It enables individual module development,
isolated testing, and easy integration into a complete environment that creates several 
executables (one to run the program, and a separate one to test each module in isolation) 
in separete run and debug modes. So the project has several main functions.

The testing is integrated with the github actions so it is automatically run everytime 
push or pull request is done. The output logs of automatic runs are stored in the logs 
directory. The log files are named with the time to avoid overwritting the different runs files.

---

## Project Structure
```
/ (root)
├── CMakeLists.txt     # Top-level CMake configuration (compiles several independent programs)
├── cmake-kits.json    # CMake kits for VS Code to select toolchains
└── .github/      # Github configurations
│ ├── workflows         # Github workflows for testing when push and PR
├── .vscode/      # Configurations to run VS code
│ └── cmake-kits.json  # To ensure gcc path for cmake (update your path)
│ └── extensions.json  # Recommended extensions (install when recommendations pop up in your VS code installation)
│ ├── launch.json      # Debug configurations of command line arguments (create your run configurations)
│ ├── settings.json    # VS Code workspace settings for CMake and build (update your paths and modules)
│ └── tasks.json       # Build and run tasks for VS Code: Add/modify tasks as you need
├── src/          # The project source code
│ ├── main.c           # Main program 
│ ├── main.h           # Program data structure and common project definitions
│ ├── alphabet/
│ │ ├── 
│ │ ├── 
│ │ └── CMakeLists.txt
│ ├── automata/
│ │ ├── automata.c
│ │ ├── automata.h
│ │ └── CMakeLists.txt
│ ├── counter/
│ │ ├── counter.c
│ │ ├── counter.h
│ │ └── CMakeLists.txt
│ ├── error_handler/
│ │ ├── error_handler.c
│ │ ├── error_handler.h
│ │ └── CMakeLists.txt
│ ├── init/
│ │ ├── init.c
│ │ ├── init.h
│ │ └── CMakeLists.txt
│ ├── input_handler/
│ │ ├── input_handler.c
│ │ ├── input_handler.h
│ │ └── CMakeLists.txt
│ ├── module_args/     # Module arguments
│ │ ├── module_args.c  # Module arguments source
│ │ ├── module_args.h  # Module arguments header
│ │ └── CMakeLists.txt # Module arguments build instructions (separate to avoid conflicts)
│ └── output_handler/  # Module 2 example template (create more modules as you need)
│ │ ├── module_2.c     # Module 2 source
│ │ ├── module_2.h     # Module 2 header
│ └── CMakeLists.txt   # Module 2 build instructions (separate to avoid conflicts)
│ ├── utils.c/         # Utility library (module example without independent CMakeList)
│ ├── utils.h/         # 
├── tests/        # Independent programs (mains) for testing modules individually
│ ├── test_module_args.c # Independent program to test the module_args
│ ├── test_module_args.h # Definitions needed just for testing module_args
│ ├── test_module_automata.c # Independent program to test the module_automata
│ ├── test_module_automata.h # Definitions needed just for testing module_automata
│ ├── test_module_2.c    # Independent program to test the module_2
│ ├── test_module_2.h    # Definitions needed just for testing module_2
│ ├── test_module.h      # Common testing definitions to all testing modules
│ └── CMakeLists.txt     # Test executables build instructions (generates the different executables)
└── build/      # Directory for CMake build output (ignored in git commits, different for each computer)
└── logs/       # Directory with the output logs to track execution (can ignore in git commits)
```

---

## Tools and Configuration

### CMake

- **CMake** is used as the build system generator.
- The project uses a **modular CMake setup**, with one `CMakeLists.txt` per module for isolated compilation.
- The top-level `CMakeLists.txt` ties all modules together and builds the main executable.
- Unit tests for each module are built as separate executables under `tests/`.

### VS Code Extensions

Recommended extensions for a smooth experience:

- **CMake Tools** (twxs.cmake) — CMake integration and build support.
- **C/C++** (ms-vscode.cpptools) — IntelliSense, debugging, and code browsing.
- **Code Runner** (formulahendry.code-runner) — quick code execution.
- **GitHub Copilot** (GitHub.copilot) — AI-assisted coding.
- **Git Graph** (mhutchie.git-graph) — visual git history.

### CMake Kits (`cmake-kits.json`)

- Preconfigures the MSYS2 UCRT64 toolchain:
  - Compiler: `gcc.exe` from MSYS2.
  - Generator: `MinGW Makefiles`.

This allows to select the proper compiler and generator in VS Code easily.

---

## Building the Project

1. Open the project folder in VS Code.
2. Select the CMake Kit `MSYS2 UCRT64 (preconfigured)` via the CMake extension.
3. Configure the project (usually done automatically on open).
4. Build the project using the **CMake Build** command or the default build task.
5. Run or debug the main executable or individual module tests from the VS Code Run panel or tasks.

---

## Running and Debugging

- Debug configurations (`launch.json`) are provided for:
  - The main program (`modules_template_main.exe`).
  - Each module test executable (`test_module_args.exe`, `test_module_2.exe`).
- These use **GDB** from the MSYS2 toolchain and are preconfigured for easy debugging in VS Code.

---

## How to Extend the Template

- Add new modules by creating a new folder under `src/` with its own `CMakeLists.txt`.
- Add corresponding test files under `tests/` and update the tests `CMakeLists.txt`.
- Extend `launch.json` and `tasks.json` to include debugging and build tasks for new modules.

---

## Notes

- The `build/` directory is ignored by git to keep build artifacts out of source control.
- The `logs/` directory can be ignored by git depending if you want to share your output files to the team.
- Environment assumes MSYS2 installed with UCRT64 toolchain available and added to PATH.
- The configuration aims for minimal manual setup to reduce friction between team contributors.
- Each module functions are written following the same name structure:
  - **Function names**: have the initial letter of the module and if the name contains multiple words, they will be separated by underscores as well.
  - **Struct names**: will start with an uppercase letter and there will be no underscores separating the multiple words each struct might have, we will differentiate different words by typing the first letter in uppercase 

# Modules
## Alphabet


## Automata
The automata module implements a deterministic finite automaton **DFA** used by the scanner.

Its responsibility is to interact with the Scanner module by providing the following functionalities:
- **execute state transitions** of an automaton
- **indicate if the state is accepting state**
- **tells if can continue with lookahead**
- **reset the automaton**

#### Functions

| FUNCTION | DESCRIPTION | INTERESTED MODULES | RETURN |
|----------|------------|-------------------|--------|
| `a_create_automata(...)`| Function to create an automata with the parameters. | SCANNER | `Automata*` --> pointer to the created automata. <br>`NULL` --> failure (invalid parameters or memory allocation failure). |
| `int a_process(Automata *automata, char c, Lookahead *lookahead)` | Processes one transition step of the automaton. Consumes `c`, checks whether it can continue using the provided `Lookahead`, and determines whether to continue, accept, or fail. | SCANNER | `A_CONTINUE (0)` – automaton can continue.<br>`A_ACCEPT (1)` – Current character consumed, cannot continue, but the current state is accepting.<br>`A_FAIL (-1)` – Cannot consume the current character or stopped in a non-accepting state. |
| `int a_mapping_alphabet(Automata *automata, char c)` | Maps a character to the corresponding column in the compressed transition table of the automaton. | --- | `col` → column index of transition table.<br>`A_FAIL (-1)` → character not found or invalid column. |
| `int a_next_state(Automata *automata, char c)` | Computes the next state from the current state using character `c`. | --- | `new_state` → next valid state.<br>`0` → character not accepted.<br>`A_FAIL (-1)` → invalid state or failure. |
| `int a_accepting_state(Automata *automata, int state)` | Checks whether a given state is an accepting state. | --- | `1` → accepting state.<br>`0` → not accepting.<br> |
| `int a_advance_automata(Automata *automata, char c)` | Advances the automaton one step if the character is accepted, updating the current state. | --- | `1` → character accepted and state advanced.<br>`0` → character not accepted.<br>`A_FAIL (-1)` → failure. |
| `int a_lookahead_process(Automata *automata, Lookahead *lookahead)` | Processes the lookahead character to determine if the automaton can continue. | --- | `1` → valid transition exists (can continue).<br>`0` → no valid transition exists..<br>`A_FAIL (-1)` → failure. |
| `void a_reset_automata(Automata *automata)` | Resets the automaton to its initial state. | SCANNER | No return value. |
|`void a_destroy_automata(Automata *automata)`|Function to free the memory of the automata.| SCANNER | No return value. |

#### Design Notes
- State `0` is always the initial state.
- No valid transition returns to state `0`.
- Lookahead does not modify the automaton state.

#### Structs

------
##### AlphabetSymbol

------

| Field | Type | Description |
|-------|------|------------|
| `name` | `char` | Character that represents a symbol of the automaton alphabet. |
| `col` | `int` | Column index in the compressed transition table corresponding to the symbol. |

------

#### AcceptingState

------

| Field | Type | Description |
|-------|------|------------|
| `flag` | `int` | Indicates whether the state is accepting (1 = accepting, 0 = not accepting). |
| `list_of_category` | `char[MAXLEN]` | Category or token type associated with the accepting state. |

------

#### Automata

------

| Field | Type | Description |
|-------|------|------------|
| `numsymbols` | `int` | Number of symbols in the alphabet. |
| `numstates` | `int` | Number of states in the automaton. |
| `numcols` | `int` | Number of columns in the compressed table. |
| `alphabet` | `AlphabetSymbol[]` | Array of alphabet symbols. |
| `transitions` | `int[][]` | Transition table (state × symbol → next state). |
| `initial_state` | `int` | Initial state of the automaton. |
| `current_state` | `int` | Current active state during execution. |
| `accept` | `AcceptingState[]` | Array indicating which states are accepting and their categories. |

------

#### Global Constants

| Name | Type | Value | Description |
|------|------|-------|------------|
| `A_FAIL` | `#define` | -1 | Indicates failure in automata operations. |
| `A_CONTINUE` | `#define` | 0 | Indicates that the automaton can continue processing. |
| `A_ACCEPT` | `#define` | 1 | Indicates successful acceptance. |

------
------

## Counter

## Error Handler

## Init

## Input Handler

## Module Args

## Output Handler

## Scanner

## Token Handler



