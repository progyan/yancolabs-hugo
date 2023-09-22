---
title: "LCDRacer"
date: 2023-07-30T16:56:38+06:00
draft: true
author: "yanb"
summary: "Классическая гонка-аркада на LCD под управлением Arduino."
bgimage: "/post_lcdracer_connection.jpg"
tags:
- "Arduino"
---

## Как играть в LCDRacer

LCDRacer - классическая гонка-аркада, в которую можно поиграть на LCD диплее с Arduino.
Твоя машина (`C:>`) с тремя жизнями. Она едет по гоночной трассе, набирая очки и скорость.
Собирай монеты (`*`) и улучшения (`?`), рули с помощью джойстика и стреляй (`-`) красной кнопкой, разрушая препятствия (`#`), мишени (`@`) и бомбы (`o`), чтобы получить больше очков. Не врежься и набери как можно больше очков!

_Видео конечного результата:_

<iframe width="660" height="371" src="https://www.youtube.com/embed/z82Q5v14J5Y" title="LCDRacer - A DIY Arcade Game with Arduino" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

## Что понадобится

Привожу ссылки с Амперки для примера.

- Breadboard, лучше на 830 точек - [https://amperka.ru/product/breadboard]
- Arduino UNO (или больше) - [https://amperka.ru/product/arduino-uno]
- LCD размером 20x4 символа на I<sup>2</sup>C - [https://amperka.ru/product/display-lcd-text-20x4-ylg-i2c-3v3]
- Аналоговый джойстик - [https://amperka.ru/product/troyka-3d-joystick]
- 2 кнопки, желательно большие, одна красная и одна синяя - [https://amperka.ru/product/big-tactile-button]
- Пьезопищалка либо динамик - [https://amperka.ru/product/piezo-buzzer]
- Два резистора на 1 кОм - [https://amperka.ru/product/resistor-1k]
- Провода папа-папа - [https://amperka.ru/product/wire-mm]

Пора собирать схему!

## Сборка

Сначала подключим LCD к Arduino: можно напрямую или через I<sup>2</sup>C.

Потом пьезопищалку, кнопки и джойстик, как нарисовано снизу.

![[Схема подключения]](/post_lcdracer_connection.jpg)

## Код

Вставим этот код в Arduino IDE и загрузим в Arduino:

<a href="/race.ino" class="file-download" download>скачать код</a>

## Готово!

Можно запускать и играть!