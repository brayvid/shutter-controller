# Shutter Controller

## Introduction
I have long appreciated the art of making timelapses. They can reveal motion in the world on timescales that are not normally noticeable like clouds forming and evaporating in the sky or the Earth rotating against the stars. In theory, timelapses are simple enough to create: one simply captures a sequence of images and stitches them together into the frames of a movie using free software. However in practice I have found them tricky to make well.

## Exposure problem
In the environments in which I want to record the ambient brightness will be continuously changing. I want timelapses with a roughly constant apparent brightness, so I can't use the manual mode on my camera as it won't adapt to the changes:
<p align="center">
  <img src="img/drastic.gif" width="100%">
    <p align="center">
   Manual mode
</p>
</p>
</br>

Automatic exposure (AE) mode isn't an option either because it causes the frames to flicker:
</br>

<p align="center">
  <img src="img/flicker.gif" width="100%">
  <p align="center">
   AE mode
</p>
</p>

## Nonlinearity of the problem
The ambient brightness throughout sunrise and sunset does not follow a straight line with respect to time. Instead, it forms a logistic curve:
<p align="center">
  <img src="img/brightness.png" width="100%">
  <p align="center">
   Brightness with respect to time inferred from real-world data
</p>
</p>
</br>
To shoot well-exposed timelapses around these times I will compensate by using a complimentary shutter speed curve:
<p align="center">
  <img src="img/shutter.png" width="100%">
  <p align="center">
   Shutter speed required to maintain a constant image brightness (range: ~15s to ~1/320s)
</p>
</p>

## Intervalometers
Certain models of intervalometer offer the possibility of varying the shutter speed during the capture sequence, but none offer enough control over how the shutter speed changes. They will only interpolate linearly between given starting and ending speeds, which is much too slow for this purpose.


## Custom control
Stay tuned for more.