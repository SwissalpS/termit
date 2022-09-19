#!/bin/sh
pkg-config --list-all|grep vte
echo "----------------------------------"
pkg-config --modversion vte-2.91
echo "----------------------------------"
pkg-config --modversion vte291
echo "----------------------------------"
pkg-config --modversion libvte
echo "----------------------------------"
pkg-config --modversion vte
echo "----------------------------------"
exit 0
