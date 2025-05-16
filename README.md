# 🔨 Mjölnir
Eine dekorative Leuchte angelehnt an Marvels Interpretation des Hammers Thors

## 📖 Dokumentation
[//]: # (- [Mjölnir dokumentation](doc/))
- [WLED Dokumentation](https://kno.wled.ge/) - ESP32 LED Firmware
- [LedFX Dokumentation](https://docs.ledfx.app/en/stable/) - Rhythmuserkennungssoftware

## 🚀 Erste Schritte
### 🛠️ Systemkonfiguration
- [x] [ESP32](https://amzn.eu/d/4D6PdJC) mit [WLED Firmware](https://github.com/wled/WLED/releases/latest) [flashen](kno.wled.ge/basics/install-binary/)
- [x] [ATTiny85 / Digispark USB](https://amzn.eu/d/9wXMY9x) mit [USB-C Supervisor Firmware](software/usb_controller/) [flashen](https://www.instructables.com/How-to-Program-an-ATtiny-85-Digispark/)
- [x] Verbinden mit AP des ESP32
    - Netzwerkname: ```WLED-AP```
    - Passwort: ```wled1234```
- [x] Navigiere zu (http://4.3.2.1/settings/sec)
    - [x] Hochladen der [Preset-Konfigurationsdatei](config/wled_presets_Mjoelnir.json) unter "Restore presets"
    - [x] Hochladen der [System-Konfigurationsdatei](config/wled_cfg_Mjoelnir.json) unter "Restore configuration"
### 🛜 WLAN Konfiguration
- [ ] Verbinden mit neuem AP des ESP32
    - Netzwerkname: ```Mjoelnir```
    - Passwort: ```wled1234```
- [ ] Navigiere zu (http://mjoelnir.local/settings/wifi)
    - [ ] Scannen nach verfügbaren Netzwerken
    - [ ] Auswählen des eigenen Netzwerkes / WLANs aus Dropdown unter "Network name"
    - [ ] Passwort des gewählten Netzwerkes unter "Network password" eintragen
    - [ ] Bestätigen durch "Save & Connect"
### 💡 Nutzung
- [ ] Während Verbindung mit Heimnetzwerk besteht: Navigiere zu (http://mjoelnir.local)