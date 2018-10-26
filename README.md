# WaveParser

This project is mainly proposed to parse wave file into struct. For example, you can exact raw PCM data to a new file. 

## Wave file format

You can look up the standard of the midi file format [here](http://soundfile.sapp.org/doc/WaveFormat/)

## play

You can play wave file using `play(Wave *)` in [play.h](external/play.h) (implement with [openal](http://openal-soft.org/))

## license

```license
Copyright (C) 2018  PinkD

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
```
