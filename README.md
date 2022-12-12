<div align = "center">
  
  <img src = "images/Run4.png">
  
  <p align = "center">
    <h1>BusMap</h1>
    <p><h3>Created by Yash Telang, Arthur Wang, and Varun Athreye</h3></p>
  </p>
  
  <p align = "center">
    <a href = "https://docs.google.com/document/d/1IUf3dyW1TnD_ucja0UIhg7Jr_0muf89ayezwk0SF0hw/edit?usp=sharing">Project Proposal</a>
    |
    <a href = "https://docs.google.com/document/d/1tTfg5maTvJ1vPNpdlG3aSTgqO196-tSzHHWcsHte4dg/edit?usp=sharing">Development</a>
    |
    <a href = "https://mediaspace.illinois.edu/media/t/1_501wkwbs">Demo</a>
    |
    <a href = "https://docs.google.com/document/d/16Ol95jGr3P_oHxa4LqEG1_2wpmvbBIXkynpoy6MEi_M/edit?usp=sharing">Reach Out</a>
  </p>
</div>

<details>
  <summary><h2>Table of Contents</h2></summary>
  <ol>
    <li><a href = "#summary">Summary</a></li>
    <li><a href = "#development-process">Development Process</a></li>
    <li>
      <a href = "#github-organization">GitHub Organization</a>
    </li>
    <li>
      <a href = "#getting-started">Getting Started</a>
      <ul>
        <li><a href = "#running-instructions">Running Instructions</a></li>
        <li><a href = "#misc-notes">Misc. Notes</a></li>
      </ul>
    </li>
  </ol>
</details>



<!--- Summary of presentation introduction --->
## Summary
Our project is a C++ program called BusMap, which takes in 2 bus stops from the Champaign–Urbana Mass Transit District, and displays the most optimal path of buses to take to get from the start input to the destination input. It also displays a map with all of the MTD stops, and highlights the stops in the path between the inputted destinations. To do this, it employs all of our proposed algorithms, which are BFS, Dijkstra's, and the Graphic Output of Graph algorithm. 


<!--- Development Process --->
## Development Process
We first created CSV files with data on the buses, including their locations, start/end times, the stops they go to, etc. Using this data about the time it takes to get from one stop to another, we assigned each connected stop a weight as the time it would take to get from one to the other. For example, if it took 5 minutes to get from Stop A to Stop B (it would take the same amount of time to go from Stop B to Stop A), the edge between the two stops would be weighted as 5. 

We then parsed this data in our program and created an undirected, weighted Graph structure with bus stops as vertices and buses as edges. Each edge had its respective weight as described above. This would then allow us to use our proposed algorithm (Dijkstra's) to find the best path to take between the two inputted stops.

Using our graph containing all of the parsed data about the buses, we then implemented Dijkstra's algorithm to find the shortest path between two inputted stops. We also compressed this path to account for multiple stops on the same bus, and then stored it in a Path object, which contains a vector of the stops and the estimated weight (time) it would take to get from one stop to another.

Next, using the parsed data about the stop locations on a map of the Champaign area, we created a PNG containing this data and highlighted the stops that the most optimal path takes on the map (Graphic Output of Graph algorithm). Finally, we used BFS to find the shortest path between the stops on the map, then highlighting the path that would be taken to get from one to another. This map is then outputted to a PNG that can be displayed to the user.

Finally, throughout this process, we have beem testing each component to make sure the data and results are accurate. This includes having assertions for the parsed data, comparing the output of our path finding algorithm to our manually calculated path (using multiple inputs), and confirming that the drawn paths match up on the outputted PNG.


<!--- Github Organization --->
## GitHub Organization

The `Documents` folder contains our project proposal and team contract.

The `Data` folder contains our created CSVs and the base image of the map that we use to display the path.

The `lib` folder contains provided CS225 classes and methods such as `PNG.h` and `HSLAPixel.h` that are used to read from and write to PNG files.

The `tests` folder contains all of our created test cases as described in our development process.

The `src` folder contains the majority of our code, where we have our graph structure in `Graph.h`, and our functions to parse data, build/compress our path, and output the path to a PNG in `busplanner.h`. This folder also contains the provided `utils.h`, which lets us easily read from files, split by string, and trim strings.

The `entry` folder contains `main.cpp`, which is where we use the functions and structures that we created to parse the data, specify user input, build and compress the path, and write to the outputted PNG.

The `build` and `.vscode` folder contain CMake build files that are created when building and running the program. Instructions to do this are in the following section. 

<!--- Provides reproducible installation and running instructions --->
## Getting Started
### Running Instructions
1. Download/Clone the repository to your local machine.
2. Open the repository using the standard CS225 Dockerfile.
3. 



### Misc. Notes
- How To Win: Complete all of the objectives before you die.

- Screen
  - Objectives are at the top left (they will turn green once you complete them)
  - Current Health is at the bottom left
  - Score is at top right

- Movement
  - WASD (or arrow keys) + mouse to move
  - Left click on mouse to shoot
  - Space bar to jump
  - Press "e" to interact with challenges
  - Upon a win, press "r" to restart game
  - Upon a loss, simply wait and the game will restart itself

- Interface
  - Enemies are the moving blocks. Everytime a block rams into you, you will lose some health
  - Destroy enemies by shooting them. Killing them will increase your score
  - Destroying one moving blocks will respawn 2 new moving blocks
