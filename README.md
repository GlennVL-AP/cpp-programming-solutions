# cpp-programming-solutions

Solutions for C++ Programming labo exercises.

## Devcontainer

Basic C++ devcontainer with cmake, compiler warnings, clang-tidy, and clang-format.

### Installed tools

* lldb
* clang
* cmake
* clang-tidy
* clang-format

### Supported IDEs

* vscode
* clion

## How to use?

### vscode

* Configure/build the project using the buttons in the vscode status bar
* Select the target to run in vscode

```text
View > Command Palette... > CMake: Set Launch/Debug Target
```

* Run/Debug the selected target executable using the buttons in the vscode status bar

### clion

1. **Settings > Build, Execution, Deployment > Toolchains**
   * **CMake**: Change from **Bundled** to **Custom CMake executable** with value **/usr/local/bin/cmake**
   * **Debugger**: Change from **Bundled GDB** to **Custom LLDB executable** with value **/usr/bin/lldb**
2. **Settings > Build, Execution, Deployment > CMake**
   * Delete **Debug** preset
   * Enable **clang-debug** and **clang-release** presets
3. **Settings > Build, Execution, Deployment > Dynamic Analysis Tools > Sanitizers**
   * **LeakSanitizer**: Set **LSAN_OPTIONS** field to **detect_leaks=0** (disables leak detection, required for running with the debugger)
