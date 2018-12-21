FROM debian:stretch

MAINTAINER DESY, Jan Kotanski <jankotan@gmail.com>

RUN /bin/bash -c 'echo "deb http://ftp.de.debian.org/debian stretch main" > /etc/apt/sources.list.d/debian9de.list'

RUN apt-get -qq update && apt-get -qq install -y libterm-readline-gnu-perl software-properties-common coreutils gnupg2 procps apt-utils curl apt-transport-https gnupg2 ca-certificates

RUN curl http://repos.pni-hdri.de/debian_repo.pub.gpg | apt-key add -
RUN add-apt-repository "deb http://repos.pni-hdri.de/apt/debian stretch main" -y
RUN apt-get -qq update && apt-get -qq -y dist-upgrade

RUN apt-get -y install cmake ninja-build python-pip
RUN apt-get -y install g++ doxygen python-sphinx
RUN apt-get -y install git
RUN apt-get -y install libboost-all-dev
RUN apt-get -y install gfortran
RUN apt-get clean
RUN pip install conan
RUN pip install gitpython
RUN conan remote remove conan-center
# RUN conan remote remove conan-transit
RUN conan remote add conan-community https://api.bintray.com/conan/conan-community/conan
RUN conan remote add conan-center https://conan.bintray.com
RUN conan remote add conan-transit https://conan-transit.bintray.com
RUN conan user
RUN mkdir /src