# embeddedweb

## 1. Aufgabe: CGI
1. Richten Sie Raspbian ein, entweder auf einem Raspberry Pi oder in einer virtuellen Maschine.
2. Richten Sie eine Internetverbindung für dieses Gerät ein.
3. Richten Sie  einen Webserver (z.B. Apache) ein.
4. Konfigurieren Sie den Webserver derart, dass unten stehendes CGI-Skript ausgeführt werden kann.
5. Testen Sie den Zugriff auf das Skript.

Geben Sie in Moodle eine Beschreibung aller Installationsschritte an, die Sie durchgeführt haben (z.B. Kommandos, die Sie ausgeführt haben und Textzeilen, die Sie in Konfigurationsdateien geschrieben haben). Berichten Sie die Ausgabe der Webseite.

Hier das CGI-Skript
```
#!/bin/sh
echo "Content-type: text/plain"
echo
env|sort
```

## 2. Aufgabe: GPIO devices
Schreiben Sie ein C-Programm, um eine LED an einem GPIO-Port auf einem Raspberry Pi ein- oder auszuschalten. Verwenden Sie dazu GPIO devices (/dev/gpiochipNNN). Verwenden Sie nicht das sysfs (/sys/class/...)

Falls Sie einen physischen Raspberry Pi benutzen: Schließen Sie die LED mit einem Vorwiderstand an einem GPIO-Port des Raspberry Pi an.

Die Device-Schnittstelle ist z.B. in [diesem Artikel](https://embeddedbits.org/new-linux-kernel-gpio-user-space-interface/) beschrieben. Obwohl es möglich ist, diese Gerätedateien [direkt](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/Documentation/driver-api/gpio/using-gpio.rst) über ioctl-Aufrufe zu bedienen, wird der Zugriff über [libgpiod](https://www.ics.com/blog/gpio-programming-exploring-libgpiod-library) empfohlen. Für bestimmte an einen GPIO-Port angeschlossene Geräte (insbesondere LEDs) gibt es spezifische Treiber (die dann z.B. über /sys/class/leds verfügbar sind). Sie können diese Treiber zum Test Ihres Aufbaus verwenden; die eigentliche Lösung der Aufgabe sollte trotzdem libgpiod verwenden.

## 3. Aufgabe: GPIO-Sensor
1. Verbinden Sie einen Sensor (z.B. DHT11) mit einem GPIO-Port des Raspberry. 
2. Schreiben Sie ein CGI-Skript, das den Sensor-Wert als HTTP-JSON-Antwort ausgibt.
3. Schreiben Sie eine Webseite, die den aktuellen Sensorwert (z.B. die Raumtemperatur) anzeigt und per AJAX regelmäßig (z.B. alle 5s) aktualisiert.
