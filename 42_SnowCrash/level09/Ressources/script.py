#!/usr/bin/env python3
import sys

# get args by `cat token` and encode it.
# 'surrogateescape' for surrogate error
value = sys.argv[1].encode(errors='surrogateescape')

# parse the values get in token
new_value = ''.join([chr(v - i) for i, v in enumerate(value)])

# print new values
print(new_value)
