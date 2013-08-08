#ifndef INCLUDE_SAN_PARSER_HPP_
#define INCLUDE_SAN_PARSER_HPP_

#include "PgnParserException.hpp"
#include "Chessboard.hpp"
#include "Piece.hpp"
#include "Bitboard.hpp"
#include "PgnMove.hpp"

namespace Pgn
{
  class InvalidMoveException : public PgnParserException
  {
  public:
    InvalidMoveException()
      : PgnParserException("The move is invalid in this position.") {};
  };


  // This function returns the only possible origin position of the move 
  // defined by its parameters.
  //
  // board : Chessboard on which the move takes place.
  //
  // p : Piece moved.
  //
  // to : Destination square of the move.
  //
  // is_capture : Indicate if the move is a capture.
  //
  // from : A bitboard with bit sets for all possible origin squares. If the 
  // SAN move contained a rank of file specifier this bitboard should have bit 
  // set for only this rank or file. If neither is provided in the SAN move 
  // from should have all bit setted.
  //
  // If a unique origin position can not be found a NoOriginException 
  // is thrown.
  Position GetOrigineMove(const Chessboard& board, Piece p, Position to, bool is_capture, Bitboard from);

  // This function parse the san move passed in parameters give the board also 
  // passed in parameters.
  PgnMove ParseSanMove(const Chessboard& board, const std::string& san);
}

#endif // INCLUDE_SAN_PARSER_HPP_
