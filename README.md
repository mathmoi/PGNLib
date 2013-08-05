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

Here is an example application showing how easy it is to parse PGN files with
pgnparser. The application open a PGN files and for each games display the 
names of the player and the coordinates of each moves. This demo can be found
in the source tree in the directory example/example1.

    :::C++
    #include <iostream>
    #include <fstream>
    #include <PgnParser.hpp>
    #include <memory>

    int main(int argc, char** argv)
    {
      // We try to open the pgn file
      std::ifstream in(argv[1], std::ios_base::in);

      Pgn::PgnParser parser(&in);

      while(!parser.eof())
      {
        Pgn::PgnGame game = parser.ParseSingleGame();

        // We display both players name.
        std::cout <<game.tags()["White"] << " - " <<game.tags()["Black"] <<std::endl;

        // We display all move in the format "from - to"
        for (auto item : game)
        {
          std::shared_ptr<Pgn::PgnMove> move = std::dynamic_pointer_cast<Pgn::PgnMove>(item);
          if (move)
          {
            std::cout <<static_cast<char>('a' + (move->from() % 8)) <<(move->from() / 8) + 1 <<" - " <<static_cast<char>('a' + (move->to() % 8)) <<(move->to() / 8) + 1 <<std::endl;
          }
        }

        std::cout <<std::endl;
      }

      in.close();
      return 0;
    }

Author
------

* [Mathieu Pagé][] (<m@mathieupage.com>)

[Mathieu Pagé]: http://www.mathieupage.com
