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

Table of content
----------------

[TOC]

License
-------

The PgnLib library is distributed under the MIT License. You can find a copy 
of the license in the file LICENSE.txt in the root directory.

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
          Pgn::PgnMove* move = dynamic_cast<Pgn::PgnMove*>(item);
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

Tutorial
--------

The first thing to do is include PgnParser.hpp (and other include files).

    :::C++
    #include <PgnParser.hpp>
    #include <iostream>

Then you need to do is create a PgnParser object. To do so, you 
need to pass it a istream object on which the parser will read the PGN 
games. This is stream may be an opened file (ifstream), the standard input,
an istringstream or any other istream. In our example, we will read PGN files
from the standard input.

    :::C++
    PgnLib::PgnParser parser(std::cin);

If we want to read all games on the stream we will need to repeatedly call the
ParseSingleGame method. To know when to stop, we can verify if we are at the 
end of the stream by looping until the eof() property of the parser object 
returns true. To parse a game, we simply call the ParseSingleGame method that
returns a PgnGame object containing all the informations of the game.

    :::C++
    while (!parser.eof())
    {
      PgnGame game = parser.ParseSingleGame();
      // Do something with the game here
    }

This should parse all the game on the istream one by one. Now we need to do
something with theses games. At first let's just print a game number and the
players names. To do so we access the tags() property that returns an 
std::map-like object containing the tags. We then extract the values of the
"White" and "Black" tags, that should contains the white and black player's
names, using the  \[\] operator.

    :::C++
    uint32_t game_number = 0;
    while (!parser.eof())
    {
      PgnLib::PgnGame game = parser.ParseSingleGame();

      ++game_number;
      std::cout <<"Game " <<game_number <<std::endl
                <<game.tags()["White"] <<" - " <<game.tags()["Black"] <<std::endl;
                <<std::endl;
    }

Let's suppose instead that we wished to display all the tags. In the case we 
would have to use an [iterator][] like this:

    :::C++
    PgnLib::PgnTags::iterator tag = game.tags().begin();
    while (tag < game.tags().end())
    {
      std::cout <<tag.first << ": " <<tag.second <<std::endl;
      ++it;
    }

[iterator]: http://en.wikipedia.org/wiki/Iterator

Better yet, if your compiler supports it, you can use C++11's range-based for
statements like this :

    :::C++
    for (auto tag : game.tags())
    {
      std::cout <<tag.first << ": " <<tag.second <<std::endl;
    }

Next, we probably wants to read the movetext. If you only care about moves in
the main line you can just iterates on the items and check if they are moves.
If they aren't you can ignore them like this :

    :::C++
    for (auto item : game)
    {
      PgnLib::PgnMove* move = dynamic_cast<PgnMove*>(item);
      if (move)
      {
        std::cout <<move->from() <<" -> " <<move->to() <<std::endl;
      }
      else
      {
        // The item is not a move
      }
    }

However, you might also want to do something with all the items found in the
movetext. For the simple items like comments and NAG you do the same thing
we just did whith the move. First you check if the item is of the type you
are looking for and then if it is, you do use it.

For variations it's a bit different. Variation can contains other variation,
so we will need somekind of recursive function to process variations.

Bellow is such a function that takes a variation in input and ouput it in a 
XML-like format.

    :::C++
    void ProcessVariation(const PgnLib::PgnVariation* variation, const std::string& tagName, const std::string& indent)
    {
      std::cout <<indent <<"<" <<tagName <<">" <<std::endl;

      for (auto item : *variation)
      {
        PgnLib::PgnMove* move = dynamic_cast<PgnLib::PgnMove*>(item);
        if (move)
        {
          ProcessMove(*move, indent + "  "); // output the move
        }
        else
        {
          PgnLib::PgnComment* comment = dynamic_cast<PgnLib::PgnComment*>(item);
          if (comment)
          {
            ProcessComment(*comment, indent + "  "); // output the comment
          }
          else
          {
            PgnLib::PgnNag* nag = dynamic_cast<PgnLib::PgnNag*>(item);
            if (nag)
            {
              ProcessNag(*nag, indent);
            }
            else
            {
              PgnLib::PgnVariation* subVariation = dynamic_cast<PgnLib::PgnVariation*>(item);
              if (subVariation)
              {
                ProcessVariation(subVariation, "variation", indent + "  "); // Recursive call
              }
              else
              {
                // This block should never be reached.
              }
            }
          }
        }
      }

      std::cout <<indent <<"</" <<tagName <<">" <<std::endl;
    }

Since a PgnGame is a PgnVariation, we can call this function on a PgnGame.

    ::C++
    PgnGame game = parser.ParseSingleGame();
    ProcessVariation(&game, "");

You can find a complete exemple application that read PGN games on the input 
stream and output then on the output stream in an xml like format in the source
tree under the directory examples/example2

Author
------

* [Mathieu Pagé][] (<m@mathieupage.com>)

[Mathieu Pagé]: http://www.mathieupage.com
