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
  TextFieldDelegateApp(snapshot, &m_stackViewController),
  m_figuresController(&m_stackViewController),
  m_stackViewController(&m_modalViewController, &m_figuresController)
{
}

}