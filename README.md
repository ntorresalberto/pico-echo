## 📢 pico-echo – A Dual-Core Text Echo Effect for Raspberry Pi Pico 🎶🔁

![Generate a conceptual illustration for a GitHub README banner for the pico-echo project, a Raspberry Pi Pico firmware demo that echoes back text over USB serial with a decaying effect. The illustration should be in a cartoonish yet professional style, engaging and modern without feeling childish.
The scene is set inside the Grand Canyon, with a Raspberry Pi Pico positioned at the bottom as if it is "yelling" a word like 'Hello!'. The text then progressively shrinks and fades as it moves into the canyon, visually representing an audio echo decay effect. The echoed words should appear in a layered manner, getting smaller and more transparent with each repetition to clearly depict the fading effect.
The perspective should be wide and panoramic, suitable for a GitHub README banner, ensuring that key elements (the Pico and the echoing text) remain clear and legible. The overall design should incorporate a subtle tech theme while maintaining a clean, dynamic composition that effectively communicates the core idea of the project.](assets/dalle_banner.webp)

Type over USB serial, and watch your text "echo" back with a fading effect! Built for the Raspberry Pi Pico, this dual-core firmware showcases real-time USB serial communication with a cool visual twist. 🚀



## 🎬 Demo

Check out the demo below to see **pico-echo** in action:


[![pico-echo demo](https://asciinema.org/a/eFPJpsTWUd3eZ76MGcL8srenE.svg)](https://asciinema.org/a/eFPJpsTWUd3eZ76MGcL8srenE)


## ✨ Features

- ⚡ **Dual-core processing** for efficient handling
- 🔄 **USB serial text echo** with a fading effect
- 🎯 **Lightweight and simple** firmware demo for the Pico


## 📂 Repository Contents

- `main.c` – Core firmware logic
- `CMakeLists.txt` – Build configuration
- `README.md` – You're reading it!

## 🚀 Why Use pico-echo?

This project is a fun way to explore **USB serial communication** and **dual-core processing** on the Raspberry Pi Pico.

Perfect for **beginners, tinkerers, and firmware enthusiasts**!


## 🛠️ Getting Started

1. **Compile the firmware**
2. **Flash the firmware** to your Raspberry Pi Pico
3. **Connect via USB serial** using a terminal
4. **Type anything** and see it echo back with a cool fading effect!

#### Compile the firmware

**Prerequisites**

Set up the [Pico SDK](https://github.com/raspberrypi/pico-sdk?tab=readme-ov-file#unix-command-line). Ensure that you set the necessary environment variables, such as:

```bash
export PICO_SDK_PATH=/path/to/pico-sdk
export PICO_PLATFORM=rp2050  # Replace with your platform if different
```


**Compilation**

Make sure to complete the prerequisites first!
Once that’s done, you can compile using these commands.

```bash
git clone https://github.com/ntorresalberto/pico-echo.git
cd pico-echo
mkdir build/ && cd build
cmake ..                          # init build system
make -j                           # compile
```

#### Flash the firmware
After compiling, you'll see multiple files inside the `build/` directory.
The firmware you need to flash is `pico_echo.uf2`.

There are several ways to flash the firmware,
but I find the easiest method is using [picotool](https://github.com/raspberrypi/picotool). You can do it with the following command:


```bash
picotool load -f pico_echo.uf2  # Flash the firmware
```

#### Connect via USB serial

You can use any serial terminal program, but I recommend
[tio](https://github.com/tio/tio) because it's super minimal and easy to use.


To list available serial ports and connect, run:
```bash
tio -l            # List serial ports
tio /dev/ttyACM0  # Replace with your actual port
```

**Using `tio`? You can exit by pressing `Ctrl+T`, then `Q`**


---

💡 **Made for fun, learning, and experimentation!**
