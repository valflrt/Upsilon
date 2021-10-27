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
      // TODO: Factorize this code
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
  // TODO: Factorize this code
  if (strncmp(k_fracCommand, m_text, strlen(k_fracCommand)) == 0) {
    const char * endOfCommand= m_text + strlen(k_fracCommand);
    if (*endOfCommand == ' ' || *endOfCommand == '{') {
      m_text += strlen(k_fracCommand);
      return popFracCommand();
    } 
  }
  else if (strncmp(k_sqrtCommand, m_text, strlen(k_sqrtCommand)) == 0) {
    const char * endOfCommand= m_text + strlen(k_sqrtCommand);
    if (*endOfCommand == ' ' || *endOfCommand == '{' || *endOfCommand == '[') {
      m_text += strlen(k_sqrtCommand);
      return popSqrtCommand();
    }
  }
  else if (strncmp(k_thetaCommand, m_text, strlen(k_thetaCommand)) == 0) {
    const char * endOfCommand = m_text + strlen(k_thetaCommand);
    if (*endOfCommand == ' ' || *endOfCommand == '\\' || *endOfCommand == '$') {
      m_text += strlen(k_thetaCommand);
      return popThetaCommand();
    }
  }
  else if (strncmp(k_piCommand, m_text, strlen(k_piCommand)) == 0) {
    const char * endOfCommand = m_text + strlen(k_piCommand);
    if (*endOfCommand == ' ' || *endOfCommand == '\\' || *endOfCommand == '$') {
      m_text += strlen(k_piCommand);
      return popPiCommand();
    }
  }
  else if (strncmp(k_overRightArrowCommand, m_text, strlen(k_overRightArrowCommand)) == 0) {
    const char * endOfCommand = m_text + strlen(k_overRightArrowCommand);
    if (*endOfCommand == ' ' || *endOfCommand == '{' || *endOfCommand == '[') {
      m_text += strlen(k_overRightArrowCommand);
      return popOverrightarrow();
    }
  }
  
  m_hasError = true;
  return LayoutHelper::String(m_text, strlen(m_text));
}

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

Layout TexParser::popOverrightarrow() {
  return VectorLayout::Builder(popBlock());
}

Layout TexParser::popThetaCommand() {
  return CodePointLayout::Builder(CodePoint(0x3b8));
}

Layout TexParser::popPiCommand() {
  return CodePointLayout::Builder(CodePoint(0x3c0));
}

}
