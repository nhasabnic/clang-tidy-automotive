# Clang-Tidy Automotive

This repository provides a collection of Clang-Tidy checks inspired by the 
goals and safety principles behind coding standards such as MISRA C:2023 
and MISRA C:2012.

The project does **not** reproduce any MISRA copyright content, including 
rule names, rule texts, or associated documentation. All the MISRA mapping
is put into a separate repository, see
[Clang-Tidy MISRA](https://github.com/PeterHallonmark/clang-tidy-misra)
for more information.

## Getting Started

To build clang-tidy Automotive, follow these steps:

### Prerequisites 

Clang 20 (or compatible version)

### Setup Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/PeterHallonmark/clang-tidy-automotive.git
   cd clang-tidy-automotive
   ```

#### Building locally

2. Run the following setup scripts to build Clang-Tidy Automotive:
   ```bash
   ./download.sh
   ./setup.sh
   ./configure.sh
   ./build.sh
   ```

#### Building inside docker

```
docker build . -t cm-clang-tidy-automative
```

This should complete successfully.

**Note:** The scripts will need to be adjusted to use a Docker container in
the future. This is part of the TODO list.

## Usage

To use the Automotive support in clang-tidy, enable the rules automotive-* 
when using clang-tidy. The example below assumes the avoid-goto.c test file 
and the root directory of clang-tidy-automotive.

### Running locally

   ```bash
   ./build/bin/clang-tidy --checks="automotive-avoid-goto" test/checkers/automotive/statement/avoid-goto.c -- 
   ```

### Running in docker
```
docker run -it cm-clang-tidy-automative bash
```

Then try `clang-tidy` command above. The output that I got is:

```
 ./build/bin/clang-tidy --checks="automotive-avoid-goto" test/checkers/automotive/statement/avoid-goto.c -- 
1836 clang-diagnostic-c23-extensions
8821 automotive-avoid-goto
8821 automotive-avoid-goto
6 warnings generated.
/home/test/checkers/automotive/statement/avoid-goto.c:6:3: warning: avoid goto statement [automotive-avoid-goto]
    6 |   goto Label1;    /* Not compliant */
      |   ^
/home/test/checkers/automotive/statement/avoid-goto.c:9:1: warning: label at end of compound statement is a C23 extension [clang-diagnostic-c23-extensions]
    9 | }
      | ^
/home/test/checkers/automotive/statement/avoid-goto.c:13:3: warning: avoid goto statement [automotive-avoid-goto]
   13 |   goto Label2;    /* Not compliant */
      |   ^
Suppressed 3 warnings (3 with check filters).
```

See [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) for more information.

## License

The repository follows LLVM's license structure to make it easier to upstream
changes to the LLVM project if and when that happens. :)

## Future Improvements

Move setup scripts to a Docker container for easier setup and environment
management.

## Contributing

Feel free to open issues or pull requests if you'd like to contribute to
this project. Contributions are always welcome!

**Note:** This project is not officially associated with MISRA or LLVM.
Any contributions or code changes are not officially endorsed by MISRA or 
LLVM.
