import sdl2
import ./[types, texture_manager]

var levelOne = [
  [0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2],
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1],
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1],
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1],
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1],
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1],
  [2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2],
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1],
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1],
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1],
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1],
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2],
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2],
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2],
  [0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2]
]

proc load(map: Map, arr: array[15, array[20, int]]) =
  for i in 0..14:
    for j in 0..19:
      map.map[i][j] = arr[i][j]
  
  echo("Map loaded!")

proc draw*(map: Map, ren: RendererPtr) =
  var kind: int

  for i in 0..14:
    for j in 0..19:
      kind = map.map[i][j]

      map.dest.x = int32(j * 32)
      map.dest.y = int32(i * 32)

      case kind
      of 0:
        map.water.draw(ren, map.src, map.dest)
      of 1:
        map.grass.draw(ren, map.src, map.dest)
      of 2:
        map.dirt.draw(ren, map.src, map.dest)
      else: break

proc init*(map: Map, game: Game) =
  map.dirt = game.renderer.load("assets/dirt.bmp")
  map.grass = game.renderer.load("assets/grass.bmp")
  map.water = game.renderer.load("assets/water.bmp")

  map.load(levelOne)

  map.src.x = 0
  map.src.y = 0
  map.src.w = 32
  map.src.h = 32

  map.dest.x = 0
  map.dest.y = 0
  map.dest.w = 32
  map.dest.h = 32