# tino

## Tested environment

| Travis CI (Linux) | Github Actions <br> Linux/Win  |
| :---------------: | :----------------------------: |
| [![Build Status](https://travis-ci.org/guerinoni/tino.svg?branch=master)](https://travis-ci.org/guerinoni/tino) | ![Ubuntu](https://github.com/guerinoni/tino/workflows/Ubuntu/badge.svg) ![Windows](https://github.com/guerinoni/tino/workflows/Windows/badge.svg) |

## Build
```
move in folder project
> mkdir build
> cd build
> cmake -DCMAKE_PREFIX_PATH=<your_path> .. (path example: ~/Qt/5.12.7/gcc_64)
> make
```


## Feature

This is a desktop application useful to simulate communication between the logic board and video board.

* import buffer configuration file from json
* treeview to show protocol of imported file
* settings loaded from file
* widget to edit IO directly using mouse
* communication through:
    - virtual com
    - modbus RS485
