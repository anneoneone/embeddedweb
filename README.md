# embeddedweb

## 2. Aufgabe: GPIO devices
Schreiben Sie ein C-Programm, um eine LED an einem GPIO-Port auf einem Raspberry Pi ein- oder auszuschalten. Verwenden Sie dazu GPIO devices (/dev/gpiochipNNN). Verwenden Sie nicht das sysfs (/sys/class/...)

Falls Sie einen physischen Raspberry Pi benutzen: Schließen Sie die LED mit einem Vorwiderstand an einem GPIO-Port des Raspberry Pi an.

Die Device-Schnittstelle ist z.B. in [diesem Artikel](https://embeddedbits.org/new-linux-kernel-gpio-user-space-interface/) beschrieben. Obwohl es möglich ist, diese Gerätedateien [direkt](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/Documentation/driver-api/gpio/using-gpio.rst) über ioctl-Aufrufe zu bedienen, wird der Zugriff über [libgpiod](https://www.ics.com/blog/gpio-programming-exploring-libgpiod-library) empfohlen. Für bestimmte an einen GPIO-Port angeschlossene Geräte (insbesondere LEDs) gibt es spezifische Treiber (die dann z.B. über /sys/class/leds verfügbar sind). Sie können diese Treiber zum Test Ihres Aufbaus verwenden; die eigentliche Lösung der Aufgabe sollte trotzdem libgpiod verwenden.
