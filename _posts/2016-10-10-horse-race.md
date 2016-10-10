---
layout: post
title: "Horse Race on BeagleBone Black"
description: "Project Description Here³"
date: 2016-10-10
tags: [beaglebone, electronics, gpio, game]
comments: true
share: true
---

### Project Requirements
 - 1x RGB Led
 - 1x Red Led
 - 1x 220Ω Resistor
 - 1x 1000Ω Resistor
 - 3x 100Ω Resistor
 - 1x Button
 - 1x Potentiometer
 - 1x BeagleBone Black

---

### How to Make

Soon...

---

If you don't wanna watch the video, there's a sketch:

![BeagleBone Sketch]({{ site.baseurl }}/assets/images/posts/beaglebone_fairylights_sketch.png)

---

### Code

All sources to execute this project are available on [GitHub](https://github.com/eltonvs/beagleproject/tree/master/HorseRace).

---

### Run on BeagleBone Black

To run this project you just need to copy the binary file (generated on `bin` folder) to your BeagleBone Black Board (you can use `ssh` to do this).

Run this on your machine:

```
$ scp bin/horserace debian@192.168.7.2:~/
```

 > The user (`debian`) and the IP address (`192.168.7.2`) may be different according with your system.

After that, you should to enter on beagle (using ssh again) and became root. So, after you're inside BeagleBone, navigate to folder that you copied the binary file and run this on terminal:

```
$ sudo su        # To became root
$ ./horserace  # Execute the binary file
```
