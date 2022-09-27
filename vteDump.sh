#!/bin/sh
echo "> pkg-config --list-all|grep vte"
pkg-config --list-all|grep vte
echo "> pkg-config --modversion vte-2.91"
pkg-config --modversion vte-2.91
echo "> pkg-config --modversion vte291"
pkg-config --modversion vte291
echo "> pkg-config --modversion libvte"
pkg-config --modversion libvte
echo "> pkg-config --modversion vte"
pkg-config --modversion vte
echo "> ls -al /usr/include/vte-291"
ls -al /usr/include/vte-2.91
echo "for https://github.com/nonstop/termit/issues/125#issuecomment-1254119382"
echo "> pkg-config --cflags vte-2.91"
pkg-config --cflags vte-2.91
echo "> pkg-config --libs vte-2.91"
pkg-config --libs vte-2.91
echo "> find /usr/include -name vte -type d"
find /usr/include -name vte -type d
echo "> ls -l /usr/include/vte-2.91/vte"
ls -l /usr/include/vte-2.91/vte
exit 0
