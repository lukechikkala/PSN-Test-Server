# PSN Test Server


This 2-dimentional PSN Test Server is a terminal / console application that sends PSN data of a Tracker moving in a circle along the X & Y axis.<br>
There is no movement along the Z-Axis; Z is set to `0`.

**Server**
<p align="center">
	<img src="docs/PSN%20Test%20Server.png" width=50% height=50%>
</p>

**Output**

<p align="center">
	<img src="docs/PSN%20Test%20Server.gif" width=50% height=50%>
</p>

The program is compiled for both Windows and macOS.<br>
Currently, the macOS version of the server is sending data only the Wi-Fi interface.<br>
In theory, it should send data on all Network Interfaces.

For future development notes, please see [Further Development](#further-development).<br>
For Developer Notes, please see [Developer Notes](#developer-notes).

## Average Transmission Rates
**Windows**

**macOS**
```
PSN DATA	: 47.50 Hz
PSN INFO	: 00.76 Hz
```

## Why is this Server needed?
It allows for testing PSN Protocol with applications that accept PSN as an Input.<br>

## Further Development
The idea is to make a GUI application that allows user to select up to 8 Trackers that could move in one of several directions.<br>
The planned movements are:
* Circle
* Line ( `XY` / `XZ` / `YZ` )
* Random
* Custom Paths (CSV Import)

The user will be able to adjust the speed and orientation for each tracker.

## Developer Notes
Currently the Window's and macOS are written in seperate files.<br>
Once the macOS application is working exactly as the Window's application, the idea is the merge both the files and compile them individually.<br>
The socket descriptors work differently in each platform and this is where a lot of fixing is needed at the moment.<br>
The function calls are similar, if not the same - which could be both good and bad.
