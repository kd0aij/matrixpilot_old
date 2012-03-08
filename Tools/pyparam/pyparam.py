#!/usr/bin/env python

'''
Use pyparam to generate MatrixPilot mavlink parameter and nv memory tables from XML database description

Copyright Matthew Coleman 2012
Released under GNU GPL version 3 or later
'''

import os, sys, glob, re

# allow import from the MAVlink/pymavlink directory, where mavutil.py is
#sys.path.insert(0, os.path.join(os.path.dirname(os.path.realpath(__file__)), '../MAVLink/pymavlink'))

