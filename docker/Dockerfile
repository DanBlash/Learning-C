FROM ubuntu:latest

RUN apt-get update && apt-get upgrade -y

RUN apt-get install -y \ 
    gcc-11 \ 
    libncurses-dev

RUN gcc-11 Snake_Game.c -o /opt/Snake_Game -lncurses

ENTRYPOINT [ "/opt/Snake_Game" ]
