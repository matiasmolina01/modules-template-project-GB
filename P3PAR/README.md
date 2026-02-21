# P2LEX - Lexical Analyzer (Scanner)

## Overview

**P2LEX** is a modular C11 lexer (lexical analyzer) that tokenizes source code for a reduced C-like language. It uses finite state automata to recognize keywords, identifiers, numbers, operators, literals, and special characters in a single-pass scan with lookahead.

The project demonstrates:
- **Modular design** with independent, testable modules
- **Finite state automata** for pattern recognition
- **CMake build system** for portable compilation
- **Unit testing** with CTest (automated via GitHub Actions)
- **Proper EOF and lookahead handling** for robust lexical analysis

---

## Features

- **Multiple Token Categories**: Keywords, identifiers, numbers, operators, special chars, literals
- **Parallel Automata**: Six finite state automata run simultaneously for efficient recognition
- **Single-Character Lookahead**: Disambiguates token boundaries without requiring backtracking
- **Modular Architecture**: Each module is independently testable and reusable
- **Robust Error Handling**: Comprehensive error codes and reporting system
- **Operation Counting**: Optional debug feature to track lexer performance (COMP, IO, GEN)
- **Cross-Platform**: Builds on Windows, macOS, and Linux with CMake

## Recognized Token Categories

| Category | Examples |
|----------|----------|
| **KEYWORD** | `if`, `int`, `void`, `char`, `while`, `else`, `return` |
| **IDENTIFIER** | `x`, `printf`, `myVar`, `count` |
| **NUMBER** | `13`, `0`, `999` |
| **OPERATOR** | `=`, `+`, `>`, `*` |
| **SPECIALCHAR** | `(`, `)`, `[`, `]`, `{`, `}`, `;`, `,` |
| **LITERAL** | `"hello"`, `"test string"` |
| **NONRECOGNIZED** | Unmatched characters |

---

## Quick Start

### Build

```bash
cd P2LEX
mkdir -p build && cd build
cmake ..
cmake --build . --config Debug
```

### Run Lexer

```bash
./modules_template_main.exe input.c
# Output: input.cscn (tokens)
```

### Run Tests

```bash
ctest --output-on-failure
```

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
│ ├── language/
│ │ ├── language.h
│ │ ├── language.c
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

## Language

The language module defines the alphabet symbols and finite state transition tables for each token category. It centralizes all language-specific definitions.

#### Responsibilities
- Define alphabet symbols for each automaton
- Provide transition matrices for each DFA
- Define accepting states for each token category
- Maintain grammar rules in data structures

#### Data Structures

