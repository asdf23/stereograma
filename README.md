# Stereograma
This is a **FREE** open source cross-platform [**stereogram maker**/**stereogram creator**/**stereogram generator**/**stereogram renderer**] written in C++ using Qt. It aims to be fast, accurate, easy to use and multifunctional piece of software, as it uses the **best** algorithm (by W.A. Steer PhD) for generating auto-stereograms (see [algorithm.pdf](algorithm.pdf)). It can even load 3D models in the .obj and .ply file formats. It also comes with some depth maps and textures so you can start to play from the first moment. One cool feature which is very unique is that it includes an interactive diagram that shows the depths of the resulted image, according to the rendering parameters.

There is also an interface for combining two pictures taken from different angles into anaglyph.

### Where to download?

visit that link: https://kapandaria.wordpress.com/stereograma/

### How to build:

Since it was developed with QtCreator, you can generate a makefile from the .pro file with qmake, or just compile it from within the IDE.
make && qmake

Forked from https://github.com/gnudles/stereograma.git adds cli

