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
echo "> ls -al /usr/include/vte"
ls -al /usr/include/vte
exit 0
