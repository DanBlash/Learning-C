#!/usr/bin/bash
# use this for building the image on linux

IMAGE_NAME = "snake_game"
IMAGE_TAG = "latest"

IMAGE_FULL_NAME = $IMAGE_NAME:$IMAGE_TAG

docker build -t $(IMAGE_FULL_NAME) ../