### MACRO MIDEA      

--- 

hello there , thanks for reading  my code , it took me a while to write it , but i think it is good enough to be used in my project , i hope you like it and if you have any suggestions please let me knoe , and if you wanna use this project in any ways , your free to do so , i had fun making this project and i hope you have fun making it too , and if you have any questions about the code or the project please feel free to ask me , i will be happy to help you with anything you need , and if you want to make any changes 

---

## BOM 

| Sr. No. | Name | Link | Price | Quantity | Total Price |
|---:|---|---|---:|---:|---:|
| 1 | ESP32-S3 Zero | [MakerBazar](https://makerbazar.in/products/esp32-c3-supermini-iot-development-board?variant=48753170481392) | $4.69 | 1 | $4.69 |
| 2 | Battery 220mAh | [MakerBazar](https://makerbazar.in/products/kp-drone-lipo-batteries-3-7v-rechargeable-battery-for-mini-rc-aircraft-quadcopters) | $2.35 | 1 | $2.35 |
| 3 | TP4056 | [MakerBazar](https://makerbazar.in/products/tp4056-1a-li-ion-lithium-battery-charging-module) | $0.19 | 1 | $0.19 |
| 4 | MX-Like Switches | [Amazon India](https://www.amazon.in/Buildcon-Mechanical-Keyboard-Universal-Keyboards/dp/B0GCCQLQBV/) | $4.15 | 1 | $4.15 |
| 5 | Rotary Encoder | [MakerBazar](https://makerbazar.in/products/360-degrees-rotary-encoder-module-brick-sensor-switch-development-ky-040) | $0.51 | 2 | $1.02 |
| 6 | Sliding Switch | [MakerBazar](https://makerbazar.in/products/micro-slide-switch) | $0.30 | 1 | $0.30 |
| 7 | Keycaps | [Amazon India](https://www.amazon.in/CALANDISTM-Transparent-Switches-Keyboards-Pointers/dp/B0F13YK4D6/) | $6.35 | 1 | $6.35 |
| | | | | **Total** | **$19.05** |

---

## key layout and design 

its a simple layout 6 switchs and two encoder 

![](https://cdn.hackclub.com/01a0da4c-3df1-7a13-a398-54f254f842ab/journal-1790368824476.png)

![](https://cdn.hackclub.com/01a0da53-583e-7a3e-a4d6-3240d34990df/journal-1790369289395.png)

And the two encoder are for scrolling media and , like youtube and stuff and with the arrow keys and and we can even use it to scroll a chat box while writing code and it has esacpe key mapped on it and volume encoder in the lower encoder , with mute on its button and volume increase and decrease , in the top left and right i didnt  know what to put , i shouldve put ctrl c and v , now thinking about it , i will later , middle top is win d , and the lower row is privous track , play pause , next track 

---

## Assembly 

okay soo first print the lid and base files 

then put the switchs and encoder through the lid , all the switchs snap into place and the encoder screws into the holes then just have a common ground wire and solder them togather 

![](https://cdn.hackclub.com/01a0deba-ae97-72d1-a7a4-002a34478df2/img20260920200306.jpg)

![](https://cdn.hackclub.com/01a0debc-f61e-7396-b0a5-b23fa0bf48e7/img20260920200304.jpg)

![](https://cdn.hackclub.com/01a0debe-1131-73c7-bc3f-86b7eca3ad73/image.png)

then just hook up every gpio pins , gnd , and then rest are likr this

12 gpio pin => to gpio pin of the esp32 

tp4056 => to battery and gnd to a common gnd and power to switch

switch => 3.7 pin of esp32 

this sounds easy but in practice it looks like 

![](https://cdn.hackclub.com/01a0dec7-df73-79b2-89a6-72830ea981eb/img20260921004809.jpg)

![](https://cdn.hackclub.com/01a0dec7-df73-79b2-89a6-72830ea981eb/img20260921004809.jpg)

![](https://cdn.hackclub.com/01a0dec9-9838-7e4a-bceb-83b609bdd2f4/img20260922145725.jpg)

then just close the lid and screw the case 

# 2*M3 18mm screws 

![](https://cdn.hackclub.com/01a0decb-f02e-74d1-b4c3-d08043476251/img20260926230716.jpg)

---

and then just flash the code from arduino IDE and add all the libraries 

>BleKeyboard.h
>Bounce2.h
>ESP32Encoder.h
>driver/rtc_io.h

---

# After flashing just connect and enjoy :) 


this was made for #pixl by hackclub 

--- 

@progod 

---