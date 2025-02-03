# MarkWareVCMake

[![Ubuntu](https://github.com/tomasmark79/MarkWareVCMake/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/tomasmark79/MarkWareVCMake/actions/workflows/ubuntu.yml)
[![MacOS](https://github.com/tomasmark79/MarkWareVCMake/actions/workflows/macos.yml/badge.svg)](https://github.com/tomasmark79/MarkWareVCMake/actions/workflows/macos.yml)
[![Windows](https://github.com/tomasmark79/MarkWareVCMake/actions/workflows/windows.yml/badge.svg)](https://github.com/tomasmark79/MarkWareVCMake/actions/workflows/windows.yml)  

## Overview

MarkWareVCMake is a comprehensive, modern C/C++ project template designed for cross-platform development in Visual Studio Code. The template provides a robust foundation for both standalone executables and libraries, incorporating industry best practices and modern build tools.

### Key Features

- Cross-platform compatibility (Linux, macOS, Windows)
- Integrated build system with CMake
- Advanced debugging capabilities
- Sanitizer support through CMake options
- Conan package management integration
- Cross-compilation support
- SSH and WSL compatibility
- Automated workflow through Visual Studio Code tasks

https://github.com/user-attachments/assets/f02a2304-37d3-4214-9019-4119619f4fa2

## System Requirements

### Essential Tools

- **Visual Studio Code** with C++ extension
- **Python 3** (managed via Pyenv)
- **Conan 2** for dependency management
- **CMake** (latest version recommended)
- **Code Formatters**:
  - Clang Format
  - CMake Format

### Integrated Technologies

- CPM.cmake for lightweight dependency management
- CPM.license for license management
- ModernCppStarter integration
- GitHub Actions workflows for continuous integration

## Getting Started

### Installation Steps

#### Linux and MacOS

```bash
# Update system packages
sudo apt update && sudo apt upgrade -y
sudo apt install cmake python3-pip curl git libssl-dev libbz2-dev libcurses-ocaml-dev build-essential gdb libffi-dev libsqlite3-dev liblzma-dev libreadline-dev libtk-img-dev

# Configure Pyenv
curl https://pyenv.run | bash
pyenv install 3.9.2
pyenv virtualenv 3.9.2 env392
pip install --upgrade pip

# Install Conan
pip install conan
conan profile detect --force
```

#### Windows Setup

Native Windows:
```powershell
# Install Pyenv
[Follow Pyenv-win installation guide]
pyenv install 3.9.2
pyenv global 3.9.2
pyenv local 3.9.2
pip install --upgrade pip

# Install Conan
pip install conan
conan profile detect --force
```

WSL Setup:
```powershell
wsl --install
wsl --install Debian
wsl --set-default-version 2
```

### Project Setup

1. Clone the repository:
```bash
git clone https://github.com/tomasmark79/MarkWareVCMake
cd MarkWareVCMake/
```

2. Optional: Customize project names:
```bash
python SolutionRenamer.py VCMLib MyLibrary VCMStandalone MyStandalone
```

3. Launch VSCode and configure shortcuts:
```bash
code .
```

## Development Workflow

### Keyboard Shortcuts

- `F5`: Launch debugger
- `F7`: Quick build
- `Shift+F7`: Task menu
- `Shift+Ctrl+S`: Run all build scenarios

### Build Configuration

- Supports multiple build types: Debug, Release, RelWithDebInfo, MinSizeRel
- Configurable CMake options for:
  - Shared/static libraries
  - Static runtime linking
  - Various sanitizer options

### Cross-Compilation Support

The template includes preconfigured support for:
- x86_64-clang-linux-gnu
- x86_64-w64-mingw32
- aarch64-linux-gnu

## Additional Features

### Automated Tasks

- Clean build directories
- Dependency installation
- CMake configuration
- Build management
- License collection
- Artifact management
- Code formatting
- Diagnostic tools

### Project Maintenance

- Solution renaming utility
- Automatic upgrade functionality
- Comprehensive logging system

## License

This project is licensed under the MIT License.