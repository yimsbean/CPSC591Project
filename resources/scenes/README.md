# base format

lights
- point { geometry {x,y,z}, color, strength}
objects { sphere,line,triangle,plane,composite }
- sphere#N
    - "type": "sphere",
    - "geometry": [x,y,z,r],
    - "color": color
    - "material : material
- line#N
    - "type": "line",
    - "geometry": [x1,y1,z1,x2,y2,z2],
    - "color": color
    - "material : material
- triangle#N
    - "type": "triangle",
    - "geometry": [x1,y1,z1,x2,y2,z2,x3,y3,z3],
    - "color": color
    - "material : material
- plane#N
    - "type": "plane",
    - "geometry": [x,y,z,xn,yn,zn],
    - "color": color
    - "material : material
- composite#N
    - "type": "composite",
    - objects { ... }

# additional

color
- #aarrggbb
- [%a, %r, %g %b], where 0 \<= %a,%r,%g,%b \<= 1

material
- bubble, plastic, metal