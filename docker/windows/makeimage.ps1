# use this for building the docker image on windows

$IMAGE_NAME = "snake_game"
$IMAGE_TAG = "latest"

$IMAGE_FULL_NAME = "${IMAGE_NAME}:${IMAGE_TAG}"

docker build -t ${IMAGE_FULL_NAME} ../