- **`keyword_alphabet`** - 16 symbols (i, f, n, t, e, l, s, w, h, r, u, c, a, v, o, d)
- **`identifiers_alphabet`** - 62 symbols (a-z, A-Z, 0-9)
- **`numbers_alphabet`** - 10 symbols (0-9)
- **`operators_alphabet`** - 4 symbols (=, +, >, *)
- **`special_char_alphabet`** - 8 symbols ((, ), [, ], ;, {, }, ,)
- **`literals_alphabet`** - 63 symbols (a-z, A-Z, 0-9, ")

#### Automata State Counts

| Automaton | States | Symbols | Notes |
|-----------|--------|---------|-------|
| Keywords | 23 | 16 | Recognizes reserved words |
| Identifiers | 3 | 62 | Recognizes variable/function names |
| Numbers | 3 | 10 | Recognizes integer literals |
| Operators | 3 | 4 | Recognizes arithmetic/assignment ops |
| Special Chars | 3 | 8 | Recognizes punctuation |
| Literals | 4 | 63 | Recognizes quoted strings |

#### Key Functions

- No exported functions (data-only module)
- Provides extern arrays: `*_alphabet[]`, `*_transitions[][]`, `*_accepting_states[]`

#### Design Pattern

- **Compressed transition tables**: Columns indexed by symbol position in alphabet
- **Dead states**: State 22 (keywords) or state 2/3 (others) as sink
- **State 0**: Always initial state
- **Accepting states**: Flag-based with associated token category

---

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
| `category` | `TokenCategory` | Category or token type associated with the accepting state. |

---

## Module Implementation Details

### Scanner Algorithm

The scanner operates as a state machine:

1. **Initialize**: Reset all automata, read first character
2. **Main Loop** (while not EOF):
   - Get lookahead character
   - Run all automata in parallel
   - Check responses:
     - If any automata accepts and lookahead blocks continuation → Accept token
     - If no automata can continue → Reject token  
     - Otherwise → Continue reading
   - Append lookahead to current token
3. **Finalize**: Output token list

### Automata Response Codes

```c
#define A_CONTINUE 0   // Can continue processing (consumed char, lookahead viable)
#define A_ACCEPT 1     // Cannot continue with lookahead, but current state accepts
#define A_FAIL -1      // Cannot consume character or in dead state
```

### Token Categories Enum

```c
typedef enum {
    CAT_NUMBER,        // Integer literals (0-9)+
    CAT_IDENTIFIER,    // Variable/function names
    CAT_KEYWORD,       // Reserved words
    CAT_LITERAL,       // String literals
    CAT_OPERATOR,      // Operators
    CAT_SPECIALCHAR,   // Punctuation
    CAT_NONRECOGNIZED  // Unknown tokens
} TokenCategory;
```

---

## Building & Testing

### Platform Requirements

| Platform | Compiler | Status |
|----------|----------|--------|
| Windows | MSVC, MinGW | ✓ Tested |
| macOS | Clang | ✓ Expected |
| Linux | GCC | ✓ Expected |

### Build Configuration

```bash
# Debug (default)
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# Release (optimized)
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

### Test Execution

```bash
# All tests
cd build && ctest --output-on-failure

# Specific test
ctest --test-dir build -R test_module_automata -VV

# Verbose output
ctest --test-dir build --output-on-failure -V
```

---

## Common Issues & Solutions

### Keywords Recognized as Identifiers

**Cause**: Multiple automata accepting same lexeme; identifier automata wins  
**Solution**: Add keyword priority in `s_check_responses()` to prefer `KEYWORDS_AUTOMATA`

### Token Missing or Incomplete

**Cause**: EOF handling bug in lookahead  
**Solution**: Ensure `i_read_char()` returns `EOF` (not NULL) and scanner breaks on EOF

### Build Failures

**Cause**: CMake path or toolchain issues  
**Solution**: 
```bash
rm -rf build
mkdir build && cd build
cmake .. -G "Unix Makefiles"  # or -G "Visual Studio 17 2022"
cmake --build .
```

---

## Performance Notes

- **Time Complexity**: O(n) where n = input characters (single pass)
- **Space Complexity**: O(t) where t = number of tokens
- **Lookahead**: Single character (no buffering)
- **Parallel Automata**: Six DFAs run simultaneously → O(1) per character

---

## Contributing

To add support for new token categories:

1. **Add to `language.h`**:
   - Define alphabet symbols
   - Create transition table
   - Add accepting states array

2. **Add to `global_context.c`**:
   - Initialize automata in `gc_init_automatas()`
   - Increment `NUM_AUTOMATAS`

3. **Add to `language.h` header**:
   - Export transition tables and alphabets

4. **Add tests** in `tests/test_module_automata.c`

---

## License

Educational project for compiler course (Team GB).

---

**Last Updated**: February 2026  
**Status**: ✓ Lexer complete | ✓ Keywords fixed | ✓ All modules tested

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

---

## Counter

Optional performance instrumentation module for tracking lexer operations. Conditional compilation via `#define COUNTCONFIG`.

#### Features

- **Count Types**:
  - `COMP` - Comparisons (character matching, state checks)
  - `IO` - I/O operations (file reads, output writes)
  - `GEN` - General operations (allocations, resets)

- **Output**: Debug file (`.dbgcnt`) or main output file
- **Logging**: Per-operation logging with partial/total counts
- **Summary**: Final count report at program end

#### Key Functions

| Function | Purpose |
|----------|----------|
| `c_count_init(filename, output)` | Initialize counters and log file |
| `c_count_log(line, func, type, inc, local)` | Log operation with counts |
| `c_count_print_summary()` | Print final count report |

#### Usage

```c
#define COUNTCONFIG 1      // Enable counting
#define COUNTOUT 1         // Output to main file
#define DBGCOUNT 0         // Create separate count file

// In main:
c_count_init(input_file, stdout);
// ... program runs ...
c_count_print_summary();

// In functions:
COUNTCOMP(1);  // Increment comparison count
COUNTIO(bytes_read);
COUNTGEN(1);
```

#### Macros

```c
#define COUNTCOMP(n)   COUNT_COMP += (n)
#define COUNTIO(n)     COUNT_IO += (n)
#define COUNTGEN(n)    COUNT_GEN += (n)
```

---

## Error Handler

Centralized error reporting and handling system with predefined error codes and messages.

#### Error Code Ranges

| Range | Module | Count |
|-------|--------|-------|
| 100-199 | Input Handler | 8 errors |
| 200-299 | Scanner | 6 errors |
| 300-399 | Automata | 15 errors |
| 400-499 | Token Handler | 9 errors |
| 500-599 | Output Handler | 6 errors |
| 600-699 | Counter | 1 error |
| 700-799 | Module Args | 1 error |
| 800-899 | Global Context | 2 errors |

#### Key Functions

| Function | Purpose |
|----------|----------|
| `e_error_report(ErrorCode)` | Report error with message lookup |
| `e_error_handler()` | Main error handling routine |

#### Error Structure

```c
typedef struct Error {
    ErrorCode code;           // Unique error identifier
    ErrorStep step;           // Processing phase (PARSER, SCANNER, PREPROCESSOR)
    const char *message;      // Human-readable error message
} Error;
```

#### Common Error Codes

```c
ERR_I_FILE_NOT_FOUND = 100        // Input file missing
ERR_I_INVALID_PATH = 107          // Invalid file path
ERR_S_AUTOMATA_INIT_FAILURE = 201 // Automata initialization failed
ERR_A_AUTOMATA_NULL = 311         // Null automata pointer
ERR_T_MEM_ALLOC_TOKEN = 400       // Token allocation failed
ERR_O_FILE_OPEN_FAILURE = 500     // Output file open failed
ERR_MA_INVALID_ARG_NUMBER = 700   // Wrong argument count
```

#### Debug Tracing

```c
#define TRACE_ERROR_HANDLER   // Enable trace output
#define TRACE_ERROR_REPORT    // Enable error reporting
```

---

## Input Handler

Manages character-by-character file I/O with line and column tracking.

#### Key Functions

| Function | Purpose | Return |
|----------|---------|--------|
| `i_create()` | Allocate Input structure | `Input*` |
| `i_open_input(input, path)` | Open file for reading | 1 = success, exits on failure |
| `i_read_char(input)` | Read next character | `char` (0-255) or `EOF` |
| `i_close_input(input)` | Close file and reset | 1 = success |
| `i_is_eof(input)` | Check EOF status | 1 = EOF, 0 = not EOF |

#### Data Structure

```c
typedef struct Input {
    FILE *input_file;   // Open file pointer
    int is_eof;         // EOF flag (IS_EOF or NO_EOF)
    int line_number;    // Current line (1-indexed)
    int column;         // Current column (0-indexed)
} Input;
```

#### Character Reading Algorithm

1. Check if file is open
2. Increment column counter
3. Read character with `fgetc()`
4. On EOF: set flag and return `EOF`
5. On newline: increment line, reset column
6. Return character or `EOF`

#### Constants

```c
#define MODE_READ "r"
#define IS_EOF 1
#define NO_EOF 0
```

---

## Module Args

Command-line argument processing module for input file validation.

#### Key Functions

| Function | Purpose |
|----------|----------|
| `process_arguments(argc, argv)` | Parse and validate CLI arguments |
| `args_free(args)` | Free allocated argument structure |
| `print_arguments(args)` | Debug print argument values |

#### Arguments Structure

```c
typedef struct Arguments {
    char *input_path;   // Path to input file
} Arguments;
```

#### Validation

- Minimum argc check: `argc >= 2`
- File path validation: non-NULL, non-empty
- Error reporting: `ERR_MA_INVALID_ARG_NUMBER`

#### Usage

```bash
./modules_template_main.exe input.c
# argv[0] = "modules_template_main.exe"
# argv[1] = "input.c" (args->input_path)
```

---

## Output Handler

Writes token list to output file in standard format.

#### Key Functions

| Function | Purpose |
|----------|----------|
| `o_output_handler(token_list, input_path)` | Write tokens to file |

#### Output Format

**Release Format** (default):
```
<lexeme, CATEGORY> <lexeme, CATEGORY> ...
```

**Debug Format** (optional):
```
<lexeme="...", category=..., line=..., column=..., length=..., capacity=...>
```

#### Output Filename Generation

```
Input:  input.c
Output: input.cscn
        ↓
    Appends ".scn" suffix
```

#### Implementation

```c
int o_output_handler(const TokenList *list, const char *input_filename) {
    // Build output filename
    char output_filename[512];
    snprintf(output_filename, sizeof(output_filename), 
             "%sscn", input_filename);
    
    // Open file
    FILE *fp = fopen(output_filename, "w");
    
    // Write tokens (release format)
    tl_token_list_print_release(fp, list);
    
    // Close file
    fclose(fp);
    return 0;
}
```

#### Error Handling

- Returns -1 on failure
- Validates token list and filename
- Reports `ERR_O_FILE_OPEN_FAILURE` if file open fails

---

## Scanner

Main lexical analysis engine using parallel finite state automata with single-character lookahead.

#### Key Functions

| Function | Purpose |
|----------|----------|
| `s_scanner(global_context)` | Main scanning loop |
| `s_run_automatas(...)` | Execute all automata in parallel |
| `s_check_responses(...)` | Process automata responses |
| `s_accept_token()` | Finalize token and add to list |
| `s_reject_token()` | Reject token (mark as NONRECOGNIZED) |
| `s_reset_initial_state()` | Reset for new token |
| `s_get_lookahead()` | Read lookahead character |
| `s_is_separator()` | Check if lexeme is whitespace |

#### Scanning Algorithm

```
1. Initialize:
   - Reset all automata
   - Read first character
   - Create initial token

2. Main Loop (while not EOF):
   - Get lookahead character
   - Run all 6 automata in parallel
   - Analyze responses:
     * A_CONTINUE: At least one automata can continue
     * A_ACCEPT: Automata accepts, lookahead blocks
     * A_FAIL: No automata can continue
   - Accept/reject token as needed
   - Move to next character

3. Cleanup:
   - Output final token list
```

#### Constants

```c
#define A_CONTINUE 0    // Can continue processing
#define A_ACCEPT 1      // Accept token
#define A_FAIL -1       // Reject token
#define HAS_LOOKAHEAD 1
#define NO_LOOKAHEAD 0
```

#### Decision Logic

```
if (count_continue > 0)
    → Continue reading
else if (any_accept)
    → Accept token with accepted automata category
else
    → Reject as NONRECOGNIZED
```

---

## Token Handler

Token creation, management, and output formatting.

#### Key Functions

| Function | Purpose |
|----------|----------|
| `t_token_create(line, col)` | Allocate token with position |
| `t_token_append_char(token, c)` | Add character to lexeme |
| `t_token_update_category(token, cat)` | Set token category |
| `t_token_destroy(token)` | Free token memory |
| `tl_token_list_init()` | Create empty token list |
| `tl_token_list_add(list, token)` | Append token to list |
| `tl_token_list_destroy(list)` | Free entire token list |
| `t_token_print_release()` | Format token for output |
| `t_token_print_debug()` | Format token for debugging |
| `tl_token_list_print_release()` | Output all tokens (release) |
| `tl_token_list_print_debug()` | Output all tokens (debug) |

#### Data Structures

```c
typedef struct Token {
    char *lexeme;           // Token text (dynamically allocated)
    size_t length;          // Current lexeme length
    size_t capacity;        // Allocated buffer size
    TokenCategory category; // Token type
    int line;               // Starting line number
    int column;             // Starting column number
} Token;

typedef struct TokenNode {
    Token token;
    struct TokenNode *next; // Linked list
} TokenNode;

typedef struct TokenList {
    TokenNode *head;        // First token
    TokenNode *tail;        // Last token
    int size;               // Total tokens
} TokenList;
```

#### Token Categories

```c
typedef enum TokenCategory {
    CAT_NUMBER,        // 0
    CAT_IDENTIFIER,    // 1
    CAT_KEYWORD,       // 2
    CAT_LITERAL,       // 3
    CAT_OPERATOR,      // 4
    CAT_SPECIALCHAR,   // 5
    CAT_NONRECOGNIZED  // 6
} TokenCategory;
```

#### Lexeme Buffer Management

- **Initial capacity**: 16 bytes
- **Growth**: Double capacity when full
- **Dynamic allocation**: Via `malloc()` / `realloc()`
- **Null termination**: Always maintained

#### Output Formats

**Release**:
```
<lexeme, CATEGORY>
```

**Debug**:
```
<lexeme="value", category=KEYWORD, line=5, column=12, length=2, capacity=16>
```



