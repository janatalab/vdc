// sysmenu.h copyright 2004 Cycling '74

#ifndef _EXT_SYSMENU_H_
#define _EXT_SYSMENU_H_

#ifdef MAC_VERSION
typedef MenuHandle t_sysmenu;
#endif
#ifdef WIN_VERSION
typedef void *t_sysmenu;
#endif

void sysmenu_appendseparator(t_sysmenu mh);
void sysmenu_appenditem(t_sysmenu mh, char *s);
void sysmenu_appendrawitem(t_sysmenu mh, char *s);
long sysmenu_itemcount(t_sysmenu mh);
void sysmenu_deleteallitems(t_sysmenu mh);
void sysmenu_setitem(t_sysmenu mh, short index, short way);
void sysmenu_checkitem(t_sysmenu mh, short index, short check);
void sysmenu_settext(t_sysmenu mh, short index, char *s);
t_sysmenu sysmenu_new(short id, char *title);
void sysmenu_gettitle(t_sysmenu mh, char *title);
void sysmenu_insertsubmenu(t_sysmenu mh);
void sysmenu_delete(short id);
void sysmenu_deleteitem(t_sysmenu mh, short item);
void sysmenu_dispose(t_sysmenu mh);
t_sysmenu sysmenu_menufromid(short id);
void sysmenu_gettext(t_sysmenu mh, short item, char *s);
t_sysmenu sysmenu_getnew(short id);
long sysmenu_popup(t_sysmenu mh, short top, short left, short draw);
void sysmenu_setfont(t_sysmenu mh, short *font, short *size);
short sysmenu_getid(t_sysmenu mh);
void sysmenu_deletemh(t_sysmenu mh);

#endif // _EXT_SYSMENU_H_
