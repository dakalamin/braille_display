# braille_display

[![GitHub Actions Workflow Status - build.yaml](https://img.shields.io/github/actions/workflow/status/dakalamin/braille_display/build.yaml?style=flat-square&label=PlatformIO%20build)](https://github.com/dakalamin/braille_display/actions/workflows/build.yaml)
[![GitHub Actions Workflow Status - readme.yaml](https://img.shields.io/github/actions/workflow/status/dakalamin/braille_display/readme.yaml?style=flat-square&label=Readme%20links%20check)](https://github.com/dakalamin/braille_display/actions/workflows/readme.yaml)

[![GitHub Release](https://img.shields.io/github/v/release/dakalamin/braille_display?sort=semver&display_name=tag&style=flat-square&label=Release)](https://github.com/dakalamin/braille_display/releases)
[![GitHub License](https://img.shields.io/github/license/dakalamin/braille_display?style=flat-square&label=License)](#license)

This project implements a scalable multi-cell Braille display system using an Arduino - it converts input characters into their corresponding Braille patterns, enabling accessibility for visually impaired users

![project breadboard scheme](assets/image.png)

## Table of Contents

- [Preparation](#preparation)
	- [In simulation via Wokwi](#1-in-simulation-via-wokwi)
	- [On real Arduino via PlatformIO in VSCode](#2-on-real-arduino-via-platformio-in-vscode)
	- [On real Arduino via Arduino IDE](#3-on-real-arduino-via-arduino-ide)
- [Usage](#usage)
- [Features](#features)
- [Todo](#todo)
- [Contribution](#contribution)
- [License](#license)

## Preparation

### **1. In simulation via [Wokwi](https://wokwi.com)**
- Follow the [Wokwi-project link](https://wokwi.com/projects/410634164212519937)
> [!NOTE]  
> If Wokwi-project link is broken or project there is corrupted, please report it to [GitHub Issues](https://github.com/dakalamin/braille_display/issues), meanwhile:
> - Clone or [download](https://github.com/dakalamin/braille_display/archive/refs/heads/main.zip) and unpack the repository
> - Start a [blank Wokwi-project](https://wokwi.com/projects/new/blank)
> - Select **`diagram.json`** tab
> - Press ⏷ button to the right of **'Library Manager'** tab, then - **'Delete'** and confirm
> - Press ⏷ button once again, then - **'Upload file(s)...'**
> - Select all files from the project's **`src/`** folder and confirm
- Press green **'Play'** button to start the simulation 

### **2. On real Arduino via [PlatformIO](https://platformio.org) in VSCode**
- Install [Visual Studio Code](https://code.visualstudio.com) and launch it
- Install [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) extension for VSCode
- Clone or [download](https://github.com/dakalamin/braille_display/archive/refs/heads/main.zip) and unpack the repository
- Open **`braille_display/`** project's folder with VSCode
- Connect your Arduino via USB to your computer
> [!NOTE]
> **Arduino Uno** is set as default board in **`platformio.ini`** - if you use different board, do the following:
> - Click **'View'->'Command Palette...'** _(or press `Ctrl+Shift+P`)_
> - Paste `> PlatformIO: PlatformIO Home` and press `Enter`
> - Select **'Projects'** tab on the left
> - Search for the **braille_display** project and click **'Configure'**
> - Choose your board in **'Platform Options'→'board'**
> - Click **'Save'** in the upper right corner
- Press **'Upload'** button in the upper right corner of VSCode window _(or press `Ctrl+Alt+U`)_

### **3. On real Arduino via Arduino IDE**
- Clone or [download](https://github.com/dakalamin/braille_display/archive/refs/heads/main.zip) and unpack the repository
- Rename project's **`src`** folder to **`main`**
- Rename **`main.cpp`** file to **`main.ino`**
- Open **`main.ino`** with Arduino IDE
> [!Note]
> Make sure that all **`.h`** files are shown in the top tabs
- Connect your Arduino via USB to your computer
> [!Note]
> Make sure to select your Arduino model in **'Tools'→'Board'**
- Press **'Upload'** button in the upper left corner of Arduino IDE window _(or press `Ctrl+U`)_

## Usage

Send messages, that you want to translate and show, to the Serial Monitor.

Press the button to display the next set of Braille patterns.

## Features

- Program can translate following symbols into Braille:
	- **Latin** alphabet
	- **Cyrillic** alphabet
	- **Numbers**
	- frequently used **Punctuation**

- You can send messages one after another not waiting for the previous ones to be shown - program will try to concatenate them until the `rx_buffer` _(receiving buffer)_ is full

- You can hold the button instead of repeatidly pressing it - program will display the next number of characters on the defined time interval

- You can easily scale the number of cells on the Braille display - the only change to the program you need to make is a single variable

- Program will keep the last part of the last message displayed until you send a new message and then press the button

- Program can process special cases of translating to Braille (e.g.: punctuation, modifiers, etc.)
	> <details>
	> <summary>Examples:</summary>
	>
	> - capital modifier is required before capital letters: **`XyZ`** → **<code><ins>⠠</ins>⠭⠽<ins>⠠</ins>⠵</code>**
	> - numeric modifier is required before numbers: **`a 12`** → **<code>⠁ <ins>⠼</ins>⠁⠃</code>**
	> - **.** (dot) symbol has different translations:<ul>
	> - **`N.o`** → **<code>⠠⠝<ins>⠲</ins>⠕</code>** _(a grammatical dot)_
	> - **`8.9`** → **<code>⠼⠓<ins>⠨</ins>⠊</code>** _(a decimal dot)_
	> 	- **\*** (asterisk) symbol is translated into a doubled **⠔** Braille pattern: **`5 * 6`**→ **<code>⠼⠑ <ins>⠔⠔</ins> ⠼⠋</code>**
	> 	- **"** (quote) symbol's Braille pattern alternates on opens and closes: **`m "q" n`** → **<code>⠍ <ins>⠦</ins>⠟<ins>⠴</ins> ⠝</code>**
	> - quote, unpaired until EOM, can be paired automatically: **`"k`** → **<code>⠦⠅<ins>⠴</ins></code>**
	> </details>

- Program doesn't process characters in advance - it translates the least neccessary amount of characters to fill the Braille display after you press the button

- Program can wait for the next messages if last symbols of the current one don't have enough context to be translated to Braille correctly
	> <details>
	> <summary>Examples:</summary>
	>
	> First comes **<code>30<ins>.</ins></code>** message
	> - there is not enough context in the message for the **.** (dot) symbol to be translated to Braille
	> - program sends **`⠼⠉⠚`** patterns to the display (without **.** symbol) and waits for the next message:
	> 	- then comes **`25`** message → program shows **<code><ins>⠨</ins>⠃⠑</code>** _(decimal dot)_
	> 	<br>**-or-**
	> 	- then comes **` re`** message → program shows **<code><ins>⠲</ins>⠗⠑</code>** _(grammatical dot)_
	> </details>

## Todo

- Add Customization section to README
- Add Russian variant of README
- Add tests
- Add Python script to prepare project for Arduino IDE
- Optimize `nchar**_t` type for symbols with translation to Braille

## Contribution

Feel free to contribute to this project by submitting issues or pull requests!

## License

This project is open-source and available under the [MIT License](LICENSE)
