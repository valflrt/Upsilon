apps += Geometry::App
app_headers += apps/geometry/app.h

app_geometry_src = $(addprefix apps/geometry/,\
  app.cpp \
  figures_controller.cpp \
  definition_type_controller.cpp \
  figure_type_controller.cpp \
)

apps_src += $(app_geometry_src)

app_images += apps/geometry/geometry_icon.png

i18n_files += $(call i18n_without_universal_for,geometry/base)

$(eval $(call depends_on_image,apps/geometry/app.cpp,apps/geometry/geometry_icon.png))