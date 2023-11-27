# RainingLEDs
<h1 id="What">What?</h1>
<p>The RainingLEDs project is a project that contains a cool and unique photo location. It's made for all ages, but more focussed on influencers and social media users. Our project consists of a box with mirror foil and 17 LEDstrips, creating an infinite rain illusion. Important to know is that this project is a prototype or smaller version for a bigger version that has yet to be made (see chapter 'Project Expansion'). 
</p>
<h1 id="how">How does it work?</h1>
<p>The 17 LED-strips are controlled by an ESP32-C3 microcontroller. That sends signals to the strips to recreate a handful of patterns. At the side of the box the vistors can push on 2 different buttons which put the LEDs in different modes.</p>
<h1 id="require">Requirements</h1>
<ul>
    <li>Materials:</li>
    <ul>
        <li>+/- 10 meters of BTF-LIGHTING WS2814 12V LED-strips</li>
        <li>3 wooden mbf plates making a cube from 70 X 70 X 71.8 cm</li>
        <li>Mirror foil for each side</li>
        <li>ESP32-C3-DevKitM-1 microcontroller</li>
        <li>2 buttons</li>
    </ul>
    <li>Software:</li>
    <ul>
    <li>Coded in C++ using the Adafruit_NeoPixel library. Follow the next steps to download the library (in Visual Studio Code).
    First you'll need to download the PlatformIO extension. Go to 'PIO Home' and select 'New Project'. Use the following settings in the next window:
    <img src="src/PlatformIO.png" alt="Platform IO screenshot">
    Now we just need to implement the Adafruit_NeoPixel.h library into our project (included inside the main.cpp file). You can simply do this by searching the Adafruit Neopixel library in the Libraries menu (at the left side in PIO Home). You should now be able to use the code on the ESP32 by building it and uploading it!
    </li>
    </ul>
</ul>
<h1>Project Expansion</h1>
As stated before, this project contains a small box which is the base for a possible expansion as a bigger (human-size) box. In this chapter you'll find all documentation and thing we noticed that can be helpfull for this.
<h2>Power Supply</h2>
<h2>LEDstrips</h2>
<h1 id="image">Images</h1>
<h2>Electric scheme</h2>  
<img src="src/elektrisch_schema.PNG" alt="elektrisch schema">
<figcaption>The Electric scheme shows into detail how all the LEDs are connected to the ESP32 microcontroller.</figcaption>
<h2>Projectcanvas</h2>
<img src="src/schema.jpg" alt="Projectcanvas" style="transform: rotate(deg);" />
<figcaption>The projectcanvas shows the different aspects of the project. It was the first plan of the project and contains things like the tasks that need to be done and the stakeholders.</figcaption>
<h2>Prototype 1</h2>
<img src="src/Prototype.jpg" alt="Prototype 1"/>
<figcaption>This is the first, very simply, prototype. The main goal was to see how big the box has to be and how many LEDs we need.</figcaption>
<h2>Testing LEDstrips</h2>
<img src="src/ledTests.jpg" alt="LED tests"/>
<figcaption>Before we started building the box, we tested the LEDstrips to see if they all worked.</figcaption>
<h2>Final box</h2>
<img src="src/box.jpg" alt="Box"/>
<figcaption>The final box, including the working LEDstrips.</figcaption>
<h1 id="members">Team members</h1>
<p>This project was developed by VIVES students Jonas De Rous, Xander Vyvey, Colin Bossuyt and Vic Verbiest in 2023.</p>
