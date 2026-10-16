// dear imgui, v1.86 WIP
// (stack layout headers)

/*

Index of this file:
// [SECTION] Stack Layout API

*/

/*

CHANGELOG
=========

-----------------------------------------------------------------------
 In Progress (Stack Layout v2.2, Dear ImGui 1.93.0 WIP)
-----------------------------------------------------------------------

Breaking Changes:

- Layout: items flow with Dear ImGui's own layout type (window->DC.LayoutType), as in menu bars,
  and layouts measure their items like groups. ItemSize() and ItemAdd() no longer call into
  stack layouts. Inside horizontal layouts, Separator() draws a vertical separator,
  MenuItem()/BeginMenu() render as in a menu bar, and NewLine() starts a new row.

Other Changes:

- Layout: fixed SameLine() inside horizontal layouts placing the next item over the previous
  one. Widgets calling SameLine() (DragFloat3(), InputInt(), ColorEdit3(), ...) collapsed.
- Layout: fixed BeginVertical() after SameLine() moving its contents down by the height of the
  previous line, where the layout clip rect hid them.
- Layout: fixed ImGuiListClipper inside BeginVertical() collapsing the scroll range of the
  window: items are measured by how far they move the cursor, as in groups.
- Layout: fixed tables without scrolling inside horizontal layouts laying out their cells
  horizontally. This needs the fix to BeginTable() submitted to Dear ImGui with this release.
- Layout: fixed a crash ending a layout begun while its parent was suspended, and on nested
  SuspendLayout() calls.
- Clipping: layouts no longer split draw commands into channels or clamp them to their measured
  size. Fixed the nav cursor, outlines and other decorations drawn around items at the edge of a
  layout being cut, draw calls no longer batching across layouts, and content moved by the root
  layout being clipped for one frame. Fixed-size axes still clip contents that overflow them.
- Nested layouts: fixed an automatic parent never shrinking when a nested layout with springs is
  wrapped in BeginGroup()/EndGroup(). Inside such a group, the item rect of the nested layout
  (GetItemRectMin()/GetItemRectMax() after EndHorizontal()/EndVertical()) is its own size rather
  than the size it grows to in the parent.
- Layout: items outside of stack layouts no longer cost a lookup of the layout state.
- Context: layout state is kept per context and per window, instead of in a process-global map.
  Fixed crashes and hooks piling up with one context per thread (thread-local GImGui), and
  modules sharing a context (plugin DLLs, hot reload) each keeping their own layout state.
- Context: the module that submits the first layout of a context registers its hooks. Keep it
  loaded as long as the context lives.
- Context: fixed layout state for IDs from changing data never being freed. Layouts unused for
  io.ConfigMemoryCompactTimer are freed, as windows and tables are, and so are all layouts of a
  window whose memory is compacted.
- Context: fixed an allocation outliving DestroyContext().
- Error Handling: layouts left open at the end of the frame while error recovery is disabled are
  reported and discarded at the next frame.
- Error Handling: fixed the same layout ID used twice in a frame hanging builds without asserts.
  It is reported, and each further use gets a layout state of its own, as table instances do.
- Error Handling: fixed ErrorRecoveryTryToRecoverState() closing layouts begun before
  ErrorRecoveryStoreState(). SuspendLayout() pushes the current ID again, which leaves item IDs
  unchanged and orders suspensions for recovery.
- Error Handling: misuse is reported and recovered instead of asserting, then crashing:
  Spring() outside of a layout, EndHorizontal()/EndVertical() without a layout, while suspended
  or on the other type of layout, and ResumeLayout() without SuspendLayout().
- Error Handling: unbalanced PushID()/PopID() inside a layout or a suspension is reported, and
  the ID stack is restored when the layout ends or resumes.
- Internals: moved internal types and functions to namespace ImGuiStackLayout. They were in
  the global and ImGui namespaces, where same-named user code or future Dear ImGui code clash.

-----------------------------------------------------------------------
 2026/10/11 (Stack Layout v2.1, Dear ImGui 1.93.0 WIP)
-----------------------------------------------------------------------

Breaking Changes:

- IDs: BeginHorizontal()/BeginVertical() scope their contents like PushID() with the same
  identifier, as BeginTable() and TreeNode() do. IDs of items submitted inside stack layouts
  change: settings saved under them (e.g. tables in imgui.ini) reset once.

Other Changes:

- Nested layouts: fixed content submitted after a nested layout not being displayed, and
  content drawn by the parent before a nested layout ending up over it. Each layout now
  clips and merges its draw commands when it ends. (thedmd/imgui#10, ocornut/imgui#846) [@pthom]
- Nested layouts: fixed an enclosing BeginGroup()/EndGroup() growing but never shrinking:
  an auto-sized nested layout grows to its parent's size only when it has springs.
  (thedmd/imgui#9) [@pthom]
- Horizontal layouts: fixed vertical drift of items with a fractional height.
  (thedmd/imgui#9, ocornut/imgui#9333) [@pthom]
- Style: fixed ImGuiStyleVar_LayoutAlign not matching its GStyleVarsInfo[] entry, which made
  PushStyleVar() modify the wrong field, or assert, for it and for every style variable
  declared after it. (thedmd/imgui#7) [@firesgc]
- Layout: fixed SameLine() in menu bars and custom combo previews moving the next item one row
  down and over the previous one. Outside of stack layouts, ItemSize() behaves as upstream.
- Springs, alignment: fixed corrections made within the frame moving unrelated vertices in
  windows with more than 64K vertices.
- Error Handling: fixed asserting on a layout left open at the end of the frame (e.g. in a
  window missing End()) before error recovery could close it.
- Error Handling: fixed a crash recovering from SuspendLayout() without ResumeLayout().
- Misc: fixed unused parameter/variable warnings. (thedmd/imgui#9) [@pthom]


ACKNOWLEDGMENTS
===============

Thanks to everyone who reported issues and contributed fixes:
- @pthom: nested layout, fractional height and warning fixes (thedmd/imgui#9, thedmd/imgui#10),
  report of ocornut/imgui#9333.
- @firesgc: ImGuiStyleVar_LayoutAlign fix (thedmd/imgui#7).
- @wkster: report of content missing after a nested layout (ocornut/imgui#846).
- @gnif: missing intptr_t include fix (thedmd/imgui#4).

*/

#pragma once

#include "imgui.h"

#ifndef IMGUI_DISABLE

//-----------------------------------------------------------------------------
// [SECTION] Stack Layout API
//-----------------------------------------------------------------------------

namespace ImGui
{
    IMGUI_API void BeginHorizontal(const char* str_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    IMGUI_API void BeginHorizontal(const void* ptr_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    IMGUI_API void BeginHorizontal(int id, const ImVec2& size = ImVec2(0, 0), float align = -1);
    IMGUI_API void EndHorizontal();
    IMGUI_API void BeginVertical(const char* str_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    IMGUI_API void BeginVertical(const void* ptr_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    IMGUI_API void BeginVertical(int id, const ImVec2& size = ImVec2(0, 0), float align = -1);
    IMGUI_API void EndVertical();
    IMGUI_API void Spring(float weight = 1.0f, float spacing = -1.0f);
    IMGUI_API void SuspendLayout();
    IMGUI_API void ResumeLayout();

} // namespace ImGui


#endif // #ifndef IMGUI_DISABLE
