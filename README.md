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
    <li>
      <a href = "#github-organization">GitHub Organization</a>
      <ul>
        <li><a href = "#inspiration">Inspiration</a></li>
      </ul>
    </li>
    <li>
      <a href = "#getting-started">Getting Started</a>
      <ul>
        <li><a href = "#download-instructions">Download Instructions</a></li>
        <li><a href = "#notes-on-gameplay">Notes On Gameplay</a></li>
      </ul>
    </li>
  </ol>
</details>



<!--- Summary of presentation introduction --->
## Summary
Our project is a C++ program called BusMap, which takes in 2 bus stops from the Champaign–Urbana Mass Transit District, and displays the most optimal path of buses to take to get from the start input to the destination input. It also displays a map with all of the MTD stops, and highlights the stops in the path between the inputted destinations. 


<!--- Development Process --->
## Development Process
To do this, we first created CSV files with data on the buses, including their locations, start/end times, the stops they go to, etc. Using this data about the time it takes to get from one stop to another, we assigned each connected stop a weight as the time it would take to get from one to the other. For example, if it took 5 minutes to get from Stop A to Stop B (it would take the same amount of time to go from Stop B to Stop A), the edge between the two stops would be weighted as 5. 

We then parsed this data in our program and created an undirected, weighted Graph structure with bus stops as vertices and buses as edges. Each edge had its respective weight as described above. This would then allow us to use our proposed algorithm (Dijkstra's) to find the best path to take between the two inputted stops.

Using our graph containing all of the parsed data about the buses, we then implemented Dijkstra's algorithm to find the shortest path between two inputted stops. We also compressed this path to account for multiple stops on the same bus, and then stored it in a Path object, which contains a vector of the stops and the estimated weight (time) it would take to get from one stop to another.

Next, using the parsed data about the stop locations on a map of the Champaign area, we created a PNG containing this data and highlighted the stops that the most optimal path takes on the map (Graphic Output of Graph algorithm). Finally, we used BFS to find the shortest path between the stops on the map, then highlighting the path that would be taken to get from one to another.


<!--- Technical architecture of project --->
## GitHub Organization
### Inspiration
When determining what kind of project to do, we wanted to choose something that we would not only learn from but was also fun. Run 4 was the perfect choice for this. Most of us did not have much game development experience, so we would learn a lot from creating our first game. Additionally, although Yash, Arthur, and Alex didn't have prior Unity experience, Charlie did. Hence, we felt comfortable taking on this challenge. In the end, we learned a lot about not just how to code a game, but also how to organize and complete a project in a timely fashion (the challenges we ran into are described in more detail in our "Development" link at the top of this page). Meanwhile, this project was super fun because we got to create something that we can share with and enjoy playing with others.

<!--- Provides reproducible installation and running instructions --->
## Getting Started
### Download Instructions
1. Go to [RUN 4](https://drive.google.com/drive/u/1/folders/13qCTqrXj8mvp2V7zyenpdeTcxGncnVcA)
2. Download the zip file (Build.zip)
3. Unzip/extract the zip file's contents and save the contents locally onto your computer
4. To start the game, go to build/Run4.exe and double click on Run4.exe. You should see a pop up screen. *Note that to exit the game, you must click on Alt + tab. This will give your cursor back. If you wish to make the game full-screen, you must click the full-screen option while the program opens and before it starts to run.*



### Notes On GamePlay
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
