apps += Geometry::App
app_headers += apps/geometry/app.h

app_geometry_src = $(addprefix apps/geometry/,\
  app.cpp \
  list/figures_controller.cpp \
  list/definition_type_controller.cpp \
  list/figure_type_controller.cpp \
  list/figure_parameters_controller.cpp \
)

apps_src += $(app_geometry_src)

app_images += apps/geometry/geometry_icon.png

i18n_files += $(call i18n_without_universal_for,geometry/base)

$(eval $(call depends_on_image,apps/geometry/app.cpp,apps/geometry/geometry_icon.png))