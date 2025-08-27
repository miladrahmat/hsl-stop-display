# HSL bus stop display

<p align=center>
  <b>A bus stop display project using the Digitransit Routing API.</b>
</p>

## Content
- [Introduction](#introduction)
- [Features](#features)
- [Hardware and requirements](#hardware-and-requirements)
- [Installation](#installation)


## Introduction

This project is an Arduino-based HSL bus stop display that shows the **next 2 buses** departing from the **Merihaka bus stop** in Helsinki, using the **Digitransit Routing API**. The display refreshes every minute to keep the departure times up-to-date in real time.

This project is a part of [Hive Helsinki's](https://www.hive.fi/en/) Embedded System Workshop and the goal is to learn how to fetch data from an API and how to parse the data received from the API.

## Features
- Fetches live departure data from the [Digitransit Routing API](https://digitransit.fi/en/developers/apis/1-routing-api/).
- Displays the next 2 buses leaving from the Merihaka bus stop.
- Automatically refreshes every 60 seconds
- Runs on a microcontroller with a display

## Hardware and requirements
- NodeMCU single-board microcontroller with WiFi support (ESP8266)
- SSD1306 OLED screen
- Internet connection (via WiFi)
- Digitransit API access

## Installation

1. To install and test this project, make sure that **Arduino** is installed. Read the documentation and follow the instructions [here](https://docs.arduino.cc/software/ide-v1/tutorials/Environment/?_gl=1*1xunddk*_up*MQ..*_ga*MzUxNTM5NjU3LjE3NTYyODY2OTc.*_ga_NEXN8H46L5*czE3NTYyODY2OTYkbzEkZzEkdDE3NTYyODY3NDIkajE0JGwwJGg0NzIyMDYyNzM.)
2. Install required Arduino libraries:
    - `ESP8266WiFi` (to connect to the internet)
    - `HTTPClient` (to fetch API data)
    - `ArduinoJson` (to parse the API data)
    - `U8g2` (Display library)
  
3. Navigate to the desired directory and clone the repository:
   ```bash
   git clone https://github.com/miladrahmat/hsl-stop-display.git
   cd hsl-bus-display
   ```
4. Get an API key from [Digitransit](https://digitransit.fi/en/developers/api-registration/)
5. Open the `.ino` file in **Arduino IDE** and add your API key and WiFi connection information.
6. Upload the code to your NodeMCU or Arduino board.
