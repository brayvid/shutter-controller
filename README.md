# Shutter Controller

## Introduction
I have long appreciated the art of timelapses. They can reveal motion in the world on timescales that are not normally noticeable like clouds forming and evaporating in the sky or the Earth rotating against the cosmos. In theory, timelapses are simple enough to create: one simply captures a sequence of images and then stitches them together into the frames of a movie using free software. However in practice I have found them tricky to make well.

## Exposure problem
In many environments, particularly those I want to record in, the ambient illumination changes during capture. Since I am most interested in making timelapses with a roughly constant apparent brightness, the camera's manual mode is not an option as it doesn't adapt to anything:
<p align="center">
  <img src="img/drastic.gif" width="100%">
    <p align="center">
   Manual mode
</p>
</p>
</br>

Automatic exposure (AE) mode is also not viable because it causes the frames to flicker jarringly:
</br>

<p align="center">
  <img src="img/flicker.gif" width="100%">
  <p align="center">
   AE mode
</p>
</p>

## Bulb ramping
Select intervalometer models offer the possibility of varying the shutter speed throughout the capture sequence, a technique called bulb ramping. But even these do not offer complete control over how the shutter speed changes. They will only interpolate linearly between given starting and ending speeds. 

The ambient brightness during sunrise and sunset does not follow a straight line, it follows an exponential curve, so to shoot a well-exposed timelapse around those times one must compensate with a complimentary exponential shutter speed curve. Nonlinear bulb ramping is needed.

## Customization
I'd like to have a controller that can vary the camera's shutter speed along a smooth curve that is inspired by real-world data but not computed by AE on the fly. I will provide this function and build the controller myself.