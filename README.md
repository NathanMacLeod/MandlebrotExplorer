# MandlebrotExplorer
Simple program that allows limited navigation of the mandlebrot set. I programmed as kind of a warm up to try using the pixel game engine: https://github.com/OneLoneCoder/olcPixelGameEngine
I thought it was pretty neat though so I decided to upload it.
Navigation is done by left clicks to zoom in, right clicks to zoom out.

To make it run a bit faster I made it use multiple cpu threads, I just hardcoded it to 12 at the top of olcExampleProgram.cpp which worked well for me. Itd probably work much better if it utilized the gpu but I haven't done that.

setting DEEP_ZOOM to true will make it automatically zoom in the coordinate defined in onUserUpdate()
