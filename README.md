<h1 align = center> CCpy </h1>

<h3 align = center> Pre-Tested C Codebase for KTU University Students</h3>

CCpy is a repository that provides access to a collection of pre-tested, working C programs designed specifically for KTU (Kerala Technological University) students. This repository aims to assist students in learning and understanding various concepts in C programming, as well as providing practical examples for assignments, projects, and exams.

## Table of Contents

- [Features](#features)
- [Navigation](#navigation)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Pre-Tested Codebase**: All programs in this repository have been thoroughly tested to ensure they work as expected.
- **Comprehensive Collection**: The repository covers a wide range of C programs that are commonly encountered in KTU university curriculum.
- **Easy to Understand**: Each program is well-commented and structured, making it easier for students to comprehend and learn from.

## Navigation

Navigating through a repository can be challenging, but our repository is designed with meticulous organization to make navigation easy and intuitive.

The file structure of CCpy is structured according to a clear navigational hierarchy. Below is an overview of this hierarchy, arranged from the highest to the lowest level of importance:

| Precedence level |                      Concept                      |
| :--------------: | :-----------------------------------------------: |
|        1         |                       Files                       |
|        2         |                Structs and Unions                 |
|        3         |                      Strings                      |
|        4         |                     Pointers                      |
|        5         |                      Arrays                       |
|        6         |                     Functions                     |
|        7         |       Loops <br>`while , do .. while, for`        |
|       8.1        |  Flow Control <br>`switch , goto, ternary (:?)`   |
|       8.2        | Flow Control (Branching) <br>`if, else , else if` |
|        9         |    Default (Anything Not Otherwise Mentioned)     |

Each navigational precedence level has its own dedicated directory or folder.
Certain levels (8.1, 8.2) are closely related that they have one parent folder with sub folders showing individual levels.

### Example Usage

Let's imagine you're looking a program that involves three key elements:

a) Functions,
b) Arrays, and
c) Loops.

In this scenario, you can efficiently navigate the repository's structure as follows:

1. **Arrays**: Begin by exploring the **_arrays_** directory since arrays have a higher precedence.

2. **Functions**: After reviewing arrays, proceed to the **_functions_** directory as it has the next highest precedance.

3. **Loops**: Finally, navigate to the **_loops_** directory, which houses loop-related programs, to complete your journey.

By following this path, you will navigate through: **Arrays > Functions > Loops > program.c**

## How to run?

To use the programs in this repository, you need to have a C compiler installed on your system, such as GCC (GNU Compiler Collection). Follow these steps to get started:

1.  Clone this repository to your local machine using the following command:

    ```shell
    git clone https://github.com/sahil-shefeek/ccpy.git


    ```

2.  Navigate to the cloned repository's directory:

    ```shell
    cd ccpy



    ```

3.  Compile and run any program using your preferred C compiler. For example, to compile and run the program named `program.c`, use the following commands:

    ```shell
    gcc program.c
    ./a.out
    ```

    For Windows users:

        gcc program.c
        a.exe

Each program in this repository is contained in its own file with a descriptive name. To use a specific program, follow these steps:

1. Open the program file (e.g., `program.c`) using a text editor of your choice.

2. Read the comments and code to understand the purpose and functionality of the program.

3. Modify the code as needed or use it as a reference for your own projects.

4. Save the changes and follow the installation instructions mentioned above to compile and run the program.

## Contributing

Contributions to CCPy are welcome and encouraged! If you would like to contribute, please follow these steps:

1. Fork the repository to your GitHub account.

2. Create a new branch based on the feature or bug you want to work on.

3. Make your changes and test them thoroughly.

4. Commit your changes with a descriptive commit message.

5. Push your branch to your forked repository.

6. Open a pull request in the main repository, explaining the changes you have made.

## License

The code in this repository is licensed under the [MIT License](LICENSE). You are free to use, modify, and distribute the code for personal and educational purposes.
