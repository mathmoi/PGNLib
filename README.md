pgnparser
=========

pgnparser is a library that can be used to read and create [Portable Game 
Notation (or PGN)][pgn] files.

[pgn]: http://www.saremba.de/chessgml/standards/pgn/pgn-complete.htm

The goal of pgnparser is to be a PGN parser library easy to integrate into
chess applications, GUIs and engine. It is written in C++, but there is plan
to provide a C and Python interfaces.

In the introduction of the PGN specifications the PGN standard is described as 

> PGN is "Portable Game Notation", a standard designed for the representation 
> of chess game data using ASCII text files. PGN is structured for easy reading
> and writing by human users and for easy parsing and generation by computer 
> programs.

However, in practice, while it's easy to read by human users, it is definitely 
not easy to parse by computer programs. In order to parse the [Standard 
Algebraic Notation (or SAN)][san] used to represent chess moves in a PGN files 
the parser need to keep tracks of the game state and know about chess rules 
such as checks and pinned pieces.

[san]: http://chessprogramming.wikispaces.com/Algebraic+Chess+Notation#Standard%20Algebraic%20Notation%20(SAN)

There is a lot of open source chess applications and engine that have the
ability to parse PGN files. However their parsers are usually dependent on
other parts of their code such as their move generator. This makes them hard
to reuse in another application.

Example
-------

    :::C++
    #include <iostream>

    int main (int, char**)
    {
      std::cout <<"Hello world!" <<std::endl;
    }

Author
------

* [Mathieu Pagé][] <m@mathieupage.com>

[Mathieu Pagé]: http://www.mathieupage.com
