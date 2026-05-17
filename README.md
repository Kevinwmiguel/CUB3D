*This project has been created as part of the 42 curriculum by kwillian, made-jes.*

# Cub3d

## Description 

- Cub3D is a simple 3D rendering engine inspired by early games like Wolfenstein 3D.
It uses raycasting to simulate a 3D environment from a 2D map, built with the MiniLibX graphics library.

### Features

- Real-time raycasting engine
- First-person navigation through a maze
- Directional wall textures (North, South, East, West)
- Configurable floor and ceiling colors
- Keyboard-based movement and camera control
- Proper window handling (close, minimize, exit cleanly)

### 🎮 Controls

| Key      | Action                 |
| -------- | ---------------------- |
| `W`      | Move forward           |
| `S`      | Move backward          |
| `A`      | Move left              |
| `D`      | Move right             |
| `← / →`  | Rotate camera          |
| `ESC`    | Exit program           |
| Window ❌ | Close and exit cleanly |

### Map & Configuration

The program takes a `.cub` file as its first argument.


✔️ Map Rules
The map must contain only:
- 0 → empty space
- 1 → wall
- N, S, E, W → player spawn + orientation

- Example:
```bash
111111
100101
101001
1100N1
111111
```

- The map must:
- Be fully enclosed by walls
- Be the last element in the .cub file
- Be parsed exactly as written (spaces are valid characters)

### 🧩 Scene Configuration

Each element (except the map) can appear in any order and be separated by empty lines.

#### 🧱 Textures
```bash
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture
```

| Identifier	|	Description		|
| ------------  | ----------------- |
| `NO`          |	North texture	|
| `SO` 			|	South texture	|
| `WE` 			|	West texture	|
| `EA` 			|	East texture	|

#### 🎨 Colors
```bash
F 220,100,0
C 225,30,0
```

| Identifier |	Description	   |
| --------   | --------------- |
| `F` 		 | Floor color (RGB) |
| `C`		 |	Ceiling color (RGB) |

- RGB values must be in the range [0, 255]

#### 📄 Example .cub File
```bash
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

#### ⚠️ Error Handling

If any configuration issue is detected, the program must:

- 1. Exit cleanly
- 2. Display:
```bash
Error
<your descriptive message>
```

Examples of errors:
- Map not closed
- Missing textures
- Invalid RGB values
- Invalid characters in map

#### 🛠️ Technical Notes

- Built using MiniLibX
- Must handle:
 - Window events (close, minimize)
 - Memory management
 - Robust parsing

# Instructions

# Resources
