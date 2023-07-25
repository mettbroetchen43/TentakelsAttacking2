# Tentakels Attacking
## Backstory:
Back to my childhood. My father used to have a strategy day. He would invite friends over and play a similar game. Unfortunately, his game no longer runs on modern computers. That's why I started to write my own game based on this game. Maybe there will be a strategy day again. 

## Your task:
The only thing you can do in this game is control your ships. Your task is to send your ships to other planets to increase your influence. Thereby battles etc. run completely on your own.

## Goal of the game (not yet implemented):
After a certain number of rounds there should be an evaluation. There all your planets, ships, and production on the planets will bring points. Whoever has the most points wins. Unfortunately I am not at this point yet. 

## Controls:
Fleets are created using the fields on the right.
IDs are entered in the "origin" and "destination" fields.
In the "X" and "Y" fields, you can also navigate to coordinates within the Galaxy.  
Either an ID or coordinates can be entered as destination. But not both.
The number of ships is entered in the "ship count" field.
As "origin" and "destination" everything can serve, which has an ID and is under your power.  

With the buttons in the main scene you can switch between the display of the Galaxy and the tables "planets" and "fleets".

# compile it yourself
- language standard: C++20
- libraries:
    - raylib 4.2
    - nlohmann-json
- include directories: every directory that is named "public"

If you have installed vcpgk you can install the libraries with it.
If you don't have vcpgk installed you find a tutorial here: https://vcpkg.io/en/getting-started.html
