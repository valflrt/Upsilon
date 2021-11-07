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

  // Expressions
  Layout popFracCommand();
  Layout popSqrtCommand();

  //Symbols
  Layout popSymbolCommand(int SymbolIndex);

  const char * m_text;
  const char * m_endOfText;
  bool m_hasError;

  // Expressions that require specific handling
  static constexpr char const * k_fracCommand = "frac";
  static constexpr char const * k_sqrtCommand = "sqrt";

  static constexpr int const k_NumberOfSymbols = 70;
  static constexpr int const k_NumberOfFunctionCommands = 32;

  // List of available Symbols
  static constexpr char const * k_SymbolsCommands[k_NumberOfSymbols] = {
    "times", "div", "forall", "partial", "exists", "pm", "approx", "infty", "neq", "equiv", "leq", "geq", 
    "leftarrow", "uparrow", "rightarrow", "downarrow", "leftrightarrow", "updownarrow", "Leftarrow", "Uparrow", "Rightarrow", "Downarrow",
    "Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Zeta", "Eta", "Theta", "Iota", "Kappa", "Lambda", 
    "Mu", "Nu", "Xi", "Omicron", "Pi", "Rho", "Sigma", "Tau", "Upsilon", "Phi", "Chi", "Psi","Omega",
    "alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", 
    "mu", "nu", "xi", "omicron", "pi", "rho", "sigma", "tau", "upsilon", "phi", "chi", "psi", "omega",
  };

  //List of the available Symbol's CodePoints in the same order of the Symbol's list
  static constexpr uint32_t const k_SymbolsCodePoints[k_NumberOfSymbols] = {
    0xd7, 0xf7, 0x2200, 0x2202, 0x2203, 0xb1, 0x2248, 0x221e, 0x2260, 0x2261, 0x2264, 0x2265, 
    0x2190, 0x2191, 0x2192, 0x2193, 0x2194, 0x2195, 0x21d0, 0x21d1, 0x21d2, 0x21d3, 
    0x391, 0x392, 0x393, 0x394, 0x395, 0x396, 0x397, 0x398, 0x399, 0x39a, 0x39b, 
    0x39c, 0x39d, 0x39e, 0x39f, 0x3a0, 0x3a1, 0x3a3, 0x3a4, 0x3a5, 0x3a6, 0x3a7, 0x3a8, 0x3a9, 
    0x3b1, 0x3b2, 0x3b3, 0x3b4, 0x3b5, 0x3b6, 0x3b7, 0x3b8, 0x3b9, 0x3ba, 0x3bb, 
    0x3bc, 0x3bd, 0x3be, 0x3bf, 0x3c0, 0x3c1, 0x3c3, 0x3c4, 0x3c5, 0x3c6, 0x3c7, 0x3c8, 0x3c9
  };
  
  // List of available Function Commands that don't require a specific handling
  static constexpr char const * k_FunctionCommands[k_NumberOfFunctionCommands] = {
    "arcos", "arcsin", "arctan", "arg", "cos", "cosh", "cot", "coth", 
    "csc", "deg", "det", "dim", "exp", "gcd", "hom", "inf", 
    "ker", "lg", "lim", "liminf", "limsup", "ln", "log", "max", 
    "min", "Pr", "sec", "sin", "sinh", "sup", "tan", "tanh"
  };

};
  
}

#endif
