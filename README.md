# Zappy

![CI Epitech Project - Zappy](https://github.com/MyEpitech/B-YEP-410-PAR-4-1-zappy-martin.vanaud/actions/workflows/main.yml/badge.svg?branch=master)

## $\color{green}{Grade: B}$

## About the project

**The aim of this project is to develop a network game that artificial intelligences will play as a team in order to win the game.**

<div align="center">

![gameplay](./gameplay.png)

</div>

The goal of the game itself is to survive and reproduce by collecting resources to perform rituals and level up. The first AI team to reach level 8 wins the game. The zappy project is separated into three distinct parts:
- **Server**: Allows the progress of the game by establishing communication with the artificial intelligences
- **GUI**: Graphical interface connecting to the server in order to follow the progress of the game
- **AI**: Client connecting to server to play automatically

---

## Getting Started

### Setup
```
$ bash .github/scripts/setup.sh
```

### Build & Execute (all)
```
$ make zappy_server

$ make zappy_ai
$ make zappy_gui

$ ./server/zappy_server --help

$ ./client/ai/zappy_ai --help
$ ./client/gui/build/zappy_gui --help
```

### Project realised by:

- **[@Clément F.](https://github.com/Clement-Fernandes)**
- **[@Gurvan L.](https://github.com/Gurvan-Le-Letty)**
- **[@Martin V.](https://github.com/martinvanaud)**
- **[@Victor P.](https://github.com/victorpalle)**
- **[@Maxime C.](https://github.com/maxime-carabina)**
- **[@Valentin D.](https://github.com/ValentinDurieux)**
