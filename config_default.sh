#! /bin/sh

PKGNAME="ffmpegyag"
PKGVERSION="0.6.0"
PKGSECTION="video"
PKGAUTHOR="Ronny Wegener <wegener.ronny@gmail.com>"
PKGHOMEAGE="http://ffmpegyag.googlecode.com"
PKGDEPENDS="ffmpeg"
PKGDESCRIPTION="A GTK based GUI for ffmpeg
 FFmpegYAG is a GUI for the popular FFmpeg audio/video encoding tool"

SRCPATTERN="*.cpp"
SRCDIR="src"
OBJDIR="obj"
DISTROOT="dist/linux"
BINFILE="$DISTROOT/usr/bin/$PKGNAME"

CC="g++"
CFLAGS="
	-c
	-Wall
	-O2
	$(wx-config --static=yes --debug=no --cflags)
	"

LD="g++"
LDFLAGS="-s"
LDLIBS="
	$(wx-config --static=yes --debug=no --libs --gl-libs)
	-lavformat
	-lavcodec
	-lswscale
	"
