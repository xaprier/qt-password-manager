<h1 align="center">
  🚀 qt-password-manager
</h1>

<p align="center">
  <a href="https://github.com/xaprier/qt-password-manager/blob/main/LICENSE" target="blank">
    <img src="https://img.shields.io/github/license/xaprier/qt-password-manager" alt="license" />
  </a>
</p>

<b>qt-password-manager</b> is a password manager to keep your passwords in local as encrypted with a master password using OpenSSL AES-256

### 🛠️ Build Instructions for Linux/UNIX

Clone the repository to your directory

```sh
git clone --recursive https://github.com/xaprier/qt-password-manager.git
```

Enter the direcotry of the source code

```sh
cd qt-password-manager/
```

Build the makefile with CMake, if you don't have cmake you have to install it.

```sh
cmake -G "Unix Makefiles" -B "build"
```

Than our Makefile is ready for build the source code. We have to access the directory of makefile and run make.

```sh
cd build && make -j$(nproc)
```

Than our compiled binary is ready for run in the directory of the makefile with the name "qt-password-manager"
You can run the sample program with this command

```sh
./qt-password-manager
```

### 📚 Dependencies

- CMake(Building project)
- GCC/Clang(Compiler for building project)
- Qt(GUI and Core libraries, 5 and later)
- OpenSSL(Library for encryption, 1.1 and later)
- Git(Just for cloning repository)
