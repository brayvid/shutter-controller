# Shutter Controller

## Introduction
I have long appreciated the art of making timelapses. They can reveal motion in the world on timescales that are not normally noticeable like clouds forming and evaporating in the sky or the Earth rotating against the stars. In theory, timelapses are simple enough to create: one simply takes a sequence of images and stitches them together into the frames of a movie using free software. However in practice I have found them tricky to make well.

## Exposure problem
The ambient brightness of the environments I want to capture will be continuously changing. Since I'm looking to produce timelapses with a roughly constant apparent brightness, I can't use the manual mode on my camera as it won't adapt:
<p align="center">
  <img src="img/drastic.gif" width="80%">
    <p align="center">
   Manual mode
</p>
</p>
</br>
Automatic exposure (AE) mode isn't an option either because it causes the frames to flicker:

</br>
<p align="center">
  <img src="img/flicker.gif" width="80%">
  <p align="center">
   AE mode
</p>
</p>

## Nonlinearity of the problem
The ambient brightness throughout sunrise and sunset does not follow a straight line with respect to time. Instead, it forms a logistic curve:
<p align="center">
  <img src="img/brightness.png" width="60%">
  <p align="center">
   Brightness with respect to time inferred from real-world data
</p>
</p>
</br>
To shoot well-exposed timelapses around these times I will compensate by using a complimentary shutter speed curve, one that decays as the brightness increases and vice-versa:
<p align="center">
  <img src="img/shutter.png" width="60%">
  <p align="center">
   Shutter speeds needed to maintain a constant image brightness (range of ~15s to ~1/320s)
</p>
</p>

## Intervalometers
Certain intervalometers offer the possibility of varying the shutter speed during the capture sequence, but none offer enough control over how the shutter speed changes. I have only seen models that interpolate linearly between given starting and ending speeds, which is too slow for this purpose.

## Custom control
I chose to build my own shutter release circuit as it can be operated programmatically via an Arduino microcontroller:
<p align="center">
  <img src="img/prototype.jpg" width="80%">
  <p align="center">
   (1) Arduino, (2) shutter release circuit, (3) 2.5mm TRS post adapter, (4) 2.5mm shutter cable, (5) interface, (6) 7-segment display
</p>
</p>
</br>
I feed what time I plan to start recording and other parameters into a Python script, and a list of appropriate shutter speeds is returned:

```python
>>> speeds_ms

[5855, 4269, 2970, 1993, 1302, 835, 530, 334, 210, 132, 83, 53, 34, 22, 15]
```

I then just copy these values into my Arduino script and ensure I start recording at exactly the time I specified.

### Stay tuned for more...