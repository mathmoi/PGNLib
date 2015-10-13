/**
* @file Piece.hpp
*
* Contains the Piece class.
*
* @author Mathieu Pagé (m@mathieupage.com)
*/
#ifndef INCLUDE_PIECE_HPP_
#define INCLUDE_PIECE_HPP_

#include <unordered_map>
#include <cstdint>

namespace m8db
{
  /**
   * Color of a piece.
   */
  enum class Color : uint_fast8_t
  {
    WHITE = 0,
    BLACK = 1
  };

  /**
   * Get the oposite color from the color passed in parameter.
   *
   * @param   c   Original color
   *
   * @return  The oposite color.
   */
  inline Color GetOtherSide(Color c)
  {
    return static_cast<Color>(static_cast<size_t>(c) ^ 1u);
  }

  /**
   * Type of a piece.
   */
  enum class PieceType : size_t
  {
    NONE = 0,
    PAWN = 2,
    KNIGHT = 4,
    BISHOP = 10,
    ROOK = 12,
    QUEEN = 14,
    KING = 6
  };

  /**
   * Create an std::unordered_map that maps characters to a pice type.
   *
   * @returns A std::unordered_map that maps between characters and piece type.
   */
  inline std::unordered_map<char, PieceType> CreateCharToPieceTypeMap()
  {
     std::unordered_map<char, PieceType> map;
     map['R'] = PieceType::ROOK;
     map['N'] = PieceType::KNIGHT;
     map['B'] = PieceType::BISHOP;
     map['Q'] = PieceType::QUEEN;
     map['K'] = PieceType::KING;
     map['P'] = PieceType::PAWN;
     return map;
  }

  static const std::unordered_map<char, PieceType> CHAR_TO_PIECE_TYPE_MAP = CreateCharToPieceTypeMap();

  /**
   * Represents a chess piece.
   */
  class Piece
  {
  private:
    size_t piece_;

  public:
    /**
     * Default constructor of the class.
     *
     * Create a piece with it's type to PieceType::NONE.
     */
    inline Piece()
      : piece_(static_cast<size_t>(PieceType::NONE))
     {};

    /**
     * Constructor of the class.
     *
     * Created a piece with the type and color passed as parameter.
     *
     * @param   t   Type of the piece.
     * @param   c   Color of the piece.
     */
    inline Piece(PieceType t, Color c)
      : piece_(static_cast<size_t>(t) + static_cast<size_t>(c))
     {};

    /**
     * Get the type of the piece.
     *
     * @return The type of the piece.
     */
    inline PieceType type() const { return static_cast<PieceType>(piece_ & ~1); };

    /**
     * Get the color of the piece
     *
     * @retrun The color of the piece.
     */
    inline Color color() const { return static_cast<Color>(piece_ & 1); };

    /**
     * Indicate if the piece is a slider.
     *
     * The Piece class has an efficient way to test if a piece is a slider.
     * this function can be used to test if the piece is a slider (a rook, a 
     * bishop or a queen).
     *
     * @return  True if the piece is a slider, false otherwise.
     */
    inline bool slide() const { return (piece_ & 8) != 0; };

    /**
     * Indicate if the piece slides like a rook.
     *
     * This function tests if the piece can slide like a rook, that is 
     * horizontally or vertically. Rooks and queens do slide like rooks.
     */
    inline bool slide_like_rook() const { return (piece_ & 6) == 6; }

    /**
     * Typecast operator to size_t.
     *
     * This allows the Piece type to be used as an index to arrays.
     */
    inline operator size_t() const { return piece_; };
  };
}

#endif // INCLUDE_PIECE_HPP_
