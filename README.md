# Shutter Controller

I have long appreciated the art of the timelapse. They can reveal motion in the world on timescales that are not normally perceptible like clouds forming and evaporating in the sky or the rotation of the Earth against the cosmos. In theory timelapses are simple enough to create: one only needs to capture a sequence of images and then stitch them together into the frames of a movie using freely available software. However one must also take the photographic parameters of shutter speed, ISO sensitivity and focal ratio (i.e. f-stop) into account.

One might think to use their camera’s automatic exposure mode to simplify the process, but this leads to a substantial drawback, oscillating exposure in the finished product:

<p align="center">
  <img src="/img/flicker.gif">
</p>
<p align="center">
   Flicker with AE
</p>

One may try to correct this by instead placing their camera in manual mode, so that each frame has identical exposure settings. But what if the environment brightness is itself changing? Say we start shooting a timelapse just before sunset and we expose the first frame properly. The frames are quickly going to become underexposed as the light level drops: 

<p align="center">
  <img src="/img/drastic.gif">
</p>
<p align="center">
   Fixed 1/20s shutter speed, f/13, ISO 50
</p>

We are in need of another technique.

Intervalometers make it easy to capture an image sequence automatically. They attach to the shutter cable port found on most semi-professional cameras and signal to the camera to fire the shutter at specified intervals. They allow the user to set a desired shutter speed, but only a select handful offer the possibility of varying the shutter speed throughout the sequence, a technique called bulb ramping. But even high-end intervalometers do not offer complete control over how the shutter speed changes. If they perform bulb ramping at all, they will only interpolate linearly between given starting and ending speeds.

The ambient brightness during sunrise and sunset actually follows an exponential curve, so if we want to shoot a well-exposed timelapse around those times we need to compensate with a complimentary exponential curve for the shutter speed. I will refer to this as nonlinear bulb ramping.