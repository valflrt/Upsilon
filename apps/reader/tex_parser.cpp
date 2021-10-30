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
  else if (strncmp(k_pmCommand, m_text, strlen(k_pmCommand)) == 0) {
    m_text += strlen(k_pmCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return poppmCommand();
    }
  }
  else if (strncmp(k_inftyCommand, m_text, strlen(k_inftyCommand)) == 0) {
    m_text += strlen(k_inftyCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popinftyCommand();
    }
  }
  else if (strncmp(k_approxCommand, m_text, strlen(k_approxCommand)) == 0) {
    m_text += strlen(k_approxCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popapproxCommand();
    }
  }
  else if (strncmp(k_neqCommand, m_text, strlen(k_neqCommand)) == 0) {
    m_text += strlen(k_neqCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popneqCommand();
    }
  }
  else if (strncmp(k_equivCommand, m_text, strlen(k_equivCommand)) == 0) {
    m_text += strlen(k_equivCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popequivCommand();
    }
  }
  else if (strncmp(k_leftarrowCommand, m_text, strlen(k_leftarrowCommand)) == 0) {
    m_text += strlen(k_leftarrowCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popleftarrowCommand();
    }
  }
  else if (strncmp(k_uparrowCommand, m_text, strlen(k_uparrowCommand)) == 0) {
    m_text += strlen(k_uparrowCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popuparrowCommand();
    }
  }
  else if (strncmp(k_rightarrowCommand, m_text, strlen(k_rightarrowCommand)) == 0) {
    m_text += strlen(k_rightarrowCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return poprightarrowCommand();
    }
  }
  else if (strncmp(k_downarrowCommand, m_text, strlen(k_downarrowCommand)) == 0) {
    m_text += strlen(k_downarrowCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popdownarrowCommand();
    }
  }
  else if (strncmp(k_leftrightarrowCommand, m_text, strlen(k_leftrightarrowCommand)) == 0) {
    m_text += strlen(k_leftrightarrowCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popleftrightarrowCommand();
    }
  }
  else if (strncmp(k_updownarrowCommand, m_text, strlen(k_updownarrowCommand)) == 0) {
    m_text += strlen(k_updownarrowCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popupdownarrowCommand();
    }
  }  
  else if (strncmp(k_LeftarrowCommand, m_text, strlen(k_LeftarrowCommand)) == 0) {
    m_text += strlen(k_LeftarrowCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popLeftarrowCommand();
    }
  }
  else if (strncmp(k_UparrowCommand, m_text, strlen(k_UparrowCommand)) == 0) {
    m_text += strlen(k_UparrowCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popUparrowCommand();
    }
  }
  else if (strncmp(k_RightarrowCommand, m_text, strlen(k_RightarrowCommand)) == 0) {
    m_text += strlen(k_RightarrowCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popRightarrowCommand();
    }
  }
  else if (strncmp(k_DownarrowCommand, m_text, strlen(k_DownarrowCommand)) == 0) {
    m_text += strlen(k_DownarrowCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popDownarrowCommand();
    }
  }

  // Greek capital letters
  else if (strncmp(k_AlphaCommand, m_text, strlen(k_AlphaCommand)) == 0) {
    m_text += strlen(k_AlphaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popAlphaCommand();
    }
  } 
  else if (strncmp(k_BetaCommand, m_text, strlen(k_BetaCommand)) == 0) {
    m_text += strlen(k_BetaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popBetaCommand();
    }
  } 
  else if (strncmp(k_GammaCommand, m_text, strlen(k_GammaCommand)) == 0) {
    m_text += strlen(k_GammaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popGammaCommand();
    }
  } 
  else if (strncmp(k_DeltaCommand, m_text, strlen(k_DeltaCommand)) == 0) {
    m_text += strlen(k_DeltaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popDeltaCommand();
    }
  } 
  else if (strncmp(k_EpsilonCommand, m_text, strlen(k_EpsilonCommand)) == 0) {
    m_text += strlen(k_EpsilonCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popEpsilonCommand();
    }
  } 
  else if (strncmp(k_ZetaCommand, m_text, strlen(k_ZetaCommand)) == 0) {
    m_text += strlen(k_ZetaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popZetaCommand();
    }
  } 
  else if (strncmp(k_EtaCommand, m_text, strlen(k_EtaCommand)) == 0) {
    m_text += strlen(k_EtaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popEtaCommand();
    }
  }
  else if (strncmp(k_ThetaCommand, m_text, strlen(k_ThetaCommand)) == 0) {
    m_text += strlen(k_ThetaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popThetaCommand();
    }
  }
  else if (strncmp(k_IotaCommand, m_text, strlen(k_IotaCommand)) == 0) {
    m_text += strlen(k_IotaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popIotaCommand();
    }
  }
  else if (strncmp(k_KappaCommand, m_text, strlen(k_KappaCommand)) == 0) {
    m_text += strlen(k_KappaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popKappaCommand();
    }
  }
  else if (strncmp(k_LambdaCommand, m_text, strlen(k_LambdaCommand)) == 0) {
    m_text += strlen(k_LambdaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popLambdaCommand();
    }
  }
  else if (strncmp(k_MuCommand, m_text, strlen(k_MuCommand)) == 0) {
    m_text += strlen(k_MuCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popMuCommand();
    }
  }
  else if (strncmp(k_NuCommand, m_text, strlen(k_NuCommand)) == 0) {
    m_text += strlen(k_NuCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popNuCommand();
    }
  }
  else if (strncmp(k_KsiCommand, m_text, strlen(k_KsiCommand)) == 0) {
    m_text += strlen(k_KsiCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popKsiCommand();
    }
  }
  else if (strncmp(k_PiCommand, m_text, strlen(k_PiCommand)) == 0) {
    m_text += strlen(k_PiCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popPiCommand();
    }
  }
  else if (strncmp(k_OmicronCommand, m_text, strlen(k_OmicronCommand)) == 0) {
    m_text += strlen(k_OmicronCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popOmicronCommand();
    }
  }
  else if (strncmp(k_RhoCommand, m_text, strlen(k_RhoCommand)) == 0) {
    m_text += strlen(k_RhoCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popRhoCommand();
    }
  }
  else if (strncmp(k_SigmaCommand, m_text, strlen(k_SigmaCommand)) == 0) {
    m_text += strlen(k_SigmaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popSigmaCommand();
    }
  }
  else if (strncmp(k_TauCommand, m_text, strlen(k_TauCommand)) == 0) {
    m_text += strlen(k_TauCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popTauCommand();
    }
  }
  else if (strncmp(k_UpsilonCommand, m_text, strlen(k_UpsilonCommand)) == 0) {
    m_text += strlen(k_UpsilonCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popUpsilonCommand();
    }
  }
  else if (strncmp(k_PhiCommand, m_text, strlen(k_PhiCommand)) == 0) {
    m_text += strlen(k_PhiCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popPhiCommand();
    }
  }
  else if (strncmp(k_KhiCommand, m_text, strlen(k_KhiCommand)) == 0) {
    m_text += strlen(k_KhiCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popKhiCommand();
    }
  }
  else if (strncmp(k_PsiCommand, m_text, strlen(k_PsiCommand)) == 0) {
    m_text += strlen(k_PsiCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popPsiCommand();
    }
  }
  else if (strncmp(k_OmegaCommand, m_text, strlen(k_OmegaCommand)) == 0) {
    m_text += strlen(k_OmegaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popOmegaCommand();
    }
  }
  else if (strncmp(k_alphaCommand, m_text, strlen(k_alphaCommand)) == 0) {
    m_text += strlen(k_alphaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popalphaCommand();
    }
  } 
  else if (strncmp(k_betaCommand, m_text, strlen(k_betaCommand)) == 0) {
    m_text += strlen(k_betaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popbetaCommand();
    }
  } 
  else if (strncmp(k_gammaCommand, m_text, strlen(k_gammaCommand)) == 0) {
    m_text += strlen(k_gammaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popgammaCommand();
    }
  } 
  else if (strncmp(k_deltaCommand, m_text, strlen(k_deltaCommand)) == 0) {
    m_text += strlen(k_deltaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popdeltaCommand();
    }
  } 
  else if (strncmp(k_epsilonCommand, m_text, strlen(k_epsilonCommand)) == 0) {
    m_text += strlen(k_epsilonCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popepsilonCommand();
    }
  } 
  else if (strncmp(k_zetaCommand, m_text, strlen(k_zetaCommand)) == 0) {
    m_text += strlen(k_zetaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popzetaCommand();
    }
  } 
  else if (strncmp(k_etaCommand, m_text, strlen(k_etaCommand)) == 0) {
    m_text += strlen(k_etaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popetaCommand();
    }
  }
  else if (strncmp(k_thetaCommand, m_text, strlen(k_thetaCommand)) == 0) {
    m_text += strlen(k_thetaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popthetaCommand();
    }
  }
  else if (strncmp(k_iotaCommand, m_text, strlen(k_iotaCommand)) == 0) {
    m_text += strlen(k_iotaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popiotaCommand();
    }
  }
  else if (strncmp(k_kappaCommand, m_text, strlen(k_kappaCommand)) == 0) {
    m_text += strlen(k_kappaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popkappaCommand();
    }
  }
  else if (strncmp(k_lambdaCommand, m_text, strlen(k_lambdaCommand)) == 0) {
    m_text += strlen(k_lambdaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return poplambdaCommand();
    }
  }
  else if (strncmp(k_muCommand, m_text, strlen(k_muCommand)) == 0) {
    m_text += strlen(k_muCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popmuCommand();
    }
  }
  else if (strncmp(k_nuCommand, m_text, strlen(k_nuCommand)) == 0) {
    m_text += strlen(k_nuCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popnuCommand();
    }
  }
  else if (strncmp(k_ksiCommand, m_text, strlen(k_ksiCommand)) == 0) {
    m_text += strlen(k_ksiCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popksiCommand();
    }
  }
  else if (strncmp(k_piCommand, m_text, strlen(k_piCommand)) == 0) {
    m_text += strlen(k_piCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return poppiCommand();
    }
  }
  else if (strncmp(k_rhoCommand, m_text, strlen(k_rhoCommand)) == 0) {
    m_text += strlen(k_rhoCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return poprhoCommand();
    }
  }
  else if (strncmp(k_sigmaCommand, m_text, strlen(k_sigmaCommand)) == 0) {
    m_text += strlen(k_sigmaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popsigmaCommand();
    }
  }
  else if (strncmp(k_tauCommand, m_text, strlen(k_tauCommand)) == 0) {
    m_text += strlen(k_tauCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return poptauCommand();
    }
  }
  else if (strncmp(k_upsilonCommand, m_text, strlen(k_upsilonCommand)) == 0) {
    m_text += strlen(k_upsilonCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popupsilonCommand();
    }
  }
  else if (strncmp(k_phiCommand, m_text, strlen(k_phiCommand)) == 0) {
    m_text += strlen(k_phiCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popphiCommand();
    }
  }
  else if (strncmp(k_khiCommand, m_text, strlen(k_khiCommand)) == 0) {
    m_text += strlen(k_khiCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popkhiCommand();
    }
  }
  else if (strncmp(k_psiCommand, m_text, strlen(k_psiCommand)) == 0) {
    m_text += strlen(k_psiCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return poppsiCommand();
    }
  }
  else if (strncmp(k_omegaCommand, m_text, strlen(k_omegaCommand)) == 0) {
    m_text += strlen(k_omegaCommand);
    if (*m_text == ' ' || *m_text == '\\' || *m_text == '$') {
      return popomegaCommand();
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

Layout TexParser::poppmCommand() {
  return CodePointLayout::Builder(CodePoint(0xb1));
}

Layout TexParser::popapproxCommand() {
  return CodePointLayout::Builder(CodePoint(0x2248));
}

Layout TexParser::popinftyCommand() {
  return CodePointLayout::Builder(CodePoint(0x221e));
}

Layout TexParser::popneqCommand() {
  return CodePointLayout::Builder(CodePoint(0x2260));
}

Layout TexParser::popequivCommand() {
  return CodePointLayout::Builder(CodePoint(0x2261));
}

Layout TexParser::popleftarrowCommand() {
  return CodePointLayout::Builder(CodePoint(0x2190));
}

Layout TexParser::popuparrowCommand() {
  return CodePointLayout::Builder(CodePoint(0x2191));
}

Layout TexParser::poprightarrowCommand() {
  return CodePointLayout::Builder(CodePoint(0x2192));
}

Layout TexParser::popdownarrowCommand() {
  return CodePointLayout::Builder(CodePoint(0x2193));
}

Layout TexParser::popleftrightarrowCommand() {
  return CodePointLayout::Builder(CodePoint(0x2194));
}

Layout TexParser::popupdownarrowCommand() {
  return CodePointLayout::Builder(CodePoint(0x2195));
}

Layout TexParser::popLeftarrowCommand() {
  return CodePointLayout::Builder(CodePoint(0x21d0));
}

Layout TexParser::popUparrowCommand() {
  return CodePointLayout::Builder(CodePoint(0x21d1));
}

Layout TexParser::popRightarrowCommand() {
  return CodePointLayout::Builder(CodePoint(0x21d2));
}

Layout TexParser::popDownarrowCommand() {
  return CodePointLayout::Builder(CodePoint(0x21d3));
}

// Greek Capital letters
Layout TexParser::popAlphaCommand() {
  return CodePointLayout::Builder(CodePoint(0x391));
}

Layout TexParser::popBetaCommand() {
  return CodePointLayout::Builder(CodePoint(0x392));
}

Layout TexParser::popGammaCommand() {
  return CodePointLayout::Builder(CodePoint(0x393));
}

Layout TexParser::popDeltaCommand() {
  return CodePointLayout::Builder(CodePoint(0x394));
}

Layout TexParser::popEpsilonCommand() {
  return CodePointLayout::Builder(CodePoint(0x395));
}

Layout TexParser::popZetaCommand() {
  return CodePointLayout::Builder(CodePoint(0x396));
}

Layout TexParser::popEtaCommand() {
  return CodePointLayout::Builder(CodePoint(0x397));
}

Layout TexParser::popThetaCommand() {
  return CodePointLayout::Builder(CodePoint(0x398));
}

Layout TexParser::popIotaCommand(){
  return CodePointLayout::Builder(CodePoint(0x399));
}

Layout TexParser::popKappaCommand(){
  return CodePointLayout::Builder(CodePoint(0x39a));
}

Layout TexParser::popLambdaCommand(){
  return CodePointLayout::Builder(CodePoint(0x39b));
}

Layout TexParser::popMuCommand(){
  return CodePointLayout::Builder(CodePoint(0x39c));
}

Layout TexParser::popNuCommand(){
  return CodePointLayout::Builder(CodePoint(0x39d));
}

Layout TexParser::popKsiCommand() {
  return CodePointLayout::Builder(CodePoint(0x39e));
}

Layout TexParser::popOmicronCommand() {
  return CodePointLayout::Builder(CodePoint(0x39f));
}

Layout TexParser::popPiCommand() {
  return CodePointLayout::Builder(CodePoint(0x3a0));
}

Layout TexParser::popRhoCommand(){
  return CodePointLayout::Builder(CodePoint(0x3a1));
}

Layout TexParser::popSigmaCommand(){
  return CodePointLayout::Builder(CodePoint(0x3a3));
}

Layout TexParser::popTauCommand(){
  return CodePointLayout::Builder(CodePoint(0x3a4));
}

Layout TexParser::popUpsilonCommand(){
  return CodePointLayout::Builder(CodePoint(0x3a5));
}

Layout TexParser::popPhiCommand(){
  return CodePointLayout::Builder(CodePoint(0x3a6));
}

Layout TexParser::popKhiCommand(){
  return CodePointLayout::Builder(CodePoint(0x3a7));
}

Layout TexParser::popPsiCommand(){
  return CodePointLayout::Builder(CodePoint(0x3a8));
}

Layout TexParser::popOmegaCommand(){
  return CodePointLayout::Builder(CodePoint(0x3a9));
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