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

  // Symbols
  Layout poptimesCommand();
  Layout popdivCommand();
  Layout popforallCommand();
  Layout poppartialCommand();
  Layout popexistsCommand();
  Layout poppmCommand();
  Layout popinftyCommand();
  Layout popapproxCommand();
  Layout popneqCommand();
  Layout popequivCommand();
  Layout popleqCommand();  
  Layout popgeqCommand();

  // Arrows
  Layout popleftarrowCommand();
  Layout popuparrowCommand();
  Layout poprightarrowCommand();
  Layout popdownarrowCommand();
  Layout popleftrightarrowCommand();
  Layout popupdownarrowCommand();
  Layout popLeftarrowCommand();
  Layout popUparrowCommand();
  Layout popRightarrowCommand();
  Layout popDownarrowCommand();

  // Greek capital letters

  Layout popAlphaCommand();
  Layout popBetaCommand();
  Layout popGammaCommand();
  Layout popDeltaCommand();
  Layout popEpsilonCommand();
  Layout popZetaCommand();
  Layout popEtaCommand();
  Layout popThetaCommand();
  Layout popIotaCommand();
  Layout popKappaCommand();
  Layout popLambdaCommand();
  Layout popMuCommand();
  Layout popNuCommand();
  Layout popKsiCommand();
  Layout popOmicronCommand();
  Layout popPiCommand();
  Layout popRhoCommand();
  Layout popSigmaCommand();
  Layout popTauCommand();
  Layout popUpsilonCommand();
  Layout popPhiCommand();
  Layout popKhiCommand();
  Layout popPsiCommand();
  Layout popOmegaCommand();

  // Greek small letters
  Layout popalphaCommand();
  Layout popbetaCommand();
  Layout popgammaCommand();
  Layout popdeltaCommand();
  Layout popepsilonCommand();
  Layout popzetaCommand();
  Layout popetaCommand();
  Layout popthetaCommand();
  Layout popiotaCommand();
  Layout popkappaCommand();
  Layout poplambdaCommand();
  Layout popmuCommand();
  Layout popnuCommand();
  Layout popksiCommand();
  Layout poppiCommand();
  Layout poprhoCommand();
  Layout popsigmaCommand();
  Layout poptauCommand();
  Layout popupsilonCommand();
  Layout popphiCommand();
  Layout popkhiCommand();
  Layout poppsiCommand();
  Layout popomegaCommand();

  const char * m_text;
  const char * m_endOfText;
  bool m_hasError;

  // Expressions
  static constexpr char const * k_fracCommand = "frac";
  static constexpr char const * k_sqrtCommand = "sqrt";

  // Symbols
  static constexpr char const * k_timesCommand = "times";
  static constexpr char const * k_divCommand = "div";
  static constexpr char const * k_forallCommand = "forall";
  static constexpr char const * k_partialCommand = "partial";
  static constexpr char const * k_existsCommand = "exists";
  static constexpr char const * k_pmCommand = "pm";
  static constexpr char const * k_inftyCommand = "infty";
  static constexpr char const * k_approxCommand = "approx";
  static constexpr char const * k_neqCommand = "neq";
  static constexpr char const * k_equivCommand = "equiv";
  static constexpr char const * k_leqCommand = "leq";
  static constexpr char const * k_geqCommand = "geq";


  // Arrows
  static constexpr char const * k_leftarrowCommand = "leftarrow";
  static constexpr char const * k_uparrowCommand = "uparrow";
  static constexpr char const * k_rightarrowCommand = "rightarrow";
  static constexpr char const * k_downarrowCommand = "downarrow";
  static constexpr char const * k_leftrightarrowCommand = "leftrightarrow";
  static constexpr char const * k_updownarrowCommand = "updownarrow";
  static constexpr char const * k_LeftarrowCommand = "Leftarrow";
  static constexpr char const * k_UparrowCommand = "Uparrow";
  static constexpr char const * k_RightarrowCommand = "Rightarrow";
  static constexpr char const * k_DownarrowCommand = "Downarrow";
  // Greek capital letters

  static constexpr char const * k_AlphaCommand = "Alpha";
  static constexpr char const * k_BetaCommand = "Beta";
  static constexpr char const * k_GammaCommand = "Gamma";
  static constexpr char const * k_DeltaCommand = "Delta";
  static constexpr char const * k_EpsilonCommand = "Epsilon";
  static constexpr char const * k_ZetaCommand = "Zeta";
  static constexpr char const * k_EtaCommand = "Eta";
  static constexpr char const * k_ThetaCommand = "Theta";
  static constexpr char const * k_IotaCommand = "Iota";
  static constexpr char const * k_KappaCommand = "Kappa";
  static constexpr char const * k_LambdaCommand = "Lambda";
  static constexpr char const * k_MuCommand = "Mu";
  static constexpr char const * k_NuCommand = "Nu";
  static constexpr char const * k_KsiCommand = "Ksi";
  static constexpr char const * k_OmicronCommand = "Omicron";
  static constexpr char const * k_PiCommand = "Pi";
  static constexpr char const * k_RhoCommand = "Rho";
  static constexpr char const * k_SigmaCommand = "Sigma";
  static constexpr char const * k_TauCommand = "Tau";
  static constexpr char const * k_UpsilonCommand = "Upsilon";
  static constexpr char const * k_PhiCommand = "Phi";
  static constexpr char const * k_KhiCommand = "Khi";
  static constexpr char const * k_PsiCommand = "Psi";
  static constexpr char const * k_OmegaCommand = "Omega";

  // Greek small letters
  static constexpr char const * k_alphaCommand = "alpha";
  static constexpr char const * k_betaCommand = "beta";
  static constexpr char const * k_gammaCommand = "gamma";
  static constexpr char const * k_deltaCommand = "delta";
  static constexpr char const * k_epsilonCommand = "epsilon";
  static constexpr char const * k_zetaCommand = "zeta";
  static constexpr char const * k_etaCommand = "eta";
  static constexpr char const * k_thetaCommand = "theta";
  static constexpr char const * k_iotaCommand = "iota";
  static constexpr char const * k_kappaCommand = "kappa";
  static constexpr char const * k_lambdaCommand = "lambda";
  static constexpr char const * k_muCommand = "mu";
  static constexpr char const * k_nuCommand = "nu";
  static constexpr char const * k_ksiCommand = "ksi";
  // static constexpr char const * k_omicronCommand = "omicron"; // just write "o" 
  static constexpr char const * k_piCommand = "pi";
  static constexpr char const * k_rhoCommand = "rho";
  static constexpr char const * k_sigmaCommand = "sigma";
  static constexpr char const * k_tauCommand = "tau";
  static constexpr char const * k_upsilonCommand = "upsilon";
  static constexpr char const * k_phiCommand = "phi";
  static constexpr char const * k_khiCommand = "khi";
  static constexpr char const * k_psiCommand = "psi";
  static constexpr char const * k_omegaCommand = "omega";

};
  
}

#endif
