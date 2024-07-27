# CTA Train Tracker with Arduino
This is a toy example of using the CTA train tracker API to pull and display information via Arduino Uno R4 WiFi.

## Step 1
Apply for an API key at https://www.transitchicago.com/developers/traintrackerapply/. I received mine within minutes. Do not ever share or publicly commit your API key!

## Step 2
Clone this repo and populate the arduino_secrets.h file with your private information, including WiFi name, password, and your API key.

To customize the stop you're pulling information about, see CTA's reference documentation at https://www.transitchicago.com/developers/ttdocs/#_Toc296199903.

## Step 3
Run the code on your Arduino R4 and inspect the Serial Monitor for results. If you'd like to surface the results to an interface such as an LCD, see the circuit schematic below. See the LCD library reference at arduino.cc/lcdlibrary for more information.

![Circuit Diagram from Arduino](https://docs.arduino.cc/static/7d7b6e99f40c7e55f2e9c6175c6db5b5/a6d36/LCD_Base_bb_Fritz.png)



