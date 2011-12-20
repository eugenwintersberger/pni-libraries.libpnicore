#!/bin/bash

scons -c debian
scons PREFIX=/usr debian
dpkg-buildpackage -uc -us -b 
mv ../libpniutils*.* .
