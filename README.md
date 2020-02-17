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

<!--
An intervalometer is a remote control for a camera. It is a small computer that repeatedly tells the camera to open the shutter and how long to keep it open. An intervalometer is an essential tool for creating timelapses. Most intervalometers will allow the user to select any shutter speed and any interval within the model's particular limitations, but few will vary the shutter speed with each frame, a technique called bulb ramping. Bulb ramping is useful when the amount of ambient light is changing, such as sunrise or sunset.

Shooting a timelapse at sunset in manual mode without bulb ramping: if the first few frames are well-exposed, subsequent frames quickly become underexposed.



Most DSLR or mirrorless cameras have an aperture-priority (Av) mode that can cope with this large change in brightness by  varying the shutter speed, but the brightness recorded in the camera will appear to oscillate rather than changing smoothly as one would expect from a sunrise or sunset. This flicker effect is jarring and not realistic:

### Advanced off-the-shelf control
High-end intervalometers usually can perform bulb ramping, but they will generally use a linear ramp, where the incremental change in exposure time is constant. A linear ramp can't keep up with the rate at which the ambient light changes during sunrise or sunset, which makes the final image brightness do this:

<p align="center">
  <img src="/img/plot1.png">
</p>

I tested a high-end intervalometer, a MIOPS Mobile Remote, and while it eliminated the flicker, it had the predicted bump. This test is described in [this Mathematica notebook](https://github.com/brayvid/Timelapses/blob/master/linear_problem.nb) [[PDF](https://github.com/brayvid/Timelapses/blob/master/linear_problem.pdf)].

<p align="left">
  <img src="/img/linear.gif">
</>
<p align="center">
   Observed bump with a linear ramp
</p>

### Custom control
I assumed that the ambient brightness after sunset follows an exponential curve consistent with astronomical data:
```
BrightnessWithAngle[θ_,min_,max_,rate_]:=(max-min)Exp[-rate θ]+min
```
Based on this assumption, I wrote code in [this Mathematica notebook](https://github.com/brayvid/Timelapses/blob/master/better_ramp.nb) [[PDF](https://github.com/brayvid/Timelapses/blob/master/better_ramp.pdf)] that computes the sequence of exposure times required for the final timelapse to have constant brightness. 

Here is an example scene brightness curve for sunset:

<p align="center">
  <img src="/img/plot2.png">
</p>

Here is a ramp function designed to compensate for the above decay. The parameters used here are: 900 frames, hours elapsed = 4, iso 160, aperture diameter = 10mm. One graph is plotted with time, and one with frame number.

<p align="center">
  <img src="/img/plot3.png">
</p>


<p align="center">
  <img src="/img/plot4.png">
</p> -->

The task now is to develop an Arduino-based shutter controller that takes as arguments a list of exposure times and a few other parameters and fires the shutter accordingly.

Here is a working Arduino-based prototype:

<p align="center">
  <img src="/img/prototype.jpg">
</p>
<p align="center">
1) Arduino Uno R3; 2) Shutter release circuit (transistor, 2 resistors); 3) 2.5mm TRS adapter (autofocus line unused); 4) Shutter release cable with 2.5mm TRS connector; 5) Buttons for user input; 6) 4x7-segment display module
</p>

Here it is in action:

<p align="left">
  <img src="/img/prototype.gif">
</p>

While the image brightness is not constant (yet), there is a noticeable improvement in how long the light lasts for. More work is needed to exactly compensate for the changing environment.







