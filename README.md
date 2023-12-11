# RainingLEDs
<h1 id="What">What?</h1>
    <p>The RainingLEDs project is a project that contains a cool and unique photo location. It's made for all ages, but more focussed on influencers and social media users. Our project consists of a box with mirror foil and 17 LEDstrips, creating an infinite rain illusion. Important to know is that this project is a proof of concept that can help making a bigger version that has yet to be made (see chapter 'Project Expansion'). 
</p>
<h1 id="how">How does it work?</h1>
    <p>The 17 LED-strips are controlled by an ESP32-C3 microcontroller. That sends signals to the strips to recreate a handful of patterns. At the side of the box the vistors can push on 2 different buttons which put the LEDs in different modes.</p>
<h1 id="require">Requirements</h1>
    <ul>
        <li>+/- 10 meters of sk6812 rgwb LED-strips</li>
        <li>3 wooden mbf plates making a cube from 70 X 70 X 71.8 cm</li>
        <li>Mirror foil for each side</li>
        <li>ESP32-C3-DevKitM-1 microcontroller</li>
        <li>2 buttons</li>
    </ul>
</ul>
<H1>Hardware</H1>
    As stated before, this project is a proof of concept, which is the base for a possible expansion. The current box is here discribed and some possible improvements are listed.
<h2>Box</h2>
    <img src="src/box.jpg" alt="Box"/>
    For building the box, we used MBF plates. These are strong wooden plates that can easily be drilled into. The inside of the box has the dimention fo 70cm x 70cm x 70cm. This is the space where someone can stand in when they want to take a picture. On the inside, we used mirror foil to  create the illusion of a bigger number of leds. The buttons are placed ad the bottom side for easy acces when taking a picture. There are still some things that can be improved:
    <ul>
        <li>
        Our box is in fact too small to take a picture of a full person. This makes is easy to replace, but is also a disadvantage since the effects would be more spectacular on a human-size box. So a bigger box should be one of the primary improvements this project needs. 
    </li>
    <li>
    While the mirror foil is a cheap and easy way to create the wanted effect, it is not as good as a real mirror. The mirror foil is not as reflective as a real mirror, so the effect is less spectacular. A real mirror would be a better option, but is also more expensive and harder to work with.
    </li>
</ul>
<h2>LEDstrips</h2>
    In the current project, we use 17 led strip who are each +/- 50 cm. this is a good length of the current box because of the extra room add the bottom is not too big and this way, we don't need an extra 5m led strip just to use 20% of it. To know if using 17 led strips works. We tried to use 2 data pins to control all the led strips.
    <img src="src/ledTests.jpg" alt="LED tests"/>
    Since this worked; we installed the leds in the box and connected everything together on top. Because of the drilled holes in the top plate. Installing the LED strips was easy. We used a breadboart to make all the connections with the esp32. This way, we could easily change the wiring if needed and replace components if they would  not work anymore. Most of the time, all led strips work as intended, but there are some times where the pattern is not 100% correct. Here are some things that can be improved about the lighting:
<ul>
    <li>
        The current box uses 17 led strips. This is a good amount for the current box, but if we want to make a bigger box, we need more led strips. This is not a problem, but we need to make sure that the esp32 can handle all the led strips. We can do this by using a second esp32 or by using a esp32 with more data pins.
    </li>
    <li>
        In this project, all led strips hang on their own. This means that the  side where leds are, are faced to the public or the camera or to the mirrors on the inside. They are never faced both. This is not a big problem but interferes with the illusion of the mirrors. This problem could be solved by putting 2 led strip, back to back instead of hang them alone.
    </li>
    <li>
        Each led strip is connected directly to the esp32. This means that there is maximum 3.3V on the data pin when sending a high signal. This can be the reason why the leds are not always working as intended. This can be solved by using a transistor or a mosfet to amplify the signal.
    </li>
