# SDL on Stilts

## Compiler Requirements

- C++20 (`concepts`)

## Module Planning (May 14th, 2024)

```text
.------------------------.
| Task Breakdown         |                           .------.
|                        |                        .--| Root | ---- [ WIP ]
|    2 / 9   Working     |                       /   `------`
|                        |                    .-%-------.
|  NEXT: *               |                    | Process | ---- [ WIP ]
`------------------------`                    %---------`
                                             /
            .--------------------.          /
  .--------(   SOS Core Modules   )--------%
  |         `--------------------`         |
  |                                        |     [ 0 / 5 ]
  |      .- [ 1 / 5 ]                      |    /
.-------/                              .-------/
| Input |           [ DONE ]           | Video |          [ TODO ]
`-------`          /                   `-------`         /
  |    .----------/                      |    .---------/
  +`---| Keyboard |                      +`---| Display |
  |    `----------`                      |    `---------`
  |    .-------.                         |    .--------.
  +`---| Mouse |  ---- [ TODO ]          +`---| Window | ---- [ TODO ]
  |    `-------`                         |    `--------`
  |    .----------.                      |    .-----------.
  +`---| Joystick | ---- [ TODO ]        +`---| Rendering | ---- [ TODO ]
  |    `----------`                      |    `-----------`
  |    .-----------------.               |    .---------.
  +`---| Game Controller |               +`---| Surface | - [ TODO ]
       `-----------------`               |    `---------`
                         \               |    .-------.
                           [ TODO ]      +`---| Pixel |
                                              `-------\
                                                       \
            .---------------------.                     [ TODO ]
  .--------( SOS Extension Modules )-------.
  |         `---------------------`        |
  |                                        |
  |      .- [ 1 / 2 ]                      |    .- [ 0 / 2 ]
.-------/                              .-------/
| Input |               [ WIP ]        | Video |          [ TODO ]
`-------`             /                `-------`         /
  |    .-------------/                      |    .------/
  +`---| Indirection |                      +`---| Text |    <(Will Require SDL2_TTF)>
  |    `-------------`                      |    `------`
  |    .--------.                           |    .-------.
  +`---| Config |                           +`---| Image |   <(Will Require SDL2_Image)>
       `--------\                                `-------\
                 \                                        \
                  [ TODO ]                                 [ TODO ]
```
