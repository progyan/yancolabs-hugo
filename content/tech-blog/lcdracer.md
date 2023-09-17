---
title: "LCDRacer"
date: 2023-07-30T16:56:38+06:00
draft: true
author: "yanb"
summary: "A classic racing arcade game played on an LCD controlled by Arduino."
bgimage: "/blog/post-lcdracer-connection.jpg"
tags:
- "Arduino"
---

## How to play LCDRacer

LCDRacer is a classic racing arcade game played on an LCD controlled by Arduino.
`C:>` is your car with three lives. It rides on the racing road and earns speed and points. 
Collect coins (`*`) and powerups (`?`), steer using your joystick, and shoot bullets (`-`) using the red button to destroy obstacles (`#`), targets (`@`), and bombs (`o`) to earn points. Avoid the obstacles and get as many points as you can!

_Watch the playthrough video:_

{{< youtube z82Q5v14J5Y >}}

## What you will need

- A breadboard
- An Arduino UNO (or bigger) board
- A 20x4 LCD screen
- An analog joystick
- 2 buttons, preferably large, one red and one blue
- A buzzer
- Two 1kΩ resistors
- Some jumper wires

Let's get started!

## Connection

First, connect the LCD to your Arduino directly or using I<sup>2</sup>C.

Then connect the buzzer, buttons, and joystick as shown in the following scheme.

![[Connection scheme]](/static/blog/post-lcdracer-connection.jpg)

## Code

Paste the following code into Arduino IDE and upload it onto your Arduino.

<a href="/static/blog/race.ino" class="file-download" download>download code</a>

## Done!

You're ready to play the game!

