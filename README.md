# gravitysimcpp

WIP

c++ version of gravitysim done in python

To build the image run the command:
- docker build --network=host .

To run the containerized version, need to run the following commands:
- xhost +Local:*
- docker run --net=host -e DISPLAY=$DISPLAY {image id}
