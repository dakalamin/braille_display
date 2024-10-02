# braille_display

This project implements a scalable multi-cell Braille display system using an Arduino - it converts input characters into their corresponding Braille patterns, enabling accessibility for visually impaired users

![project breadboard scheme](assets/image.png)

## Usage

1. **In simulation via [Wokwi](https://wokwi.com)**
    - Follow the [Wokwi-project link](https://wokwi.com/projects/410634164212519937)
        <blockquote>
        <details><summary> <b>Note:</b> if the Wokwi-project link is broken or the project there is corrupted, please report it to <a href="https://github.com/dakalamin/braille_display/issues">GitHub Issues</a>, meanwhile... </summary>
        <ul>
        <li>Clone or <a href="https://github.com/dakalamin/braille_display/archive/refs/heads/main.zip">download</a> and unpack the repository</li>
        <li>Start a <a href="https://wokwi.com/projects/new/blank">blank Wokwi-project</a></li>
        <li>Select <b><code>diagram.json</code></b> tab</li>
        <li>Press the triangle button to the right of <b>'Library Manager'</b> tab, then - <b>'Delete'</b> and confirm</li>
        <li>Press the triangle button once again, then - <b>'Upload file(s)...'</b></li>
        <li>Select all files from the project's <b><code>src</code></b> folder and confirm</li>
        </details>
        </blockquote>
    - Press green **'Play'** button to start the simulation 

2. **On real Arduino via [PlatformIO](https://platformio.org) in VSCode**
    - Install [Visual Studio Code](https://code.visualstudio.com) and launch it
    - Install [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) extension for VSCode
    - Clone or [download](https://github.com/dakalamin/braille_display/archive/refs/heads/main.zip) and unpack the repository
    - Open **`braille_display/`** project's folder with VSCode
    - Connect your Arduino via USB to your computer
        <blockquote>
        <details><summary> <b>Note:</b> <b>Arduino Uno</b> is set as default board in <b><code>platformio.ini</code></b> - if you use different board, do the following...</summary>
        <ul>
        <li>Click <b>'View'->'Command Palette...'</b> <i>(or press <code>Ctrl+Shift+P</code>)</i></li>
        <li>Paste <code>> PlatformIO: PlatformIO Home</code> and press <code>Enter</code></li>
        <li>Select <b>'Projects'</b> tab on the left</li>
        <li>Search for the <b>braille_display</b> project and click <b>'Configure'</b></li>
        <li>Choose your board in <b>'Platform Options'->'board'</b></li>
        <li><b>IMPORTANT:</b> Click <b>'Save'</b> in the upper right corner</li>
        </ul>
        </details>
        </blockquote>
    - Press **'Upload'** button in the upper right corner of VSCode window *(or press `Ctrl+Alt+U`)*

2. **On real Arduino via Arduino IDE**
    - Clone or [download](https://github.com/dakalamin/braille_display/archive/refs/heads/main.zip) and unpack the repository
    - Rename project's **`src`** folder to **`main`**
    - Rename **`main.cpp`** file to **`main.ino`**
    - Open **`main.ino`** with Arduino IDE *(make sure, that all .h files are shown the top tabs)*
        <blockquote>
        <b>Note:</b> make sure that all <b><code>.h</code></b> files are shown the top tabs
        </blockquote>
    - Connect your Arduino via USB to your computer
        <blockquote>
        <b>Note:</b> make sure to select your Arduino model in <b>'Tools'->'Board'</b>
        </blockquote>
    - Press **'Upload'** button in the upper left corner of Arduino IDE window *(or press `Ctrl+U`)*

