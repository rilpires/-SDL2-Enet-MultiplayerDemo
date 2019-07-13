# -SDL2-Enet-MultiplayerDemo
A simple demo made with SDL2 graphic lib and Enet network lib

This demo requires 'SDL2' , 'SDL2_image' and 'SDL2_ttf' libraries installed

## Building in Linux
First we need to compile Enet library. We need 'libtool', 'automake' and 'autoconf' available
We execute in project root folder:
<br><code> cd Engine/enet && autoreconf -vfi && ./configure && make && cd ../../ </code><br>

After that we compile the demo with
<br><code> cmake . && make</code><br>

We should set up a server and that's it
<br><code>./server</code><br>

We open the demo in a terminal 
<br><code>./app</code><br>
it will ask for the server ip address and try to connect with it
