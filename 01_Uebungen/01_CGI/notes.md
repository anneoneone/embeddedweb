## Aufgabe 1: CGI

### Schritte um Aufgabe zu lösen

1. Raspios runterladen, auf die SD Karte Flashen, Pi booten
2. Pi einrichten (User, Locale, Netzwerk, SSH, etc.)
3. Apache Webserver einrichten   
    3.1 Apache installieren `sudo apt install apache2`  
    3.2 Testen ob der Webserver läuft (am PC *http://uni-pi.fritz.box* aufrufen). Standard Apache Website wird gezeigt -> Webserver läuft.
4. CGI einrichten   
    4.1 in `/usr/lib/cgi-bin` das Skript speichern (z.B. als `env.cgi`)   
    4.2 das Skript ausführbar machen`sudo chmod +x env.cgi`   
    4.3 Das CGI Modul aktivieren `sudo a2enmod` (Apache2 enable module) -> cgi/cgid auswählen   
    4.4 Es braucht keine weitere Konfiguration damit das Skript gefunden wird, da Apache`/usr/lib/cgi-bin` als Standardpfad konfiguriert hat   
5. Webserver neu starten `sudo service apache2 reload`
6. Testen -> *http://uni-pi.frit.box/cgi-bin/env.cgi*  im Browser aufrufen   
7. Im Browser werden die Umgebungsvariablen angezeigt -> funktioniert
