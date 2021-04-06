#!/usr/bin/env python
#
# Script to find the list of 'make' options from the CMake cache and output to stdout. This is
# used to dump the available options for 'make help'.
#

import os.path
import sys
import re
import subprocess

# Usage for the script
def usage():
    print "usage: " + os.path.basename(sys.argv[0]) + " <list type> <build path>"
    print "  list type      - Type of option list (e.g. normal or debug)"
    print "  build path     - Top of the build object tree (e.g. build/embedded-<platform>)"
    print
    exit(1)

# Get the parameters
list_type = sys.argv[1]
cache_path = os.path.join(sys.argv[2], "CMakeCache.txt")

# There is nothing to output if the build path does not exist
if not os.path.exists(cache_path):
    exit(0)

# Look for the variables we want from the cache file. If these exist, they will be CMake lists (';' delimeter)
search_base = "BCM_" + list_type.upper() + "_"
file = open(cache_path, "r")
options = []
descriptions = []
values = []

cache_contents = file.readlines()

for line in cache_contents:
    if re.search(search_base + "OPTIONS", line):
        options = line.replace(search_base + "OPTIONS:STRING=", "").strip().split(';')
    if re.search(search_base + "DESCRIPTIONS", line):
        descriptions = line.replace(search_base + "DESCRIPTIONS:STRING=", "").strip().split(';')

# Next go through the cache_contents and find the current value for variables.
for option in options:
    r = re.compile(option + ":.*=")
    option_line = filter(r.match, cache_contents)[0].strip()
    values.append(r.sub("", option_line))

# At this point if the cache had the values we have two lists, one with the option and one with the description
for idx, val in enumerate(options):
    print("   %-25s - %s [current='%s']" % (val, descriptions[idx], values[idx]))

exit(0)