</ul>
<h1>software</h1>
    <h2>Adafruit_NeoPixel library</H2>
        Coded in C++ using the Adafruit_NeoPixel library. Follow the next steps to download the library (in Visual Studio Code).
        First you'll need to download the PlatformIO extension. Go to 'PIO Home' and select 'New Project'. Use the following settings in the next window:
        <img src="src/PlatformIO.png" alt="Platform IO screenshot">
        Now we just need to implement the Adafruit_NeoPixel.h library into our project (included inside the main.cpp file). You can simply do this by searching the Adafruit Neopixel library in the Libraries menu (at the left side in PIO Home). You should now be able to use the code on the ESP32 by building it and uploading it!
    <h2>main.cpp</h2>
        In the main program foor the project 'Raining LEDs', there are 3 crusial parts:
        <ul>
            <li>
                <h3>buttons</h3>
                The buttons are programed to be triggered on the positive flank. This means that when the button is going from a low state to a high, the program will interpret at that as a button press. This means that nothing will happen when someone releases the button ore hold it. To reduce the Dender, there is a delay programmed to filter only one positive flank.
            </li>
            <li>
                <h3>cycle</h3>
                The cycle is the part of the program that is responsible for changing the pattern. When a button is pressed, the cycle will change to the next pattern. This is done by using an array witch include all patterns  whereof the index, which is used to filter the correct data, is increased or decreased. When the index is bigger than the array, the index will be set to 0. When the index is smaller than 0, the index will be set to the last index of the array.
            </li>
            <li>
                <h3>sending data</h3>
                To send the data to the ledstrips, the correct data has to be filtert. This is done by useing a series of if-statements wich check of the data in the array from above. when the correct data is found, the data will be send to the ledstrips. This is done by using the Adafruit_NeoPixel library. This library has a function called 'show()' witch will send the data to the ledstrips.since there are  data pins, the sended data looks like this:
                <img src="src/data.png" alt="data">
            </li>
        </ul>
    <h2>MQTT<H2>
<h1>project expension</h1>
    Because this project is a proof of concept, there was expected of us to make a project that can be expanded. This means that the project can be used as a base for a bigger project. Here are some ideas that can be used to expand and elaborated vision of what this could become.
    <h2>ideas</h2>
        <ul>
            <li>double ledstrips</li>
            <li>bigger box</li>
            <li>use of transistors for data transmition</li>
            <li>using mirrors</li>
            <li>mount</li>
            <li>PCB</li>
            <li>...</li>
        </ul>
    <h2>our vision</h2>
    there are a lot of thing we can do for make this a incrediple project. The amount of possibilities is almost endless. We have some ideas that we think are the most important to make this project a succes.Here is our vision of what this project could become.
    <h3>box</h3>
    <ul>
        <li>
            <h3>dimentions</h3>
            The box is where the whole project relies on. Whne there is no box, There is nothing to make a picture of. We think it would be a good thing if a whole person could stand between de hanging ledstrips. This means tha the box has to be at least 2 meters high. It would also be a good thing if the box is a little bit bigger. This way, the illusion of the mirrors would be better becous of the more ledstrips and there could bo more than 1 person in ther bow. With only a little more space, there can be a extra person on photo.
            <img src="src/expantion_dimentions.png" alt="expanded box">
            We think the dimentions of 100cm x 100cm x 200cm would be a good size for the box. This way, there is enough space for at least 3 people. If you want to be the project mobile, it is posible to split te side pannels in 2. 
            <img src="src/expantion_split_box.png" alt="expanded box">
            This way, the box can be transported in a car. If you find a way to link te bottom part to the top part, it can be used it again as the full project. It woeld be even possible to separate the top part to. This way, it is just a option to use the mirror sides.
        </li>
        <li>
            <h3>mirrors</h3>
            To create the effect that we want, the top and sides of the inside of the box has to reflective. The best thing to use for this would be mirrors. in the prototype, we did not use mirror becaus of the expensive price. with mirrors, the effect could make this project a intressting attraction on a event. In the perfect world, the top and both sides would be mirrors. but sinds the ledsstrips has to come true the top, this would be very hard to do. Drilling holes in a mirror is a difficult proces and will result in a huge monney loss if it goes wrong. For the top part, we would dtick to the mirror foil.
        </li>
    </ul>
    <h3>ledstrips</h3>
        When the box becaums bigger, it is normal tha the number en langth of the ledstrips grows to. If we want to make a box as descriped above, there would be 25 ledstrips hanging from above. since we wanted to double the ledstips for the mirror effect, this would come down on 50 ledstrips. When we make each of tham 150 cm, that would mean that there would be 75 meters of ledstrips. this would come down on 277 euro with the type of leds we are currently using.
        <img src="src/expantion_ledplacement.png" alt="expanded box">
        This would be a good placment of the ledstrips. with the staggert placement, The mirrors will reflecta as much of the light as possible resulting in a beautifull photo.
    <h3>electronics</h3>
    <ul>
        <li>
            <h3>mcu</h3>
                The best way to controle all ledstrips is when every ledstrip has its own data pin. This way, it is possible for every ledstrip to do somthing completely different which would result in no boundaries for patterns. In the current project, we used an ESP32-C3-DevKitC-02.
                <img src="src/esp32-c3-devkitm-1-v1-pinout.png" alt="esp32-c3-devkitm-1-v1-pinout">
                This microcontroler has 15 GPIO ports. this is enough for the prototype but comes to short for the expanded version. We would need at least 27 GPIO ports if we want to keep the cycle buttons. A good solution would be the ESP32-WROOM-32. This microcontroler has 38 GPIO ports. This would be enough for the expanded version and would give us the possibility to add more buttons or other components.
                <img src="src/esp32-wroom-32.webp" alt="expanded box">
        </li>
        <li>
            <h3>powersuply</h3>
                With 50 ledstrips, the power consumption will be a lot higher. This means that the power supply has to be more powerfull. When we use 50 ledstrips, the max powerconsumption would be around 30 Watt. The project would have to be connected to a 5V 6A power supply like the LHA30F-5-SNY
                <img src="src/LHA30F-5-SNY.jpg" alt="LHA30F-5-SNY">
        </li>
        <li>
            <h3>data transmition</h3>
        </li>
    </ul>
    

