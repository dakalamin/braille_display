# braille_display

This project implements a scalable multi-cell Braille display system using an Arduino - it converts input characters into their corresponding Braille patterns, enabling accessibility for visually impaired users

![project breadboard scheme](assets/image.png)

## Preparation

1. **In simulation via [Wokwi](https://wokwi.com)**
	- Follow the [Wokwi-project link](https://wokwi.com/projects/410634164212519937)
		<blockquote>
		<details>
		<summary>
		<b>Note:</b> if the Wokwi-project link is broken or the project there is corrupted, please report it to <a href="https://github.com/dakalamin/braille_display/issues">GitHub Issues</a>, meanwhile...
		</summary>
		<ul>
		<li>Clone or <a href="https://github.com/dakalamin/braille_display/archive/refs/heads/main.zip">download</a> and unpack the repository</li>
		<li>Start a <a href="https://wokwi.com/projects/new/blank">blank Wokwi-project</a></li>
		<li>Select <b><code>diagram.json</code></b> tab</li>
		<li>Press ⏷ button to the right of <b>'Library Manager'</b> tab, then - <b>'Delete'</b> and confirm</li>
		<li>Press ⏷ button once again, then - <b>'Upload file(s)...'</b></li>
		<li>Select all files from the project's <b><code>src</code></b> folder and confirm</li>
		</ul>
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
		<details>
		<summary>
		<b>Note:</b> <b>Arduino Uno</b> is set as default board in <b><code>platformio.ini</code></b> - if you use different board, do the following...
		</summary>
		<ul>
		<li>Click <b>'View'->'Command Palette...'</b> <i>(or press <code>Ctrl+Shift+P</code>)</i></li>
		<li>Paste <code>> PlatformIO: PlatformIO Home</code> and press <code>Enter</code></li>
		<li>Select <b>'Projects'</b> tab on the left</li>
		<li>Search for the <b>braille_display</b> project and click <b>'Configure'</b></li>
		<li>Choose your board in <b>'Platform Options'→'board'</b></li>
		<li><b>IMPORTANT:</b> Click <b>'Save'</b> in the upper right corner</li>
		</ul>
		</details>
		</blockquote>
	- Press **'Upload'** button in the upper right corner of VSCode window *(or press `Ctrl+Alt+U`)*

3. **On real Arduino via Arduino IDE**
	- Clone or [download](https://github.com/dakalamin/braille_display/archive/refs/heads/main.zip) and unpack the repository
	- Rename project's **`src`** folder to **`main`**
	- Rename **`main.cpp`** file to **`main.ino`**
	- Open **`main.ino`** with Arduino IDE *(make sure, that all .h files are shown the top tabs)*
		<blockquote>
		<b>Note:</b> make sure that all <b><code>.h</code></b> files are shown the top tabs
		</blockquote>
	- Connect your Arduino via USB to your computer
		<blockquote>
		<b>Note:</b> make sure to select your Arduino model in <b>'Tools'→'Board'</b>
		</blockquote>
	- Press **'Upload'** button in the upper left corner of Arduino IDE window *(or press `Ctrl+U`)*

## Usage

Send messages, that you want to translate and show, to the Serial Monitor.

Press the button to display the next set of Braille patterns.

## Features

- Program can translate following symbols into Braille:
	- **Latin** alphabet
	- **Cyrillic** alphabet
	- **Numbers**
	- frequently used **Punctuation**

- You can send messages one after another not waiting for the previous ones to be shown - program will try to concatenate them until the `rx_buffer` *(receiving buffer)* is full

- You can hold the button instead of repeatidly pressing it - program will display the next number of characters on the defined time interval

- You can easily scale the number of cells on the Braille display - the only change to the program you need to make is a single variable

- Program will keep the last part of the last message displayed until you send a new message and then press the button

- Program can process special cases of translating to Braille (e.g.: punctuation, modifiers, etc.)
	<blockquote>
	<details>
	<summary>Examples:</summary>
	<ul>
	<li>capital modifier is required before capital letters: <b><code>XyZ</code></b> → <b><code><ins>⠠</ins>⠭⠽<ins>⠠</ins>⠵</code></b></li>
	<li>numeric modifier is required before numbers: <b><code>a 12</code></b> → <b><code>⠁ <ins>⠼</ins>⠁⠃</code></b></li>
	<li><b>.</b> (dot) symbol has different translations:<ul>
	<li><b><code>N.o</code></b> → <b><code>⠠⠝<ins>⠲</ins>⠕</code></b> <i>(a grammatical dot)</i></li>
	<li><b><code>8.9</code></b> → <b><code>⠼⠓<ins>⠨</ins>⠊</code></b> <i>(a decimal dot)</i></li>
	</ul></li>
	<li><b>*</b> (asterisk) symbol is translated into a doubled <b>⠔</b> Braille pattern: <b><code>5 * 6</code></b>→ <b><code>⠼⠑ <ins>⠔⠔</ins> ⠼⠋</code></b></li>
	<li><b>"</b> (quote) symbol's Braille pattern alternates on opens and closes: <b><code>m "q" n</code></b> → <b><code>⠍ <ins>⠦</ins>⠟<ins>⠴</ins> ⠝</code></b></li>
	<li>quote, unpaired until EOM, can be paired automatically: <b><code>"k</code></b> → <b><code>⠦⠅<ins>⠴</ins></code></b></li>
	</ul>
	</details>
	</blockquote>

- Program doesn't process characters in advance - it translates the least neccessary amount of characters to fill the Braille display after you press the button

- Program can wait for the next messages if last symbols of the current one don't have enough context to be translated to Braille correctly
	<blockquote>
	<details>
	<summary>Examples:</summary>
	first comes <b><code>30<ins>.</ins></code></b> message
	<br>there is not enough context in the message for the <b>.</b> symbol to be translated to Braille
	<br>program sends <b><code>⠼⠉⠚</code></b> patterns to the display (without <b>.</b> symbol) and waits for the next message:
	<ul>
	<li>then comes <b><code>25</code></b> message → program shows <b><code><ins>⠨</ins>⠃⠑</code></b> <i>(decimal dot)</i></li>
	<b>-or-</b>
	<li>then comes <b><code> re</code></b> message → program shows <b><code><ins>⠲</ins>⠗⠑</code></b> <i>(grammatical dot)</i></li>
	</ul>
	</details>
	</blockquote>

## Todo

- Add Customization section to README
- Add Russian variant of README
- Add tests
- Add [PlatformIO CI](https://docs.platformio.org/en/latest/integration/ci/index.html)
- Optimize `nchar**_t` type for symbols with translation to Braille

## Contribution

Feel free to contribute to this project by submitting issues or pull requests!

## License

This project is open-source and available under the [MIT License](LICENSE)
