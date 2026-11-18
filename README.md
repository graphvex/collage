# collage — the rect-first compositor

> Nothing is implemented yet. Work order: `_notes/ideas/collage/MANIFEST.md`. Laws: [collage-preferences.md](collage-preferences.md). Checked out at `graphvex/compositor/`; the code keeps the `Compositor*` prefix.

collage composes everything as rectangles — widgets, glyph runs, images, vector shapes and meld scenes — into the window's single seam canvas through graphvex's `Swapchain`.

```text
graphvex (api) → collage | meld → darling (UI, incl. the 3D panel)
```

## Deliberate seams

1. **Rect-first and forward-rendered.** No retained scene; the rect list is rebuilt and drawn each frame. Rounded shapes and masks refine inside rects.
2. **No tessellation.** Shapes are analytic coverage or an SDF atlas lookup.
3. **collage never includes meld.** A scene arrives as a graphvex `Image` + version; darling wires meld's newest image in as a `SceneSource`.
4. **Composition is linear-light premultiplied RGBA.** Display encoding happens only at present; BGRA stays inside the presentation adapter.
5. **Shaders are GLSL | MSL | WGSL → SPIR-V.**
6. **Deliberate gaps** carried from `../api_old/COMPOSITOR.md` stay open until each is closed with evidence.
