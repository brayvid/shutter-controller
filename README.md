# Basic shutter control
An intervalometer is a remote control for a camera. It is a small computer that repeatedly tells the camera to open the shutter and how long to keep it open. An intervalometer is an essential tool for creating timelapses. Most intervalometers will allow the user to select any shutter speed and any interval within the model's particular limitations, but few will vary the shutter speed with each frame, a technique called bulb ramping. Bulb ramping is useful when the amount of ambient light is changing, such as sunrise or sunset.

Shooting a timelapse at sunset in manual mode without bulb ramping: if the first few frames are well-exposed, subsequent frames quickly become underexposed.

<p align="left">
  <img src="/img/drastic.gif">
</p>
<p align="center">
   Fixed 1/20s shutter speed, f/13, ISO 50
</p>

Most DSLR or mirrorless cameras have an aperture-priority (Av) mode that can cope with this large change in brightness by  varying the shutter speed, but the brightness recorded in the camera will appear to oscillate rather than changing smoothly as one would expect from a sunrise or sunset. This flicker effect is jarring and not realistic:

<p align="left">
  <img src="/img/flicker.gif">
</p>
<p align="center">
   Flicker effect using auto-exposure
</p>

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
</p>

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







