#!/usr/bin/env python 
'''
Copyright (C) 2010 David Turner <novalis@novalis.org>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St Fifth Floor, Boston, MA 02139
'''
import inkex, simplepath

import sys


class RemoveRedundant(inkex.Effect):
    def __init__(self):
        inkex.Effect.__init__(self)

    def effect(self):

        pathTag = inkex.addNS('path','svg')

        for id, node in self.selected.iteritems():
            if node.tag == pathTag:
                d = node.get('d')
                path = simplepath.parsePath(d)
                newPath = []
                start = prev = None
                seenSegments = set()
                pathclosed = True
                for command, coords in path:
                    tcoords = tuple(coords)
                    if command == 'M':
                        newPath.append([command, coords])
                        start = prev = tcoords
                        pathclosed = True
                    elif command == 'L':
                        if ('L', prev, tcoords) in seenSegments or \
                           ('L', tcoords, prev) in seenSegments:
                            newPath.append(['M', coords])
                            pathclosed = False
                        else:
                            newPath.append([command, coords])
                            seenSegments.add(('L', prev, tcoords))
                        prev = tcoords
                    elif command == 'Z':
                        if ('L', prev, start) in seenSegments or \
                           ('L', start, prev) in seenSegments:
                            newPath.append(['M', start])
                        else:
                            if pathclosed:
                                newPath.append([command, coords])
                            else:
                                newPath.append(['L', start])
                            seenSegments.add(('L', prev, start))
                        prev = start
                    elif command == 'C':
                        if ('C', prev, tcoords) in seenSegments or \
                           ('C', tcoords[4:], (tcoords[2:4], tcoords[0:2], prev)) in seenSegments:
                            newPath.append(['M', coords[4:]])
                        else:
                            newPath.append(['C', coords])
                            seenSegments.add(('C', prev, tcoords))
                        prev = tcoords[4:]                        
                    else:
                        newPath.append([command, coords])
                while len(newPath) and newPath[-1][0] == 'M':
                    newPath = newPath[:-1]
                node.set('d',simplepath.formatPath(newPath))


e = RemoveRedundant()
e.affect()