<h1 id="troubleshooting">Troubleshooting</h1>
<h2>LEDstrips</h2>
We had to resolder a few LEDstrips because the cables were detached while we were putting them in the box. When all the LEDs were in place we noticed that 2 strips stopped functioning and replaced them by 2 smaller strips.
<h2>Coding</h2>
We started coding some simple functions to test the LEDs. After that we extended the LEDstrip to see if it would still work with the ESP32. We encountered a problem with some code examples where the LEDs would not follow the code and would simply show random colours. When the voltage was adapted to the right value, it started working again with a larger LEDstrip. This was all done with one data line, however we wanted to use mutiple data lines to create a more natural flow between the LEDstrips so that there would be some variation. This worked with four data lines but only one pattern at a time. We still had some problems with cycling between dynamic patterns with multiple data lines.
<h2>Power supply</h2>
We began with following the datasheet, so we used a voltage of 3.6 with a school power supply. Because we were working with a voltage of 3.6 we had to consider to limit our brightness so we wouldn't take up a whole lot of wattage. We concluded that the ideal brightness for the LEDs was 60%. This also made sure that the functions worked properly. When we rearranged the wiring of our project, we made it work using our own power supply with 5V.
<h2>Button</h2>
The buttons were implemented fairly quickly, but we ran into some problems: they only worked with static functions, not with dynamic patterns and a delay occured when pushed. We solved the delay problem by adding a debounce system that ensured that only one button press is registered. By working with threads we managed to cycle between dynamic functions.
<h1 id="image">Images</h1>
<h1>Electric schematic</h1> 
Ad first, we wanted to make a Led cube using 2 data pins and 2 buttons. Because of the 2 data pins, we could send 2 different patterns to the LED-strips witch could make the illusion of falling rain or other dynamic patterns. The initial electric schematic looked like this:
<img src="src/elektrisch_schema.PNG" alt="elektrisch schema">
When we slowly progressed on the project, we noticed that the difference between 2 and 4 data pins was not that big. With 4 data pins, there is a grated variety and freedom in the patterns we can create. There are still 2 buttons to cycle between the patterns. The final electrical schematic looks like this:
<img src="src/elektrisch_schema2.png" alt="elektrisch schema2">
<figcaption>The Electric schematic shows into detail how all the LEDs are connected to the ESP32 microcontroller.</figcaption>
<h1>Projectcanvas</h1>
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
