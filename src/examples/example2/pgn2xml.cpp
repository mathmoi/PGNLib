#include <iostream>

#include <PgnParser.hpp>

void ProcessTags(const PgnLib::PgnTags& tags, const std::string indent)
{
  std::cout <<indent <<"<tags>" <<std::endl;

  for (auto tag : tags)
  {
    std::cout <<indent <<"  " <<"<tag name=\"" <<tag.first <<"\" value=\"" <<tag.second <<"\" />" <<std::endl;
  }

  std::cout <<indent <<"</tags>" <<std::endl;
}

void ProcessMove(const PgnLib::PgnMove& move, const std::string indent)
{
  std::cout <<indent <<"<move from=\"" <<move.from() <<"\" to=\"" <<move.to() <<"\"";

  if (move.promotion_piece_type() != PgnLib::PieceType::NONE)
  {
    std::cout <<" promote_to=\"";
    switch (move.promotion_piece_type())
    {
    case PgnLib::PieceType::QUEEN:
      std::cout <<'Q';
      break;

    case PgnLib::PieceType::ROOK:
      std::cout <<'R';
      break;

    case PgnLib::PieceType::KNIGHT:
      std::cout <<'K';
      break;

    case PgnLib::PieceType::BISHOP:
      std::cout <<'B';
      break;

    case PgnLib::PieceType::PAWN:
    case PgnLib::PieceType::KING:
    case PgnLib::PieceType::NONE:
      break;
    }
    std::cout <<"\"";
  }

  std::cout <<" />" <<std::endl;
}

void ProcessComment(const PgnLib::PgnComment& comment, const std::string indent)
{
  std::cout <<indent <<"<comment>" <<comment.comment() <<"</comment>" <<std::endl;
}

void ProcessNag(const PgnLib::PgnNag& nag, const std::string indent)
{
  std::cout <<indent <<"<nag value=\"" <<static_cast<unsigned int>(nag.nag()) <<"\" />" <<std::endl;
}

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

void ProcessGame(const PgnLib::PgnGame& game, const std::string& indent)
{
  std::cout <<indent <<"<game>" <<std::endl;
  ProcessTags(game.tags(), indent + "  ");
  ProcessVariation(static_cast<const PgnLib::PgnVariation*>(&game), "movetext", indent + "  ");
  std::cout <<indent <<"</game>" <<std::endl;
}

int main(int, char**)
{
  std::string indent = "";
  PgnLib::PgnParser parser(&std::cin);

  std::cout <<indent <<"<games>" <<std::endl;

  while (!parser.eof())
  {
    PgnLib::PgnGame game = parser.ParseSingleGame();
    ProcessGame(game, indent + "  ");
  }

  std::cout <<indent <<"</games>" <<std::endl;

  return 0;
}
