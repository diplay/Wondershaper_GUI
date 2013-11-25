all: compile

install: compile
	cp speed /usr/bin/speed
	chmod +x /usr/bin/speed
	echo "[Desktop Entry]\n\
	Exec=gksu /usr/bin/speed\n\
	Icon=/usr/share/pixmaps/gksu.png\n\
	Terminal=false\n\
	Type=Application\n\
	Categories=Network;Settings;\n\
	Name[ru_RU]=Speed\n\
	Name=Speed" > /usr/share/applications/speed.desktop

uninstall:
	rm -f /usr/bin/speed
	rm -f /usr/share/applications/speed.desktop

clean:
	rm -f speed

compile:
	gcc -Wall -g speed.c -o speed `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
