# BPG - Block Puzzle Game

Just a fun project I made during learning C++ with SDL and modern language constructions. Most interesting was to reuse uint16 for storing object matrix, lets say "efficient memory utilization" :)
I call it Block Puzzle Game but technically everyone sees by which game it was inspired from.

## Screenshots
<img width="1023" height="767" alt="bpg-title-screen" src="https://github.com/user-attachments/assets/11737eac-05ab-4023-973a-a43e26b890fe" />
<img width="1020" height="765" alt="bpg1" src="https://github.com/user-attachments/assets/b510f523-2c8c-4b43-8b11-f22e572d5338" />
<img width="1017" height="760" alt="bpg2" src="https://github.com/user-attachments/assets/56849f4b-9c9d-4f8f-ab86-ef9b4f45cf2d" />
<img width="1020" height="765" alt="bpg3" src="https://github.com/user-attachments/assets/3d0c56b3-2d58-4019-a7b6-8738c8c6b6d4" />
<img width="1022" height="766" alt="bpg4" src="https://github.com/user-attachments/assets/983c2b4b-5d03-4d69-9868-d74306d5d8bd" />


## Build & Run

### Dependencies

You will need the following libraries installed:

- `SDL2`
- `SDL2_image`
- `SDL2_ttf`

### Build Command (Linux/macOS)

Use the provided `Makefile` to compile the project:

```bash
make build
```

### Run

```bash
make run
```

## Controls

- **Arrow Keys (Left/Right)**: Move the block horizontally.
- **Arrow Key (Down)**: Speed up the descent.
- **Space**: Rotate the block.
- **ESC**: Exit the game.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
