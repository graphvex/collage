# collage — Repo-Local Living Preferences

## Constitution Link

gist.md (`../../../../metadata/gists/preferences/gist.md`) is the compressed law list; all universal laws bind this repository. Read one on demand: `./tools/prefs law "<title>"`. Universal laws are inherited, never restated.

## Tier and Ownership

**Tier:** `core` — the rect-first, forward-rendered compositor. Repo `graphvex/collage`, checked out at `graphvex/compositor/`; the public class prefix stays `Compositor*`.
**Owns:** `lang/` graphics vocabulary, `paint/`, `text/`, the element tree, sources, groups, filters, composition, damage, scheduling, presentation.
**Does not own:** GPU objects or drivers (graphvex), scenes (meld), widgets/input/layout policy (darling).
Includes point down only; never meld, darling, hotcwap or driver headers. Scene images arrive as graphvex `Image`s.

## Directory Headers

* One `.h` per directory, named after the directory; the repo root header is `collage.h`.

## Exclusive Laws

| Law Title | Scope | Enforcement |
| **Rect-First Law** | whole repo | Mandatory for `collage` |
| **Graphics Language & Board Compositor Law** | `lang/`, `compose/` | Mandatory for `collage` |
| **UI Graphics Source Placement Law** | `source/`, `element/` | Mandatory for `collage` |
| **Absolute Rendering & Event Bound Law** | `element/`, `compose/` | Mandatory for `collage` |
| **Ordered Filter & Scatter Composition Law** | `filter/`, `compose/` | Mandatory for `collage` |
| **Independent Scene Cadence Law** | `source/scene_source`, `schedule/` | Mandatory for `collage` (consumer) |

### Rect-First Law

* Everything is a rect: widgets, glyph runs, images, vector shapes, scene images.
* Planning, culling, damage and allocation work on integer native-pixel rects. Rounded corners, masks and SDF refine inside a rect and never replace it as the unit of scheduling.
* collage is forward-rendered: no retained scene, no G-buffer; the rect list is rebuilt, sorted in painter order, batched and drawn as instanced quads each frame. An offscreen group exists only when a filter or mask needs isolation.
* Shapes are never tessellated: analytic coverage (rect, rounded rect, circle, ellipse, strokes) or an SDF atlas lookup (glyphs, complex paths).

### Graphics Language & Board Compositor Law

* collage owns the graphics vocabulary, element tree and widget compositor: placement, isolated groups, images, filters, masks, render dependencies, ordered composition.
* Darling is the widget interface; it submits collage records, never a competing filter/render compositor.
* `lang/` owns `filter`, `filter_stack`, `compositor`, `graphics_component`, `element_node`, `transform`, `size`.
* Naming marks the layer: `GraphicsComponent`, never `Component`; `ElementNode`, never darling's container.
* `AUTO` is a sentinel with per-class equivalence; `lang/size.h` owns `SIZE_AUTO`.
* `Property` is the placement bound every element carries (x/y/w/h + radius/background/border/shadow/blur).

### UI Graphics Source Placement Law

* Panel/label graphics live under `source/<kind>/`; public vocabulary under `lang/`.
* Editing, focus, layout policy and application behavior remain Darling's; collage borrows lifetime, lib and vexspoke contracts only.

### Absolute Rendering & Event Bound Law

* Each element has two public bounds — event bound (resolved layout/hit rect; filters never alter it) and absolute bound (conservative world-space AABB of paint after effects, child clips and ordered filters).
* Unknown support requires conservative full-group fallback or explicit rejection, never an invented margin.
* Targets keep their world origin; expanded allocations translate coordinates only, never stretching results back into event rects.
* Movement, removal, filters and descendant changes invalidate old and new absolute support; backdrop reads add rendering dependencies.

### Ordered Filter & Scatter Composition Law

* Ordered filter stacks run over isolated graphics groups.
* Backdrop filters consume the composed painter-order prefix (excluding self and later siblings); foreground filters consume content/children; element filters consume the assembled element.
* Filter token = `ID16 | payload48`; `filter/filter_type.h` owns the operation IDs.
* Stacks execute left to right; no silent reordering.
* Composition and blur use linear-light premultiplied RGBA; weighted contributions add into isolated f32 accumulation, then resolve into one source-over group composition.
* A filtered backdrop replaces its masked prefix region; never composite the original backdrop twice.

### Independent Scene Cadence Law

* Widget composition and scene-image production run on independent logical schedules; separate OS threads are optional.
* `SceneSource` takes the newest completed scene image and never forces a scene tick or waits for one.
* Images and parameter records stay alive until consumers finish, resize/close included.
* Widget changes and completed scene versions invalidate composition independently.

## Repo-Local Extensions

* None — no managed exceptions to universal laws.

## Readiness Cross-Reference

* Feature readiness: collage readiness gist.
* Open blockers: ecosystem blockers gist.
* Proof lawbook: `tests/test-preferences.md` — `./tools/prefs test "<title>"`.
* Evidence ledger: `metadata/gists/test-checklist.md` — `python3 tools/test_checklist.py check`.
