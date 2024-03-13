# Adding a Filesystem

## Adding littlefs Using Arduino IDE 1

Install
https://github.com/earlephilhower/arduino-esp8266littlefs-plugin.

Move the files you want available in your filesystem to the `/data` folder of your sketch.

From the `tools` menu, select `ESP8266 LittleFS Data Upload`.

## Creating a littlefs Image

To upload a littlefs image using the upload server, you need to create a littlefs `.bin` image.

Install a copy of [mklittlefs](https://github.com/earlephilhower/mklittlefs).

Create a littlefs image of a folder containg the files you want to use:

```shell
mklittlefs --create "<PATH_TO_FOLDER>" "<OUTPUT_FILE.BIN>" --size 512000 -b 8192 -p 256
```
(These settings are defined in `board.txt` definition file of the ESP8266 Core.)

Upload the resulting `.bin` file using the [update server](#) or using [esptool](#uploading-using-esptool).

## Uploading using esptool

First, install [esptool](https://github.com/espressif/esptool).

Then run:

```shell
esptool.py --chip esp8266 --port PORT --baud 512000 write_flash 0x200000 IMAGE_PATH
```

(These settings can be obtained when uploading the `/data` folder of your sketch using the [Arduino IDE plugin](#uploading-a-littlefs-image-using-arduino-ide-1).)
