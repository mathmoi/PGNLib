#ifndef INCLUDE_PGN_PARSER_HPP_
#define INCLUDE_PGN_PARSER_HPP_

#include <memory>

#include "PgnTokenizer.hpp"
#include "PgnToken.hpp"
#include "PgnGame.hpp"
#include "PgnVariation.hpp"
#include "PgnMove.hpp"
#include "PgnNag.hpp"
#include "PgnComment.hpp"
#include "Chessboard.hpp"
#include "PgnParserException.hpp"

namespace Pgn
{
  class UnexpectedTokenException : public PgnParserException
  {
  public:
    UnexpectedTokenException()
      : PgnParserException("An unexpected token was found while parsing the pgn games.") {}
  };

  /**
   * Class that encapsulate the parser functionalities.
   *
   * This class is the main client interface to the parser functionalities. To
   * parse a PGN file you need to create an instance of PgnParser and pass an
   * istream to it's constructor. You then repeatedly call ParseSingleGame to
   * get every games in the file.
   */
  class PgnParser
  {
  private:
    PgnTokenizer tokenizer_;
    std::unique_ptr<PgnToken> current_token_;

  public:
    /**
     * Constructor of the class.
     *
     * You need to pass a pointer to a istream. It can be an already opened
     * file an istringstream or any other istream on wich PGN games can be
     * red. If the istream is a file it must be opened before the constructor
     * is called and it must be closed by the calling code after all call to
     * \ref ParseSingleGame.
     *
     * \param is std::istream on wich the parser will try to read PGN games.
     */
    inline PgnParser(std::istream* is)
      : tokenizer_(is),
        current_token_(new PgnToken(tokenizer_.GetNextToken()))
    {};

    /**
     * This function parse and return a single game.
     *
     * Before calling ParseSingleGame the client code should make sure that the
     * end of the stream is not reached by calling \ref eof() first. To parse 
     * multiples or all games of a file, ParseSingleGame must me called
     * multiple times.
     *
     * \return A Pgn game object containing all the informations  of the 
     * parsed game.
     */
    PgnGame ParseSingleGame();

    /**
     * Indicate if the end of the stream is reached.
     * 
     * If not, we should be able to read the next game with 
     * \ref ParseSingleGame.
     *
     * Client code should call this function before each call to 
     * ParseSingleGame to makes sure there is still data to be parsed on the 
     * stream.
     * 
     * \return True if there is still data on the strea, false otherwise. 
     */
    bool eof() const;
  
  private:
    /*
     * Following are private helper functions
     */
    void ReadNextToken();
    void CheckUnexpectedEof() const;
    void SkipExpectedToken(PgnTokenType type, const std::string& value);
    void CheckExpectedTokenType(PgnTokenType type);
    void CheckExpectedTokenValue(const std::string& value);

    void ParseTags(PgnTags& tags);
    void ParseVariation(Chessboard board, unsigned int first_move_number, bool first_move_white, PgnVariation* variation);
    PgnMove* ParseMove(const Chessboard& board);
    PgnNag* ParseNag();
    PgnNag* ParseSuffixAnnotation();
    PgnComment* ParseComment();
    PgnResult ParseResult();
  };
}

#endif // INCLUDE_PGN_PARSER_HPP_
