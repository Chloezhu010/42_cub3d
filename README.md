# 42_cub3d
## Description
- A group project to create a dynamic view inside a 3D maze
- Using minilibX lib to implement raycasting in the style of Wolfenstein 3D game
## Allowed functions
- Libft
- math lib
- minilibX lib
- open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday
## Requirements
- Map
    - .cub file
    - 0 for empty space, 1 for a wall, NSEW for the player's start position and spawning orientation
    - must be closed by walls, if not return error
- NO LEAKS ARE POSSIBLE OFC

## Key modules
### Map parser
- Read & validate map config file in .cub
- Parse textures, colors, map layout
- Create a 2D array representation of the map
### Ray casting engine
- Cast rays from player position to determine wall distance
- Cal wall heights based on ray distance
- Handle different textures for different wall directions (NSEW)
- Implement the digital differenetial analysis (DDA) algo
### Player controller
- Handle player pos and viewing direction
- Process keyboard/ mouse inputs for movement & rotation
- Implement collision detection with walls
### Renderer
- Create windown and manage game loop
- Render wall with textures and heights
- Draw celling and floor with colors
- Apply texture mapping to walls
### Texture manager
- Load texture img
- Map textures to walls based on orientation
- Cal texture coordinates for each vertical strip
### Main game loop
- Init all required modules
- Handle the game timing
- Process user input
- Update game state
- Trigger rendering
- Manage clean shutdown and resource cleanup

## Key concepts
### Raycasting


## Resource
- Doc: https://ab9jvcjkej.feishu.cn/docx/YNTpd8Uq4oNihGxQnftcqk3xngc
