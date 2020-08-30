# MandlebrotExplorer
Simple program that allows limited navigation of the mandlebrot set. I programmed as kind of a warm up to try using the pixel game engine: https://github.com/OneLoneCoder/olcPixelGameEngine

To make it run a bit faster I made it use multiple cpu threads, I just hardcoded it to 12 at the top of olcExampleProgram.cpp which worked well for me. Itd probably work much better
if it utilized the gpu but I haven't done that.
