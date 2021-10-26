#include "tex_parser.h"
#include <ion/unicode/utf8_decoder.h>

namespace Reader {

TexParser::TexParser(const char * text, const char * endOfText) : 
  m_text(text), 
  m_endOfText(endOfText),
  m_hasError(false)
{
    
}

Layout TexParser::getLayout() {
  Layout layout = popText(0);

  if (m_hasError) {
    return CodePointLayout::Builder(CodePoint(0xfffd));
  }

  return layout;
}

Layout TexParser::popBlock() {
  while (*m_text == ' ') {
    m_text ++;
  }

  if (*m_text == '{') {
    m_text ++;
    return popText('}');
  }

  if (*m_text == '\\') {
    m_text ++;
    return popCommand();
  }

  if (m_text >= m_endOfText) {
    m_hasError = true;
  }

  UTF8Decoder decoder(m_text);
  m_text ++;
  return CodePointLayout::Builder(decoder.nextCodePoint());
}

Layout TexParser::popText(char stop) {
  HorizontalLayout layout = HorizontalLayout::Builder();
  const char * start = m_text;
  
  while (m_text < m_endOfText && *m_text != stop) {
    switch (*m_text) {
      case '\\':
        if (start != m_text) {
          layout.addOrMergeChildAtIndex(LayoutHelper::String(start, m_text - start), layout.numberOfChildren(), false);
        }
        m_text ++;
        layout.addOrMergeChildAtIndex(popCommand(), layout.numberOfChildren(), false);
        start = m_text;
        break;
      case ' ':
        if (start != m_text) {
          layout.addOrMergeChildAtIndex(LayoutHelper::String(start, m_text - start), layout.numberOfChildren(), false);
        }
        m_text ++;
        start = m_text;
        break;
      case '^':
        if (start != m_text) {
          layout.addOrMergeChildAtIndex(LayoutHelper::String(start, m_text - start), layout.numberOfChildren(), false);
        }
        m_text ++;
        layout.addOrMergeChildAtIndex(VerticalOffsetLayout::Builder(popBlock(), VerticalOffsetLayoutNode::Position::Superscript), layout.numberOfChildren(), false);
        start = m_text;
        break;
      case '_':
        if (start != m_text) {
          layout.addOrMergeChildAtIndex(LayoutHelper::String(start, m_text - start), layout.numberOfChildren(), false);
        }
        m_text ++;
        layout.addOrMergeChildAtIndex(VerticalOffsetLayout::Builder(popBlock(), VerticalOffsetLayoutNode::Position::Subscript), layout.numberOfChildren(), false);
        start = m_text;
        break;
      default:
        m_text ++;
    }
  }

  if (start != m_text) {
    layout.addOrMergeChildAtIndex(LayoutHelper::String(start, m_text - start), layout.numberOfChildren(), false);
  }
  
  m_text ++;

  if (layout.numberOfChildren() == 1) {
    return layout.squashUnaryHierarchyInPlace();
  }

  return layout;
}

Layout TexParser::popCommand() {
  if (strncmp(k_fracCommand, m_text, strlen(k_fracCommand)) == 0) {
    m_text += strlen(k_fracCommand);
    if (*m_text == ' ' || *m_text == '{') {
      return popFracCommand();
    } 
  }
  else if (strncmp(k_sqrtCommand, m_text, strlen(k_sqrtCommand)) == 0) {
    m_text += strlen(k_sqrtCommand);
    if (*m_text == ' ' || *m_text == '{' || *m_text == '[') {
      return popSqrtCommand();
    }
  }
  else if (strncmp(k_thetaCommand, m_text, strlen(k_thetaCommand)) == 0) {
    m_text += strlen(k_thetaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popthetaCommand();
    }
  }
  else if (strncmp(k_piCommand, m_text, strlen(k_piCommand)) == 0) {
    m_text += strlen(k_piCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return poppiCommand();
    }
  }
  else if (strncmp(k_timesCommand, m_text, strlen(k_timesCommand)) == 0) {
    m_text += strlen(k_timesCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return poptimesCommand();
    }
  }
  else if (strncmp(k_divCommand, m_text, strlen(k_divCommand)) == 0) {
    m_text += strlen(k_divCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popdivCommand();
    }
  }
  else if (strncmp(k_forallCommand, m_text, strlen(k_forallCommand)) == 0) {
    m_text += strlen(k_forallCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popforallCommand();
    }
  }
  else if (strncmp(k_partialCommand, m_text, strlen(k_partialCommand)) == 0) {
    m_text += strlen(k_partialCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return poppartialCommand();
    }
  }
  else if (strncmp(k_existsCommand, m_text, strlen(k_existsCommand)) == 0) {
    m_text += strlen(k_existsCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popexistsCommand();
    }
  }
  
  m_hasError = true;
  return LayoutHelper::String(m_text, strlen(m_text));
}

// Expressions
Layout TexParser::popFracCommand() {
  Layout numerator = popBlock();
  Layout denominator = popBlock();
  FractionLayout l = FractionLayout::Builder(numerator, denominator);
  return l;
}

Layout TexParser::popSqrtCommand() {
  while (*m_text == ' ') {
    m_text ++;
  }
  if (*m_text == '[') {
    m_text ++;
    Layout rootFactor = popText(']');
    Layout belowRoot = popBlock();
    return NthRootLayout::Builder(belowRoot, rootFactor);
  }
  else {
    return NthRootLayout::Builder(popBlock());
  }
}

// Symbols
Layout TexParser::poptimesCommand() {
  return CodePointLayout::Builder(CodePoint(0xd7));
}

Layout TexParser::popdivCommand() {
  return CodePointLayout::Builder(CodePoint(0xf7));
}

Layout TexParser::popforallCommand() {
  return CodePointLayout::Builder(CodePoint(0x2200));
}

Layout TexParser::poppartialCommand() {
  return CodePointLayout::Builder(CodePoint(0x2202));
}

Layout TexParser::popexistsCommand() {
  return CodePointLayout::Builder(CodePoint(0x2203));
}

// Greek small letters
Layout TexParser::popalphaCommand() {
  return CodePointLayout::Builder(CodePoint(0x3b1));
}

Layout TexParser::popbetaCommand() {
  return CodePointLayout::Builder(CodePoint(0x3b2));
}

Layout TexParser::popgammaCommand() {
  return CodePointLayout::Builder(CodePoint(0x3b3));
}

Layout TexParser::popdeltaCommand() {
  return CodePointLayout::Builder(CodePoint(0x3b4));
}

Layout TexParser::popepsilonCommand() {
  return CodePointLayout::Builder(CodePoint(0x3b5));
}

Layout TexParser::popzetaCommand() {
  return CodePointLayout::Builder(CodePoint(0x3b6));
}

Layout TexParser::popetaCommand() {
  return CodePointLayout::Builder(CodePoint(0x3b7));
}

Layout TexParser::popthetaCommand() {
  return CodePointLayout::Builder(CodePoint(0x3b8));
}

Layout TexParser::popiotaCommand(){
  return CodePointLayout::Builder(CodePoint(0x3b9));
}

Layout TexParser::popkappaCommand(){
  return CodePointLayout::Builder(CodePoint(0x3ba));
}

Layout TexParser::poplambdaCommand(){
  return CodePointLayout::Builder(CodePoint(0x3bb));
}

Layout TexParser::popmuCommand(){
  return CodePointLayout::Builder(CodePoint(0x3bc));
}

Layout TexParser::popnuCommand(){
  return CodePointLayout::Builder(CodePoint(0x3bd));
}

Layout TexParser::popksiCommand(){
  return CodePointLayout::Builder(CodePoint(0x3be));
}

Layout TexParser::poppiCommand() {
  return CodePointLayout::Builder(CodePoint(0x3c0));
}

Layout TexParser::poprhoCommand(){
  return CodePointLayout::Builder(CodePoint(0x3c1));
}

Layout TexParser::popsigmaCommand(){
  return CodePointLayout::Builder(CodePoint(0x3c3));
}

Layout TexParser::poptauCommand(){
  return CodePointLayout::Builder(CodePoint(0x3c4));
}

Layout TexParser::popupsilonCommand(){
  return CodePointLayout::Builder(CodePoint(0x3c5));
}

Layout TexParser::popphiCommand(){
  return CodePointLayout::Builder(CodePoint(0x3c6));
}

Layout TexParser::popkhiCommand(){
  return CodePointLayout::Builder(CodePoint(0x3c7));
}

Layout TexParser::poppsiCommand(){
  return CodePointLayout::Builder(CodePoint(0x3c8));
}

Layout TexParser::popomegaCommand(){
  return CodePointLayout::Builder(CodePoint(0x3c9));
}


}