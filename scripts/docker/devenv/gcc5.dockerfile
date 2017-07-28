FROM ubuntu:16.04

RUN apt-get -q update && apt-get install -qy \
    g++-5 \
    cmake \
    git \
    libleveldb-dev \
    libmicrohttpd-dev \
 && rm -rf /var/lib/apt/lists/*
