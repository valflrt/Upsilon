#ifndef __TEX_PARSER_H__
#define __TEX_PARSER_H__

#include <poincare_layouts.h>
#include <poincare/layout_helper.h>
#include <string.h>

using namespace Poincare;

namespace Reader
{
/// @brief Class used in the WordWrapTextView class to parse a Tex expression
class TexParser {
public:
  TexParser(const char * text, const char * endOfText);
  Layout getLayout();
private:
  Layout popBlock();
  Layout popText(char stop);
  Layout popCommand();
  Layout popFracCommand();
  Layout popSqrtCommand();
  Layout popPiCommand();
  Layout popThetaCommand();
  const char * m_text;
  const char * m_endOfText;
  bool m_hasError;

  static constexpr char const * k_fracCommand = "frac";
  static constexpr char const * k_sqrtCommand = "sqrt";
  static constexpr char const * k_thetaCommand = "theta";
  static constexpr char const * k_piCommand = "pi";
};
  
}

#endif
