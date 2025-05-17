# USB-C Supervisor Firmware

## 🎯 Verwendungzweck
- Überwacht Kapabilitäten der verwendeten Spannungsquqelle
- Verhindert Zerstörung der Spannungsquelle
- Sorgt für Einhaltung der USB-C-Guidlines

## 🛠️ Kompilation und Upload der Firmware
Zur Kompilation wird das [PlatformIO](https://platformio.org/) Tool verwendet. <br>
Der Upload auf den [ATTiny85 / Digispark USB](https://amzn.eu/d/9wXMY9x) erfolgt über ISP mithilfe eines [Arduino Unos](https://store.arduino.cc/products/arduino-uno-rev3)
![Schaltplan zur Programmierung des Digispark USB](doc/digispark_usb_isp.png)

Stelle nach Anschluss des Arduino Unos an deinen Computer sicher, dass der Wert der Option `upload_port` in der [platformio.ini](software/usb_controller/platformio.ini) Konfigurationsdatei dem [Port des Arduinos](https://www.mathworks.com/help/matlab/supportpkg/find-arduino-port-on-windows-mac-and-linux.html) entspricht.
Flashe anschließend die [ArduinoISP Firmware](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP/) auf den Arduino Uno.

### Visual Studio Code
Stelle sicher, dass die [PlatformIO Extension für VSCode](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) installiert ist.

Öffne den Ordner [software/usb_controller/](software/usb_controller/) in VSCode.

Starte den Kompilations- und Uploadprozess über die Tastenkombination `CTRL+ALT+U`

### PlatformIO-Core
Navigiere im Terminal in den Ordner [software/usb_controller/](software/usb_controller/)
```console
cd software/usb_controller
```
Starte den Kompilations- und Uploadprozess mit
```console
platformio run -t upload
```