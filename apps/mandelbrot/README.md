# Mandelbrot native omega numworks app

**This was only tested on omega 2.0.4 (epsilon 15).**

To add this app to your omega build:

1. Add the contents of this repository to a directory called `mandelbrot` and put this directory in the `apps` directory.
2. Add "mandelbrot" in `EPSILON_APPS` in `build/config.mak`:

   ```
   EPSILON_APPS ?= calculation graph code statistics probability solver atomic sequence regression mandelbrot settings external
   ```

   > please do not copy this line since I removed rpn from it and you might want to keep it

3. Add "mandelbrot" to `apps/home/apps_layout.csv`

   ```
   Default,calculation,rpn,graph,code,statistics,probability,solver,atomic,sequence,regression,mandelbrot,settings
   HidePython,calculation,rpn,graph,code,statistics,probability,solver,atomic,sequence,regression,mandelbrot,settings
   ```

4. Add `mandelbrot_icon.png` or another icon you made to the directory of the selected theme (example: `themes/themes/local/omega_light`).

And I think that should be all.

I also made a python script that does about the same thing as this app (way slower tho):

```py
from kandinsky import *
from ion import *
from math import *
import time

keys=[KEY_ZERO,KEY_ONE,KEY_TWO,KEY_THREE,KEY_FOUR,KEY_FIVE,KEY_SIX,KEY_SEVEN,KEY_EIGHT,KEY_NINE]
fg=color(255,255,255)

def read_d():
  for i in range(len(keys)):
    if keydown(keys[i]):
      return i
  return -1
def displayf(x):
  x=int(x*100)
  return str(x//100)+"."+str(x%100)

values=[0.0,0.10,0.25,0.4,0.55,0.7,0.85,0.95]
colors=[
  (10,2,20),
  (200,40,230), #purple
  (20,160,230), #blue
  (60,230,80), #green
  (255,230,20), #yellow
  (255,120,20), #orange
  (255,40,60), #red
  (2,0,4)
]
def color_gradient(t):
  if t<values[0]:
    return colors[0]
  if t>values[-1]:
    return colors[-1]
  for i in range(len(values)-1):
    if values[i]<=t<=values[i+1]:
      ratio=(t-values[i])/(values[i+1]-values[i])
      r1,g1,b1=colors[i]
      r2,g2,b2=colors[i+1]
      r=r1*(1-ratio)+r2*ratio
      g=g1*(1-ratio)+g2*ratio
      b=b1*(1-ratio)+b2*ratio
      return int(r),int(g),int(b)

def mandelbrot(x, y, zoom, N=20, p=1):
  for i in range(320//p+1):
    if i%4==0 and keydown(KEY_BACKSPACE):
      return
    fill_rect(i*p, 0, p, 222, fg)
    k=1
    prev=None
    for j in range(222//p+1):
      z=complex(0,0)
      c=complex(
        (((i+0.5)*p-159.9)*zoom+x)/221,
        (((j+0.5)*p-110.9)*zoom+y)/221
      )
      n=0
      while n<N and abs(z)<2:
        n+=1
        z=z*z+c
      v=int(1000*n/N)
      if j==0:
        prev=v
      if j==222//p or v!=prev:
        r,g,b=color_gradient(prev/1000)
        fill_rect(
          i*p,
          (j-k)*p,
          p,
          (k+1)*p,
          color(
            (r//16)*16,
            (g//16)*16,
            (b//16)*16
          )
        )
        k=1
        prev=v
      else:
        k+=1

x,y=0,0
nz,nz_min,nz_max=1,1,46
step,step_min,step_max=60,10,110
acc=9

u=True
while True:
  if keydown(KEY_PLUS) and nz<nz_max:
    nz+=1
    u=True
  if keydown(KEY_MINUS) and nz>nz_min:
    nz-=1
    u=True
  if keydown(KEY_HOME):
    x,y=0,0
    nz=1
    step=60
    acc=9
    u=True
  z = pow(0.6,nz-5)
  if keydown(KEY_MULTIPLICATION) and step<step_max:
    step+=10
  if keydown(KEY_DIVISION) and step>step_min:
    step-=10
  if keydown(KEY_RIGHT):
    x+=step*z
    u=True
  if keydown(KEY_UP):
    y-=step*z
    u=True
  if keydown(KEY_LEFT):
    x-=step*z
    u=True
  if keydown(KEY_DOWN):
    y+=step*z
    u=True

  nacc=read_d()
  if nacc>-1:
    acc=nacc
    u=True
  if u:
    #fill_rect(0,0,320,2,fg)
    st = time.monotonic()
    mandelbrot(
      x,y,z,
      int(120+40*nz/nz_max),
      2*acc if acc>0 else 1
    )
    draw_string(displayf(time.monotonic()-st)+"s",0,204)
    if nz==nz_max:
      draw_string("max",0,186)
    #draw_line(155, 111, 166, 111, fg)
    #draw_line(160, 106, 160, 117, fg)

  u=False
```
