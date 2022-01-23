#include "app.h"
#include "geometry_icon.h"
#include "apps/apps_container.h"
#include "apps/i18n.h"

namespace Geometry 
{

I18n::Message App::Descriptor::name() 
{
  return I18n::Message::GeometryApp;
}

I18n::Message App::Descriptor::upperName() 
{
  return I18n::Message::GeometryAppCapital;
}

const Image * App::Descriptor::icon() 
{
  return ImageStore::GeometryIcon;
}

App * App::Snapshot::unpack(Container * container) 
{
  return new (container->currentAppBuffer()) App(this);
}

App::Descriptor * App::Snapshot::descriptor()
{
  static Descriptor descriptor;
  return &descriptor;
}

App::App(Snapshot * snapshot) :
  TextFieldDelegateApp(snapshot, &m_tabViewController),
  m_figuresController(&m_stackViewController),
  m_stackViewController(&m_tabViewController, &m_figuresController),
  m_graphController(&m_graphAlternateEmptyViewController),
  m_graphAlternateEmptyViewController(&m_graphHeader, &m_graphController, &m_graphController),
  m_graphHeader(&m_graphStackViewController, &m_graphAlternateEmptyViewController, &m_graphController),
  m_graphStackViewController(&m_tabViewController, &m_graphHeader),
  m_otherViewController(&m_tabViewController),
  m_tabViewController(&m_modalViewController, snapshot, &m_stackViewController, &m_graphAlternateEmptyViewController, &m_otherViewController)
{
}

}