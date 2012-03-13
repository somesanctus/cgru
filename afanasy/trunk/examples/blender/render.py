#!/usr/bin/python2.5
# coding=utf8

import os
import af

job = af.Job('Blender Test')

block = af.Block('render', 'blender')
block.setCommand('./blender -b scene.blend -s %1 -e %2 -a')
block.setNumeric( 1, 20, 2)

job.blocks.append( block)

print
job.output( True)
print

job.send()
