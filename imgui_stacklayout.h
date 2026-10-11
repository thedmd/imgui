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
