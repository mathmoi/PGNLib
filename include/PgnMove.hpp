#ifndef INCLUDE_PGN_MOVE_HPP_
#define INCLUDE_PGN_MOVE_HPP_

#include "Piece.hpp"
#include "PgnMoveTextItem.hpp"

namespace PgnLib
{
  typedef size_t Position;
  
  /**
   * Represent a chess move in a PGN game's movetext
   *
   * Moves are represented by 3 properties, the from and to coordinates and 
   * the promotion piece type for pawn promotions.
   *
   * The from and to coordinates have values from 0 to 63. 0 represents a1, 7 
   * represents h1 and 63 represents h8.
   *
   * If the piece is a pawn promotion the promotion_piece_type property will
   * have a value indicating what piece the pawn promotes to. If it's not a
   * pawn promotion, this property will have a value of `PieceType::NONE`.
   *
   * The castling move are encoded using the from and to coordinates 
   * corresponding to the two square move of the castling king. For example,
   * the white king kingside castling would have a from value of 4 (e1) and a
   * to value of 6 (g1).
   */
  class PgnMove : public PgnMoveTextItem
  {
  private:
    Position from_;
    Position to_;
    PieceType promotion_piece_type_;
  public:
    /**
     * Constructor
     *
     * @param   from  Coordinates of the origin square
     *
     * @param   to    Coordinates of the destination square
     *
     * @param   promotion_piece_type  Type of the piece the pawn promotes to 
     *                                if the move is a pawn promotion
     */
    PgnMove(Position from, Position to, PieceType promotion_piece_type)
      : from_(from),
        to_(to),
        promotion_piece_type_(promotion_piece_type)
    {};

    /**
     * Creates a copy of the PgnMove.
     *
     * This function create a dynamically allocated copy of the item. The code
     * which calls the function must assume ownership of the allocated memory 
     * and is responsible for releasing it eventually.
     *
     * @return a pointer to a dynamically allocated copy of the object.
     */
    inline PgnMoveTextItem* Clone() const { return new PgnMove(from_, to_, promotion_piece_type_); };
    
    /**
     * Get the from (origin) position of the piece moved
     *
     * @return  Origin position of the moved piece
     */
    inline Position from() const { return from_; };

    /** 
     * Set the from (origin) position of the piece moved
     *
     * @param   from  New origin position of the moved piece
     */
    inline void set_from(Position from) { from_ = from; };

    /**
     * Get the to (destination) position of the piece moved
     *
     * @return  Origin position of the moved piece
     */
    inline Position to() const { return to_; };

    /** 
     * Set the to (destination) position of the piece moved
     *
     * @param   to  New destination position of the moved piece
     */
    inline void set_to(Position to) { to_ = to; };

    /**
     * Get the type of the piece the pawn is promoted to in case the move is a 
     * pawn promition.
     *
     * @return  If the move is a pawn promotion, type of the piece the pawn is 
     *          promoted to. If the move is not a promotion then 
     *          `PieceType::NONE`.
     */
    inline PieceType promotion_piece_type() const { return promotion_piece_type_; };

    /**
     * Set the type of the piece the pawn is promoted to in case the move is a 
     * pawn promotion.
     *
     * If the move is not a pawn promotion this property should be set to 
     * `PieceType::NONE`.
     *
     * @param   promotion_piece_type  If the move is a pawn promotion, type of 
     *                                the piece the pawn is promoted to. If 
     *                                the move is not a promotion, 
     *                                `PieceType::NONE`.
     */
    inline void set_promotion_piece_type(PieceType promotion_piece_type) { promotion_piece_type_ = promotion_piece_type; };
  };
}

#endif // INCLUDE_PGN_MOVE_HPP_
