#ifndef ESCHER_PALETTE_H
#define ESCHER_PALETTE_H

#include <kandinsky/color.h>

class Palette {
public:

  // Shared
  constexpr static KDColor PrimaryText = KDColor::RGB24(0x000000);
  constexpr static KDColor SecondaryText = KDColor::RGB24(0x6e6e6e);
  constexpr static KDColor AccentText = KDColor::RGB24(0x00857f);
  constexpr static KDColor BackgroundHard = KDColor::RGB24(0xffffff);
  constexpr static KDColor BackgroundApps = KDColor::RGB24(0xfafafa);
  constexpr static KDColor BackgroundAppsSecondary = KDColor::RGB24(0xf0f0f0);
  constexpr static KDColor Toolbar = KDColor::RGB24(0xc03535);
  constexpr static KDColor ToolbarText = KDColor::RGB24(0xffffff);
  constexpr static KDColor ExpressionInputBackground = KDColor::RGB24(0xe0e0e0);
  constexpr static KDColor Battery = KDColor::RGB24(0xffffff);
  constexpr static KDColor BatteryInCharge = KDColor::RGB24(0x179e1f);
  constexpr static KDColor BatteryLow = KDColor::RGB24(0x992321);
  constexpr static KDColor ApproximateSignText = KDColor::RGB24(0x595959);
  constexpr static KDColor ApproximateExpressionText = KDColor::RGB24(0x595959);

  // Controls (switches, gauge, arrows...)
  constexpr static KDColor Control = KDColor::RGB24(0x00857f);
  constexpr static KDColor ControlEnabled = KDColor::RGB24(0x00b2b0);
  constexpr static KDColor ControlDisabled = KDColor::RGB24(0x9e9e9e);

  // Calculation
  constexpr static KDColor CalculationBackgroundOdd = KDColor::RGB24(0xffffff);
  constexpr static KDColor CalculationBackgroundEven = KDColor::RGB24(0xfafafa);
  constexpr static KDColor CalculationEmptyBox = KDColor::RGB24(0xc4c4c4);
  constexpr static KDColor CalculationEmptyBoxNeeded = KDColor::RGB24(0x00857f);
  
  // Code
  constexpr static KDColor CodeBackground = KDColor::RGB24(0x000000);
  constexpr static KDColor CodeBackgroundSelected = KDColor::RGB24(0xe0e0e0);
  constexpr static KDColor CodeText = KDColor::RGB24(0xffffff);
  constexpr static KDColor CodeComment = KDColor::RGB24(0x999988);
  constexpr static KDColor CodeNumber = KDColor::RGB24(0x009999);
  constexpr static KDColor CodeKeyword = KDColor::RGB24(0xff000c);
  constexpr static KDColor CodeOperator = KDColor::RGB24(0xd73a49);
  constexpr static KDColor CodeString = KDColor::RGB24(0x032f62);

  // Probability
  constexpr static KDColor ProbabilityCurve = KDColor::RGB24(0x00857f);

  // Statistics
  constexpr static KDColor StatisticsBox = KDColor::RGB24(0x00857f);
  constexpr static KDColor StatisticsSelect = KDColor::RGB24(0xe0e0e0);

  // Graph
  constexpr static KDColor GraphTangent = KDColor::RGB24(0x595959);

  // SubMenus
  constexpr static KDColor SubMenuBackground = KDColor::RGB24(0xe0e0e0);
  constexpr static KDColor SubMenuBorder = KDColor::RGB24(0xfafafa);
  constexpr static KDColor SubMenuText = KDColor::RGB24(0x000000);

  // Toolbox
  constexpr static KDColor ToolboxHeaderBackground = KDColor::RGB24(0x4a4a4a);
  constexpr static KDColor ToolboxHeaderText = KDColor::RGB24(0xffffff);
  constexpr static KDColor ToolboxHeaderBorder = KDColor::RGB24(0x4a4a4a);
  constexpr static KDColor ToolboxBackground = KDColor::RGB24(0x000000);

  // Lists
  constexpr static KDColor ListCellBackground = KDColor::RGB24(0xffffff);
  constexpr static KDColor ListCellBackgroundSelected = KDColor::RGB24(0xe0e0e0);
  constexpr static KDColor ListCellBorder = KDColor::RGB24(0xededef);

  // Button
  constexpr static KDColor ButtonBackground = KDColor::RGB24(0xe0e0e0);
  constexpr static KDColor ButtonBackgroundSelected = KDColor::RGB24(0xd1d1d1);
  constexpr static KDColor ButtonBackgroundSelectedHighContrast = KDColor::RGB24(0x595959);
  constexpr static KDColor ButtonBorder = KDColor::RGB24(0xadadad);
  constexpr static KDColor ButtonShadow = KDColor::RGB24(0x003833);
  constexpr static KDColor ButtonText = KDColor::RGB24(0x000000);

  // Tabs
  constexpr static KDColor TabBackground = KDColor::RGB24(0x4a4a4a);
  constexpr static KDColor TabBackgroundSelected = KDColor::RGB24(0x757575);
  constexpr static KDColor TabBackgroundActive = KDColor::RGB24(0xfafafa);
  constexpr static KDColor TabBackgroundSelectedAndActive = KDColor::RGB24(0xe3e3e3);
  constexpr static KDColor TabText = KDColor::RGB24(0xffffff);
  constexpr static KDColor TabTextActive = KDColor::RGB24(0x000000);

  // SubTabs
  constexpr static KDColor SubTabBackground = KDColor::RGB24(0xe0e0e0);
  constexpr static KDColor SubTabBackgroundSelected = KDColor::RGB24(0xd1d1d1);
  constexpr static KDColor SubTabText = KDColor::RGB24(0x000000);

