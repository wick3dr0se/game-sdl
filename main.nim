import sdl2
import ./src/[types, game]

proc main() =
  const
    FPS = 60
    frameDelay = 1000 div FPS

  var
    frameStart, frameTime: uint32
    game = new(Game)

  game.init("Game", w = 640, h = 480)

  while game.isRunning:
    frameStart = getTicks()

    game.events()
    game.update()
    game.render()

    frameTime = getTicks() - frameStart

    if frameDelay > frameTime:
      delay(frameDelay - frameTime)
  
  game.clean()

main()