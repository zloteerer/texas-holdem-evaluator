# C++ Texas Hold'em Poker Hand Evaluator

![Poker Image](https://play-lh.googleusercontent.com/tfQ4f-Eup5yuDgxGVjrDYmWv_U8VWhfI3-dBi7HwmXSubB-UGHV8JXJ7Moli2lXVd1k)

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Build](#build)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Welcome to the Texas Hold'em Poker Hand Evaluator! This project is a fast and efficient Texas Hold'em poker hand evaluator using bit fields to determine the winning hand.


## Features

- Efficient evaluation of poker hands using bit fields.
- Detection of winning hands and players in Texas Hold'em games.

## Getting Started

### Prerequisites

Before you get started, make sure you have the following installed:

- CMake

### Build

1. Clone the repository:
   ```sh
   git clone https://github.com/evandelagnes/texas-holdem-evaluator.git
   cd poker-winner-detector
   ```

2. Create a build directory:
    ```sh
    mkdir build
    cd build

3. Generate the build system using CMake:
    ```sh
    cmake ..
    ```

4. Build the project:
    ```sh
    make
    ```

## Usage

To evaluate Texas Hold'em poker hands and determine the winner, use the following command:

```sh
Usage: ./poker [options]

Options:
    -b, --board <cards>  Specify the community cards on the board. Provide 3, 4, or 5 cards, e.g., -b 5h9djsqckh.
    -p, --player <cards> Specify the hole cards for players. Provide 2 cards per player with a maximum of 10 players, e.g., -p 2c3s.

Example:
    ./poker -b 3s9hkd -p 7cah
``````