  // Banners
  constexpr static KDColor BannerFirstBackground = KDColor::RGB24(0x4a4a4a);
  constexpr static KDColor BannerFirstBorder = KDColor::RGB24(0x4a4a4a);
  constexpr static KDColor BannerFirstText = KDColor::RGB24(0xffffff);
  constexpr static KDColor BannerFirstVariantBackground = KDColor::RGB24(0x4a4a4a);
  constexpr static KDColor BannerFirstVariantBorder = KDColor::RGB24(0xfafafa);
  constexpr static KDColor BannerFirstVariantText = KDColor::RGB24(0xffffff);
  constexpr static KDColor BannerSecondBackground = KDColor::RGB24(0xe0e0e0);
  constexpr static KDColor BannerSecondBorder = KDColor::RGB24(0xfafafa);
  constexpr static KDColor BannerSecondText = KDColor::RGB24(0x000000);

  // Home
  constexpr static KDColor HomeBackground = KDColor::RGB24(0xffffff);
  constexpr static KDColor HomeCellBackground = KDColor::RGB24(0xffffff);
  constexpr static KDColor HomeCellBackgroundActive = KDColor::RGB24(0x4a4a4a);
  constexpr static KDColor HomeCellText = KDColor::RGB24(0x000000);
  constexpr static KDColor HomeCellTextActive = KDColor::RGB24(0xffffff);

  // Defaults
  constexpr static KDColor YellowDark = KDColor::RGB24(0xffb734);
  constexpr static KDColor YellowLight = KDColor::RGB24(0xffcc7b);
  constexpr static KDColor PurpleBright = KDColor::RGB24(0x656975);
  constexpr static KDColor PurpleDark = KDColor::RGB24(0x414147);
  constexpr static KDColor GreyWhite = KDColor::RGB24(0xf5f5f5);
  constexpr static KDColor GreyBright = KDColor::RGB24(0xececec);
  constexpr static KDColor GreyMiddle = KDColor::RGB24(0xd9d9d9);
  constexpr static KDColor GreyDark = KDColor::RGB24(0xa7a7a7);
  constexpr static KDColor GreyVeryDark = KDColor::RGB24(0x8c8c8c);
  constexpr static KDColor Select = KDColor::RGB24(0xd4d7e0);
  constexpr static KDColor SelectDark = KDColor::RGB24(0xb0b8d8);
  constexpr static KDColor WallScreen = KDColor::RGB24(0xf7f9fa);
  constexpr static KDColor WallScreenDark = KDColor::RGB24(0xe0e6ed);
  constexpr static KDColor SubTab = KDColor::RGB24(0xb8bbc5);
  constexpr static KDColor LowBattery = KDColor::RGB24(0xf30211);
  constexpr static KDColor Red = KDColor::RGB24(0xff000c);
  constexpr static KDColor RedLight = KDColor::RGB24(0xfe6363);
  constexpr static KDColor Magenta = KDColor::RGB24(0xff0588);
  constexpr static KDColor Turquoise = KDColor::RGB24(0x60c1ec);
  constexpr static KDColor Pink = KDColor::RGB24(0xffabb6);
  constexpr static KDColor Blue = KDColor::RGB24(0x5075f2);
  constexpr static KDColor BlueLight = KDColor::RGB24(0x718fee);
  constexpr static KDColor Orange = KDColor::RGB24(0xfe871f);
  constexpr static KDColor Green = KDColor::RGB24(0x50c102);
  constexpr static KDColor GreenLight = KDColor::RGB24(0x52db8f);
  constexpr static KDColor Brown = KDColor::RGB24(0x8d7350);
  constexpr static KDColor Purple = KDColor::RGB24(0x6e2d79);
  constexpr static KDColor DataColor[] = {Red, Blue, Green, YellowDark, Magenta, Turquoise, Pink, Orange};
  constexpr static KDColor DataColorLight[] = {RedLight, BlueLight, GreenLight, YellowLight};
};

#define ATOM_APP_USE_PALETTE
class AtomPalette {
public:
  constexpr static KDColor Unknown = KDColor::RGB24(0xeeeeee);
  constexpr static KDColor AtomText = KDColor::RGB24(0x000000);
  constexpr static KDColor AlkaliMetal = KDColor::RGB24(0xffaa00);
  constexpr static KDColor AlkaliEarthMetal = KDColor::RGB24(0xf6f200);
  constexpr static KDColor Lanthanide = KDColor::RGB24(0xffaa8b);
  constexpr static KDColor Actinide = KDColor::RGB24(0xdeaacd);
  constexpr static KDColor TransitionMetal = KDColor::RGB24(0xde999c);
  constexpr static KDColor PostTransitionMetal = KDColor::RGB24(0x9cbaac);
  constexpr static KDColor Metalloid = KDColor::RGB24(0x52ce8b);
  constexpr static KDColor Halogen = KDColor::RGB24(0x00debd);
  constexpr static KDColor ReactiveNonmetal = KDColor::RGB24(0x00ee00);
  constexpr static KDColor NobleGas = KDColor::RGB24(0x8baaff);
  constexpr static KDColor TableLines = KDColor::RGB24(0x323532);
  constexpr static KDColor AtomColor[] = {
      Unknown, AlkaliMetal, AlkaliEarthMetal, Lanthanide, Actinide, TransitionMetal,
      PostTransitionMetal, Metalloid, Halogen, ReactiveNonmetal, NobleGas
  };
};

#endif
