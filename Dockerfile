FROM ubuntu:latest

RUN apt-get update && apt-get install -y wget ninja-build \
    build-essential cmake git python3 python3-pip

WORKDIR /home
COPY . /home

RUN ./download.sh
RUN ./setup.sh
RUN ./configure.sh
RUN ./build.sh