apps += Mandelbrot::App
app_headers += apps/mandelbrot/app.h

app_mandelbrot_src = $(addprefix apps/mandelbrot/,\
  app.cpp \
  mandelbrot_controller.cpp \
  mandelbrot_view.cpp \
)

apps_src += $(app_mandelbrot_src)

app_images += apps/mandelbrot/mandelbrot_icon.png

i18n_files += $(call i18n_without_universal_for,mandelbrot/base)

$(eval $(call depends_on_image,apps/mandelbrot/app.cpp,apps/mandelbrot/mandelbrot_icon.png))

### The Makefile, is the file who allows you to compile successfully your app.
### If you add files or rename some files, don't forget to change the Makefile!
