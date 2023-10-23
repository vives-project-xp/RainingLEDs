# RainingLEDs
<h1>Table of contents</h1>
<ul>
    <li>[What?](#What)</li>
    <li>[How does it work?](#how)</li>
    <li>[Reguirements](#require)</li>
    <li>[Image](#image)</li>
    <li>[Team members](#members)</li>
</ul>
<h1 id="What">What?</h1>
<p>The RainingLEDs project is a project that contains a cool and unique photo location. It's made for all ages, but more focussed on influencers and social media users. Our project consists of a box with mirror foil and 18 LEDstrips, creating an infinite rain illusion. Important to know is that this project is a prototype or smaller version for a bigger version that has yet to be made.
</p>
<h1 id="how">How does it work?</h1>
<p>The 18 LED-strips are controlled by an ESP32-C3 microcontroller. That sends signals to the strips to recreate a handful of patterns. At the side of the box the vistors can push on 2 different buttons which put the LEDs in 2 different modes.</p>
<h1 id="require">Requirements</h1>
<ul>
    <li>Materials:</li>
    <ul>
        <li>10 meters of BTF-LIGHTING WS2814 12V LED-strips</li>
        <li>3 wooden mbf plates making a cube from 70 X 70 X 71.8 cm</li>
        <li>Mirror foil for each side</li>
        <li>ESP32-C3-DevKitM-1 microcontroller</li>
        <li>2 buttons in a 3D printed box</li>
    </ul>
    <li>Software:</li>
    <ul>
    <li>coded in C++ using the Adafruit_NeoPixel library</li>
    </ul>
</ul>
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
<h1 id="members">Team members</h1>
<p>This project was developed by VIVES students Jonas De Rous, Xander Vyvey, Colin Bossuyt and Vic Verbiest in 2023.</p>
