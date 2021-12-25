# MandlebrotExplorer
Simple program that allows limited navigation of the mandlebrot set. I programmed as kind of a warm up to try using the pixel game engine: https://github.com/OneLoneCoder/olcPixelGameEngine
I thought it was pretty neat though so I decided to upload it.
Navigation is done by left clicks to zoom in, right clicks to zoom out.

To make it run a bit faster I made it use multiple cpu threads. I just hardcoded it to use 12 threads, which worked well for me. It is defined at the top of olcExampleProgram.cpp if you want to change it. Itd probably work much better if it utilized the gpu but I haven't done that.

setting DEEP_ZOOM to true will make it automatically zoom in the coordinate defined in onUserUpdate()

Click to view a demo on my Youtube channel:

[![Gameplay](https://img.youtube.com/vi/DtTY8uucYuw/0.jpg)](https://www.youtube.com/watch?v=DtTY8uucYuw)
