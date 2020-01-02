# Systems Level Programming Final Project Proposal
Team Members: Calvin Chu, Anthony Li, Jerry Lin
Project Summary: Create a text-based rpg game with stat & equipment management, player vs computer combat, and player vs player combat. Also includes minigames (for stat improvements).

### User Interface and Project Details:
* The majority of the game will ask for player input of either 1, 2, 3, ..., corresponding to the choices printed and labelled on the terminal.
* Upon calling the program, it will ask to create a character or choose an existing character.
* The character cannot be accessed by multiple main game processes, if attempted.
* Characters also cannot have the same name (for a user)
* After creating or selecting a character, the player will be brought to a “menu” in which they can select between Training, Random Encounter, Inventory, Skills, and PvP.
* Training: the player selects a stat to improve. The game executes a minigame program that may lead to the improvement of that stat onto the save file.
* Random Encounter: the game process randomly selects an unequally chanced enemy. The game executes the combat program.
* Inventory: the game displays the character’s collection of equipment. Upon selecting the item, players can view it’s stats, a description, and choose to equip it, altering the character statistics.
* Skills: the game displays the character’s collection of skills, similarly to equipment. Up to 4 skills can be equipped at a time, each having an impact in combat.
* PvP: the player requests to connect to another. When both agree, they join a combat program. “Referee” is run on the challenger.
* Minigames: not yet specified, but text-based.
* Combat: turn-based. PvP has timed actions. Players select from their skills or the default attack skill. Ends when the hitpoints of one side is reduced to 0.

### Topics Used:
* Working with files — the main game process accesses character save files, equipment statistics files, and enemy encounter statistics files, and minigame data files.
* Processes — minigames and combat are conducted in separate processes. 
* Signals — save character data before terminating the process.
* Pipes — send character data to and from the main game process to the combat process or minigame processes.
* Semaphores — control the turn-based gameplay of combat.
* Networking — allows for PvP combat across devices (transmit information).

### Data Structures and Algorithms:
Data Structures:
* Structs 
* assigning stats and other info to characters/enemies
* holding question/answer info for minigames that require it
* stuff inside the player’s inventory/equipped

* Arrays 
    * basically pseudo-dictionaries, translates items from their ID number to understandable text

Algorithms:
* combat-related calculations using stat ints.
* Drop rate and other random chance things
* String decoding to read files.



### Task Delegation
* Anthony:
    * Developing the main game program
    * Creating the Inventory and Skills portions of the game process.
    * Creating the combat program
    * Writing: descriptions for items and skills; algorithms for gameplay.

* Jerry:
    * File writing/reading: formatting save files, minigame files, item files
    * Directories: organizing files/assets for ease of development
    * Character info: basic framework for putting relevant data for each character in a struct
    * Minigames: doing planning and coding for many of them.(no specifics yet)
    * Writing: questions in minigames, descriptions for items (if time allows)

* Calvin:
    * PvP networking (if time allows)
    * Writing: descriptions for items and skills; algorithms for gameplay.
    * Minigames: doing planning and coding
    * Connections (pipes, sockets, semaphores)

### Timeline:
* 1/05/20 - basic formatting for files (characters, items, etc.) and maximum values.
* 1/08/20 - basic framework for minigames, game menu, communications.
* 1/12/20 - working game (at least one minigame, inventory working, combat working, etc.).  
* 1/16/20 - complete the project, expand minigames, increase item variety
* 1/17/20 - additional content
