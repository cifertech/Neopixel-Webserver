# Neopixel-Webserver
Wireless control of neopixel LEDs by building a web server with ESP8266 board.

## What it DO!
In the neopixel LED wireless control project, by building a web server with ESP8266 board, we can have complete control over our neopixel ring module and the values related to the main colors, ie red, blue, green, in the scale of 0 to 255 To change, there is also a color plot on the web server that we can visually select the desired color.

### Make it Portable
To make the LED wireless control project portable, just use the wemos board with the battery charging shield. The battery shield allows the user to portable their IoT project, so that by connecting the shield to the Wemos board and connecting the battery from the relevant connector, in addition to the portable size of the project, you can charge the battery. do. The lithium battery suitable for this shield is in the voltage range of 3.3 to 4.2.

### Items needed
-Neopixel Ring
-ESP8266
-Wemos

### Required libraries
-Adafruit_NeoPixel
-ESP8266WiFi

## Conclusion
Finally, after uploading the code on the desired board, by resetting the board, you will be able to find the ip related to the created web page in the Arduino monitor serial, and by searching it in your browser, you can access the web server. In this tutorial, using the ESP8266 board and the Neopixel Ring module, we were able to change the values of R, G, B in the neopixel module in real time and using a web page. Also, using the wemos board with the battery shield, this project Turn it into a portable circuit.

Full Tutorial at http://cifertech.net/control-neopixel-with-esp8266/
