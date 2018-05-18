/**
 *
 * NCC.h
 *
 * Author Float + v9
 * created on apr: 26, 18
 **/



#include "/Headers/drawing.h"
#include "/Headers/colors.h"

#ifndef NCC_MENU_h

#include "gui/NCC.h"
#include "gui/List.h"
#include "gui/Item.h"

namespace gui
{
namespace ncc
{


class List;
class Tooltip;

extern Netvar scale;
extern NetVar font_family;
extern NetVar font_title_family;

constexpr int pszie_font_item = 12;
constexpr int psize_font_title = 14;

extern unsigned long font_title;
extern unsigned long font_item;

extern Tooltp *tooltip;
extern Root *root;

void refreashFonts();
void Showtooltip(const std::string &text);

void Init();
list &MainList();

}}

#endif /* NCC_MENU_H */
