FROM cimg/base:stable

RUN apt-get update
RUN apt-get install libgtest-dev
RUN apt-get install cmake
