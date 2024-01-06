import sdl2
import ./[types, texture_manager]

proc entity*(entity: Entity, ren: RendererPtr, texsheet: string, x, y: cint) =
  entity.texture = ren.load(texsheet)

  entity.x = x
  entity.y = y

proc update*(entity: Entity) =
  entity.x.inc()
  entity.y.inc()

  entity.srcRect.x = 0
  entity.srcRect.y = 0
  entity.srcRect.w = 32
  entity.srcRect.h = 32

  entity.destRect.x = entity.x
  entity.destRect.y = entity.y
  entity.destRect.w = entity.srcRect.w
  entity.destRect.h = entity.srcRect.h

proc render*(entity: Entity, ren: RendererPtr) =
  ren.copy(entity.texture, addr(entity.srcRect), addr(entity.destRect))