# MarsRoverChallenge2
Mars Rover Challenge Version 2 A secret mission to send a Rover to perform geological surveys on the Martian surface has just been leaked by anonymous NASA scientists. With only a few days before the deployment probe reaches the surface of Mars, disaster has struck: a freak solar flare has scrambled the memory of the Rover, and all its programming has been erased! In the leak, NASA scientists are appealing to hackers, programmers, and engineers across the globe to reproduce the Rover’s source code. It is vital that this happens before the Rover touches down on the Martian surface. The ETA for Rover deployment is: Friday 9th June, 2017, 23h59 Earth-time. They require the Rover to autonomously control itself (it will be too far from Earth to make manual control a feasible option), and to survey as much of the Martian surface as possible, before hardware failure. The Rover will eventually fail, as it will run out of energy storage.

<h2> General </h2>
Application created using C++ under the Qt framework.
Qt is cross platform and should compile on Linux/Mac/Windows.
The application was compiled on a windows machine, If Qt is installed on any other relevant OS the code should compile.


Application begins at main.cpp
The application runs through test classes before deployment to validate functional and unit credibility per class.

<h2> Classes to note </h2>

- OverallControlAlgorithm

- MarsTerrain

- RoverAPI

- RoverPowerStorage

- RoverTimeActions

Test Classes

- TestMarsTerrain

- TestOverallControlAlgorithm

- TestRoverAPI

- TestRoverPowerStorage


<h2> Notes on Time and Power of Rover </h2>
- All time constraints are calculated in seconds
- All power consumption is calculated in joules only (Jouoles per hour)

<h2> Assumptions</h2>
A few Assumptions were made based on the Challenge, These assumptions were then udated in the code accordingly

- Rover Deployed at 23:59.

- Rover deployed at the start of night.

- Sol day is calculated from begining of night to end of daylight

- At deployment: Rover is fully charged

- Rover is facing North

- Rover Camera is facing North

- Rover Solar panels are retracted on deployment

- Location and Terrain of Rover is Unknown (X and Y coordinates are just used for mapping purposes)

- Algorithm caters for a 70% chance of uneven terrain when scanning

- Algorithm determines action based on random terrain to scan, rotate, survey, move and so forth

- Not all Sol days are surveying and scanning based on time and power constraints

- Hibernation function is to set rover on standstill not usinng power but waiting for next opportune time (Time Spent)



A release version (EXE) of the working application can be found on the deploy_release branch.
Run the MarsRoverChallengeTwo.exe to simulate algorithm
