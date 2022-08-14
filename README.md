# Tesseract LED Cube
An 8x8x8 LED Cube that I built using Arduino

![Tesseract ON](https://user-images.githubusercontent.com/88684972/184557755-02a9b48f-027b-476d-acf1-9bdb8137065f.png)
![Tesseract ON Sideview](https://user-images.githubusercontent.com/88684972/184557811-045b3a24-1e77-47e9-adc4-b761d314bb46.png)
![Tesseract](https://user-images.githubusercontent.com/88684972/184557883-97aa5e7b-e504-4b5c-b050-5c684226b7fb.png)

## ✨ Motivation 
At some point in my school, our group took a course of electronics and I fell in love with them. Eventually they taught us about Arduino, which after all we went before resulted as the greatest and powerful tool for me. **I was so amazed by it!**

One day I found a video about cool electronic projects that could be done with Arduino, and a LED Cube was one of them. So I said to myself... **Why not?**

I built the cube when I was at fifth grade.

`This is my first big electronic project, and I'm so proud of it ^w^`

## ⌛ Time
The process of designing the cube, building the LED arrangement and coding the library for it took me around 6 months

## ⚙ Functionality
The cube is made of three main elements:
- Blue LEDs 🔹
- Shift Registers 💾
- Arduino MEGA 💻

⚙ There are 512 blue LEDs, every floor is cathode and every pilar is anode common, there are 8 floors and 64 pilars.

⚙ A total of 8 Shift Registers allow us to control every single pilar, and a ninth controls the floors.

⚙ To light up an LED, the floor as well as the pilar need to be activated so the LED turns on.

⚙ To light up mulitple LEDs on different floors, every floor lights up one by one and very fast, showing their corresponding LEDs sequence just like TVs show images.

⚙ I made a library for Arduino that creates kinda like a ***"virtual cube"*** that allows me to determine which LED should turn or off, or when to turn off at a specific time.
