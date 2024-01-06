import sdl2
import ./[types, entity, map]

var
  player = new(Entity)
  enemy = new(Entity)
  level = new(Map)

proc init*(game: Game, title: cstring, x = SDL_WINDOWPOS_CENTERED, y = SDL_WINDOWPOS_CENTERED; w, h: cint, flags = SDL_WINDOW_SHOWN) =
  if sdl2.init(INIT_EVERYTHING):
    echo("Subsystems initialized!")

    game.window = createWindow(title, x, y, w, h, flags)
    if game.window.isNil():
      echo($getError())
    else:
      echo("Window created!")

    game.renderer  = createRenderer(game.window, -1, 0)
    if game.renderer.isNil():
      echo($getError())
    else:
      game.renderer.setDrawColor(150, 255, 155, 255)
      echo("Renderer created!")
    
    player.entity(game.renderer, "assets/player.bmp", 0, 0)
    enemy.entity(game.renderer, "assets/enemy.bmp", 32, 32)
    level.init(game)
    
    if player.isNil():
      echo($getError())
    else:
      echo("Player loaded!")

    game.isRunning = true
  else:
    echo($getError())
    game.isRunning = false

proc events*(game: Game) =
  var evt = sdl2.defaultEvent

  while pollEvent(evt):
    case evt.kind
    of QuitEvent:
      game.isRunning = false
      break
    else:
      break

proc update*(game: Game) =
  player.update()
  enemy.update()

proc render*(game: Game) =
  game.renderer.clear()
  level.draw(game.renderer)
  player.render(game.renderer)
  enemy.render(game.renderer)
  game.renderer.present

proc clean*(game: Game) =
  game.window.destroy()
  game.renderer.destroy()
  sdl2.quit()
  echo("Game cleaned!")