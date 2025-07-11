# image_stenography

A GUI-based C++ tool for hiding and extracting text or files inside images using LSB steganography with OpenCV and Dear ImGui.

## Features

- **Hide Text or Files:** Conceal text messages or any files within images using Least Significant Bit (LSB) steganography.
- **Extract Data:** Retrieve hidden text or files from images that were encoded with this tool.
- **User-Friendly GUI:** Built with Dear ImGui for an interactive and intuitive user interface.
- **Image Processing:** Leverages OpenCV for efficient image manipulation and processing.

## Demo

<img width="1283" height="759" alt="image" src="https://github.com/user-attachments/assets/8ba25227-ff1f-4c0e-9259-87d5fe0fe53c" />
<img width="1196" height="645" alt="image" src="https://github.com/user-attachments/assets/be304c2f-30c0-4485-923f-9af0df250235" />



## Installation

### Prerequisites

- **C++ Compiler** (supporting C++17 or newer)
- **CMake** (version 3.10+ recommended)
- **OpenCV** (version 4.x)
- **Dear ImGui** (with a backend for your platform)
- **GLFW** or another window/context system supported by ImGui

### Build Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Ramsha-Anwar/image_stenography.git
   cd image_stenography
   ```

2. **Install dependencies:**
   - Ensure OpenCV and Dear ImGui are installed and available to your build system.
   - On Ubuntu, you can install OpenCV with:
     ```bash
     sudo apt-get install libopencv-dev
     ```
   - Dear ImGui can be included as a submodule or installed separately.

3. **Build the application:**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Run the application:**
   ```bash
   ./image_stenography
   ```

## Usage

1. **Launch the Application:** Double-click the executable or run it from the terminal.
2. **Encode Data:**
   - Select the image in which you want to hide data.
   - Choose whether to hide text or a file.
   - Enter the text or select the file to hide.
   - Click "Encode" and save the resulting image.
3. **Decode Data:**
   - Open an image that contains hidden data.
   - Click "Decode" to extract and view the hidden text or file.

## How It Works

This tool uses the Least Significant Bit (LSB) technique to modify the smallest bits in each pixel of an image to encode hidden data. This results in minimal visible changes to the image.

## Contributing

Contributions are welcome! Please open issues or submit pull requests.

## License

MIT License

## Acknowledgements

- [OpenCV](https://opencv.org/)
- [Dear ImGui](https://github.com/ocornut/imgui)

## Contact

For questions or feedback, please open an issue in this repository.

---
*This project is maintained by [Ramsha-Anwar](https://github.com/Ramsha-Anwar).*
