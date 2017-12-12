#! /bin/sh
# run Jaxx wallet in a docker container

docker build -t jaxx .
docker run -ti --rm \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v $HOME/.config/Jaxx:/home/docker/.config/Jaxx \
    jaxx    
