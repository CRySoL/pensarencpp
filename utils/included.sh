#!/bin/bash
grep "xi:include" $1 | grep -v "^<\!--" | cut -d'"' -f2
