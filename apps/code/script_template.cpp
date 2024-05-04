#include "script_template.h"

namespace Code
{

  constexpr ScriptTemplate emptyScriptTemplate(".py", "\x01"
                                                      R"(from math import *
)");

  constexpr ScriptTemplate squaresScriptTemplate("squares.py", "\x01"
                                                               R"(from math import *
from turtle import *
def squares(angle=0.5):
  reset()
  L=330
  speed(10)
  penup()
  goto(-L/2,-L/2)
  pendown()
  for i in range(660):
    forward(L)
    left(90+angle)
    L=L-L*sin(angle*pi/180)
  hideturtle())");

  constexpr ScriptTemplate mandelbrotScriptTemplate("mandelbrot.py", "\x01"
                                                                     R"(from kandinsky import *
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

  u=False)");

  constexpr ScriptTemplate polynomialScriptTemplate("polynomial.py", "\x01"
                                                                     R"(from math import *
# roots(a,b,c) computes the solutions of the equation a*x**2+b*x+c=0
def roots(a,b,c):
  delta = b*b-4*a*c
  if delta == 0:
    return -b/(2*a)
  elif delta > 0:
    x_1 = (-b-sqrt(delta))/(2*a)
    x_2 = (-b+sqrt(delta))/(2*a)
    return x_1, x_2
  else:
    return None)");

  constexpr ScriptTemplate parabolaScriptTemplate("parabola.py", "\x01"
                                                                 R"(from matplotlib.pyplot import *
from math import *

g=9.81

def x(t,v_0,alpha):
  return v_0*cos(alpha)*t
def y(t,v_0,alpha,h_0):
  return -0.5*g*t**2+v_0*sin(alpha)*t+h_0

def vx(v_0,alpha):
  return v_0*cos(alpha)
def vy(t,v_0,alpha):
  return -g*t+v_0*sin(alpha)

def t_max(v_0,alpha,h_0):
  return (v_0*sin(alpha)+sqrt((v_0**2)*(sin(alpha)**2)+2*g*h_0))/g

def simulation(v_0=15,alpha=pi/4,h_0=2):
  tMax=t_max(v_0,alpha,h_0)
  accuracy=1/10**(floor(log10(tMax))-1)
  T_MAX=floor(tMax*accuracy)+1
  X=[x(t/accuracy,v_0,alpha) for t in range(T_MAX)]
  Y=[y(t/accuracy,v_0,alpha,h_0) for t in range(T_MAX)]
  VX=[vx(v_0,alpha) for t in range(T_MAX)]
  VY=[vy(t/accuracy,v_0,alpha) for t in range(T_MAX)]
  for i in range(T_MAX):
    arrow(X[i],Y[i],VX[i]/accuracy,VY[i]/accuracy)
  grid()
  show())");

  const ScriptTemplate *ScriptTemplate::Empty()
  {
    return &emptyScriptTemplate;
  }

  const ScriptTemplate *ScriptTemplate::Squares()
  {
    return &squaresScriptTemplate;
  }

  const ScriptTemplate *ScriptTemplate::Mandelbrot()
  {
    return &mandelbrotScriptTemplate;
  }

  const ScriptTemplate *ScriptTemplate::Polynomial()
  {
    return &polynomialScriptTemplate;
  }

  const ScriptTemplate *ScriptTemplate::Parabola()
  {
    return &parabolaScriptTemplate;
  }

}
