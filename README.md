<div align="center">
  
# [Master-UTFPR](https://github.com/BrenoFariasdaSilva/Master-UTFPR) <img src="https://github.com/BrenoFariasdaSilva/Master-UTFPR/blob/6d4e05fafa6ee2927227ca66b930d774ff63a9f3/.assets/Icons/BooksStack.svg"  width="3%" height="3%">

</div>

<div align="center">
  
---

Master-UTFPR centralizes coursework, practices, and reports from UTFPR's postgraduate Computer Science program, combining C implementations for Algorithms and Data Structures with Java and Maven-based activities for Software Testing.
  
---

</div>

<div align="center">

![GitHub Code Size in Bytes](https://img.shields.io/github/languages/code-size/BrenoFariasdaSilva/Master-UTFPR)
![GitHub Commits](https://img.shields.io/github/commit-activity/t/BrenoFariasdaSilva/Master-UTFPR/main)
![GitHub Last Commit](https://img.shields.io/github/last-commit/BrenoFariasdaSilva/Master-UTFPR)
![GitHub Forks](https://img.shields.io/github/forks/BrenoFariasdaSilva/Master-UTFPR)
![GitHub Language Count](https://img.shields.io/github/languages/count/BrenoFariasdaSilva/Master-UTFPR)
![GitHub License](https://img.shields.io/github/license/BrenoFariasdaSilva/Master-UTFPR)
![GitHub Stars](https://img.shields.io/github/stars/BrenoFariasdaSilva/Master-UTFPR)
![GitHub Contributors](https://img.shields.io/github/contributors/BrenoFariasdaSilva/Master-UTFPR)
![GitHub Created At](https://img.shields.io/github/created-at/BrenoFariasdaSilva/Master-UTFPR)
![wakatime](https://wakatime.com/badge/github/BrenoFariasdaSilva/Master-UTFPRsvg)

</div>

<div align="center">
  
![RepoBeats Statistics](https://repobeats.axiom.co/api/embed/fdb453aad500c56be793cee32465d75571e439fc.svg "Repobeats analytics image")

</div>

## Table of Contents
- [Master-UTFPR ](#master-utfpr-)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Requirements](#requirements)
  - [Setup](#setup)
    - [Clone the repository](#clone-the-repository)
  - [Installation:](#installation)
  - [Run Programing Language Code:](#run-programing-language-code)
    - [Dependencies](#dependencies)
  - [Usage](#usage)
  - [Contributing](#contributing)
  - [Collaborators](#collaborators)
  - [License](#license)
    - [Apache License 2.0](#apache-license-20)

## Introduction

This repository brings together the material developed for two master's level subjects at UTFPR. In PPGCC02 - Algorithms And Data Structures, the content is organized into activities, classes, practice folders, templates, and tests that cover arrays, heterogeneous structures, dynamic memory allocation, files, stacks, lists, recursion, hash tables, binary trees, AVL trees, B-trees, and sorting algorithms through C implementations. In PPGCC12 - Software Testing, the activities focus on automated testing techniques with Java projects structured with Maven, including unit testing, identifier validation, mutation-oriented exercises, property-based testing, mocks, and Test-Driven Development.

## Requirements

- Git
- GCC compiler
- Make
- Java Development Kit (JDK 21 or higher)
- Maven 3 or higher

## Setup

### Clone the repository

1. Clone the repository with the following command:

   ```bash
  git clone https://github.com/BrenoFariasdaSilva/Master-UTFPR.git
   cd Master-UTFPR
   ```

## Installation:

* Programing Languages:

  * Manually:
      ```bash
    # C toolchain
    sudo apt install gcc make -y

    # Java toolchain
    sudo apt install openjdk-21-jdk maven -y
      ```

  * Using Makefile:
      ```bash
    cd "Subjects/PPGCC02 - Algorithms And Data Structures/Template"
    make
      ```

  * Using Maven:
      ```bash
    cd "Subjects/PPGCC12 - Software Testing/Activities/Activity 01 - Adição Números Grandes"
    mvn clean test
      ```  

## Run Programing Language Code:

```bash
# C example
cd "Subjects/PPGCC02 - Algorithms And Data Structures/Activities/Activity 12 - Sorting Algorithms"
make run

# Java example
cd "Subjects/PPGCC12 - Software Testing/Activities/Activity 07 - Test Driven Development"
mvn clean test
```

### Dependencies

1. Install the Maven dependencies for the Software Testing activities with the following command:

   ```bash
  cd "Subjects/PPGCC12 - Software Testing/Activities/Activity 06 - Mocks"
  mvn dependency:resolve
   ```

## Usage

In order to run the project, choose a subject activity and use the corresponding command:

```bash
# C activities
cd "Subjects/PPGCC02 - Algorithms And Data Structures/Activities/Activity 07 - Recursion/ex06 - Binary Search"
make run

# Java activities
cd "Subjects/PPGCC12 - Software Testing/Activities/Activity 06 - Mocks"
mvn clean test
```

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**. If you have suggestions for improving the code, your insights will be highly welcome.
In order to contribute to this project, please follow the guidelines below or read the [CONTRIBUTING.md](CONTRIBUTING.md) file for more details on how to contribute to this project, as it contains information about the commit standards and the entire pull request process.
Please follow these guidelines to make your contributions smooth and effective:

1. **Set Up Your Environment**: Ensure you've followed the setup instructions in the [Setup](#setup) section to prepare your development environment.

2. **Make Your Changes**:
   - **Create a Branch**: `git checkout -b feature/YourFeatureName`
   - **Implement Your Changes**: Make sure to test your changes thoroughly.
   - **Commit Your Changes**: Use clear commit messages, for example:
     - For new features: `git commit -m "FEAT: Add some AmazingFeature"`
     - For bug fixes: `git commit -m "FIX: Resolve Issue #123"`
     - For documentation: `git commit -m "DOCS: Update README with new instructions"`
     - For refactorings: `git commit -m "REFACTOR: Enhance component for better aspect"`
     - For snapshots: `git commit -m "SNAPSHOT: Temporary commit to save the current state for later reference"`
   - See more about crafting commit messages in the [CONTRIBUTING.md](CONTRIBUTING.md) file.

3. **Submit Your Contribution**:
   - **Push Your Changes**: `git push origin feature/YourFeatureName`
   - **Open a Pull Request (PR)**: Navigate to the repository on GitHub and open a PR with a detailed description of your changes.

4. **Stay Engaged**: Respond to any feedback from the project maintainers and make necessary adjustments to your PR.

5. **Celebrate**: Once your PR is merged, celebrate your contribution to the project!
