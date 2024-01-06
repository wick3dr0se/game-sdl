import sdl2

type
  Game* = ref object
    cnt*: cint
    isRunning*: bool
    window*: WindowPtr
    renderer*: RendererPtr
  Entity* = ref object
    x*, y*: cint
    texture*: TexturePtr
    renderer*: RendererPtr
    srcRect*, destRect*: Rect
  Map* = ref object
    src*, dest*: Rect
    dirt*, grass*, water*: TexturePtr
    map*: array[20, array[25, int]]