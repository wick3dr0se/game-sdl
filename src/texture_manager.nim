import sdl2

proc load*(ren: RendererPtr, tex: string): TexturePtr =
  let tmpSurface = loadBMP(tex)

  result = createTextureFromSurface(ren, tmpSurface)
  freeSurface(tmpSurface)

proc draw*(tex: TexturePtr, ren: RendererPtr, src, dest: Rect) =
  ren.copy(tex, addr(src), addr(dest))