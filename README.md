# Uwol for DOS

This is a port of the game [Uwol, quest for money](https://www.mojontwins.com/juegos_mojonos/uwol-quest-for-money/) for DOS.

Required:

- CMake
- Dosbox
- [Open Watcom V2.0](https://github.com/open-watcom/open-watcom-v2) 

How to use it:

- Source the Open Watcom environment
    ```
    $ source <Open Watcom installation path>/owsetenv.sh
    ```

- build the game
    ```
    $ mkdir build
    $ cd build
    $ cmake .. -GNinja
    $ dosbox ../dosbox.conf 
    ```
