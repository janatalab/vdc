#ifndef _EXT_TIMELINE_H_
#define _EXT_TIMELINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

// structures and functions for timeline externals

enum{
	TR_IDLE,
	TR_SELECTED,
	TR_EDITName,
	TR_SELECTEvent,
	TR_EDITEvent,
	TR_ADDNewEvent,					/* transient state */
	TR_DRAGMoveEvent,				/* transient state */
	TR_DRAGSelectEvent,				/* transient state */
	TR_STRETCHEvent,				/* transient state */
	TR_DORMANT,
	TR_PLAY
};

#define	TR_EDITModes	3			/* track edit states */
#define	TRACK_EDIT		0
#define	TRACK_ARRANGE	1
#define	TRACK_LOCKED	2

typedef struct linkthing {
	struct	tinyobject l_ob;
	void	*l_thing;
	void	*l_clock;
	void	*l_who;
	void	*l_arg;
	method	l_fn;
	struct	linkthing *l_prev;
	struct	linkthing *l_next;
	long	l_logical;				// if time is beyond this value, bang
	long	l_start;				// if time gets to be less than this value, whimper
	struct timeline *l_tl;
	short	l_flags;
} t_linkthing;

/* flags for linkthing */

#define LINK_FLAG_DIEONSTOP 1
#define LINK_FLAG_MUSTHAPPEN 2
#define LINK_FLAG_L_USEMSCLOCK 4

#define L_DIEONSTOP LINK_FLAG_DIEONSTOP
#define L_MUSTHAPPEN LINK_FLAG_MUSTHAPPEN
#define L_USEMSCLOCK LINK_FLAG_L_USEMSCLOCK

typedef	struct loopPt {
	long	l_begining;				/* begining mark */
	long	l_end;					/* end mark */
	long	l_repetionCount;		/* number of repetitions */
	struct	loopPt *l_nextLoop;		/* next loop structure */
} loopPt, *LoopPt, t_looppt;

typedef	struct tlTrack {
	t_object	tr_ob;
	t_symbol	*tr_name;			/* track name */
	long		tr_number;			/* track number */
	
	Boolean		tr_function;		/* am I a function track? */
	long		tr_sample;			/* what is my sample interval? */
	t_symbol	*tr_tag;			/* data tag */
	long		tr_dataMin,tr_dataMax;	/* for scaling of output data */
	float		tr_dataScale;		/* precomputed scaling factor */
	long		tr_outletIndex;		/* outlet index to retreive later */
	void		*tr_outlet;			/* pointer to timeline outlet */
									/* outlet is assigned by popup menu on track pane */
	
	short		tr_mode;			/* track mode */
	short		tr_saveMode;

	void 		*tr_parent;
	t_wind 		*tr_wind;			/* window inherited from parent */
	Boolean		tr_inColor;			/* are we in color? */
	Boolean		tr_preview;			/* preview mode? */
	Boolean		tr_mute;			/* are events active in play back? */
	Boolean		tr_solo;
	
	Boolean		tr_spooled;			/* has a redraw been requested? */
	Boolean		tr_active;			/* is this an active track? */
	Boolean		tr_high;			/* is it highlighted? */
	Boolean		tr_visible;
	Rect		tr_textPane;
	Rect		tr_nameBox;
	Rect		tr_numberBox;
	Rect		tr_actionIconBox;
	Rect		tr_padlockBox;
	Rect		tr_editBox;
	short		*tr_divider;
	
	long		tr_selStart;		/* start of selection */
	long		tr_selEnd;			/* end of selection */
	Rect		tr_selectionBox;	/* for selecting events */
	long		tr_selCount;		/* count of selected events */
	RgnHandle	tr_selRgn;			/* selection region for dragging */
	Point		tr_selDelta;		/* how much has region moved since last time? */
	long		tr_selBufStartTime;	/* selection buffer start time */
	
	long		tr_downTime;		/* mouse down time */
	Point		tr_selDown;			/* selection point offsets */
	Point		tr_prevDown;		/* previous mouse down point */
	Point		tr_mouseDown;		/* mouse down point */
	Boolean		tr_autoScrolling;	/* am I auto scrolling? */
	Boolean		tr_nameInited;		/* has name TERec been initialized */
	short		tr_vol;				/* location of action class */
	t_symbol	*tr_actionName;		/* name of action class */
	method		tr_actionIcon;		/* action class icon */
	short		tr_actionType;		/* action type */
	void		*tr_messageList;	/* list of messages track deals with */
	t_object	*tr_action;			/* the action class instance */
	
	short		tr_editMode;		/* current edit mode */
	Boolean		tr_editable;		/* edits allowed? */

	short		tr_prevOffset;
	short		tr_vOffset;			/* track vertical offset */
	short		tr_height;			/* track height */
	short		tr_expandedHeight;	/* track height when expanded, if collapsed */

	struct		event *tr_nextEvent;	/* the next event to play */
	struct		event *tr_event;		/* events of some sort */
	struct		event *tr_targetEvent;	/* event that receives keys */

	long		*tr_currentTime;
	long		tr_oldPix;
	Boolean		tr_showTimeBar;		/* turn on and off time bar display */
	long		*tr_timeOffset;
	long		*tr_displayTime;
	
	t_looppt	*tr_loops;			/* loop points for track */
	t_looppt	*tr_currentLoop;		/* which loop are we in the middle of? */
	
	short		tr_updflags;	
	Boolean		tr_invalid;
	long		tr_updStart;		/* update region */
	long		tr_updEnd;
	Rect		tr_updRect;
	struct event *tr_updateList;	/* list of events to update */

	t_linkthing *tr_linkThing;	/* end event stuff */

	TEHandle	tr_teh;				/* text edit handle */
	
	void		*tr_saveThing;
	struct		tlTrack	*tr_upd;	/* timeline update list */
	struct		tlTrack	*tr_next;	/* pointer to next track (if linked list) */
	
	void		*tr_extraThing;		/* reserved for later use */
} tlTrack, *TLTrack, t_tltrack;

// used by smallbox

typedef struct objsize {
	Rect o_rect;
#ifdef CAREFUL
	long b_magic;					/* magic number					*/
#endif
} t_objsize;

// the smallbox is used by a timeline event

typedef struct smallbox
{
	union bx {
		t_object b_ob;
		t_objsize b_os;
	} b_header;
	short b_inlet:1;			/* this box is an inlet */
	short b_outlet:1;			/* this box is an outlet */
	short b_textdirty:1;		/* text has been changed */
	short b_drawfirstin:1;	/* draw inlet for the real object */
	short b_outline:1;		/* draw the box */
	short b_drawn:1;			/* has been drawn */
	short b_spooled:1;		/* is spooled for drawing */
	short b_growy:1;			/* can grow in y direction */
	unsigned short b_inset:3;	/* top-and-bottom inset for text */
	short b_selected:1;		/* on if selected */
	unsigned short b_color:4;	/* index into palette (default 0) */
	unsigned short b_fsize;	/* font size */
	short b_fontindex;		/* font index (get from window) */
	short b_growboth:1;		/* can grow independently in both directions */
	short b_ignorelockclick:1; /* ignore clicks if patcher is locked (be "transparent") */
	short b_hidden:1;			/* hide box on lock */
	short b_nogrow:1;			/* don't grow at all */
	short b_hilited:1;		/* hilited, typeable object */
	short b_pending:1;		/* typing is pending */
	short b_hiliteable:1;		/* hiliteable object */
	short b_savehilite:1;		/* save hilite state when window is not active */
	short b_saveselect:1;		/* save select state when window is not active */
	short b_undo:2;			/* undo bit */
	short	b_bogus:1;			/* box's bogus bit--patcher creates its inlets/outlets on connect */
	short b_checkinvis:1;		/* check when invizzing */
	short b_visible:1;		/* for vnewobj patchers, is box visible? */
	short b_drawinlast:1;		/* used by vnewobj, inlet, outlet to draw inlets/outlets */
	short b_hasauxdata:1;			/* has auxiliary box data */
	short b_remote:1;			/* remote box */
	short b_ignoreclick:1;	/* user setting for ignoring a lock click */
	short b_background:1;	// part of background
	short b_transparent:1;	// transparent
	short b_unused: 5;		/* extra space for future bits */
	short b_temp;
} t_smallbox;


// timeline event

typedef struct event {
	t_object e_obj;
	struct smallbox *e_box;	/* Pointer to Smallbox (or Box) that holds the rectangle */
	struct event *e_upd;	/* Update list link (used internally for spooling events) */
	Rect *e_rect;			/* Pointer to rectangle within e_box */
	struct event *e_next;	/* Linked list of Events in the Timeline Track */
	struct tlTrack *e_track;	/* Pointer to owning Track */
	void *e_assoc;	/* List of associated objects (internal use) */
	t_object *e_o;			/* Pointer to object in unitary receiver case */
	t_symbol *e_label;		/* Descriptive text for Event locate pop-up menu */
	long e_start;			/* Event start time (in milliseconds) */
	long e_duration;		/* Event duration (in milliseconds) */
	t_symbol *e_dataType;		/* Data type of the message */
	t_symbol *e_message;		/* Message selector that is sent */
	t_symbol *e_editor;		/* Editor name */
	void *e_edit;	/* Internal information about the Editor */
	void *e_saveThing;		/* Internal temporary variable */
	void *e_thing;			/* Internal unused variable */
	short e_wantOffset;		/* If the track containing the editor has been collapsed */ 
	Boolean e_active;		/* Currently unused */
	Boolean e_preview;		/* Should be non-zero, not currently used */
	Boolean e_constantWidth;	/* If this flag is non-zero, the Events duration is */
	Boolean e_editable;		/* Flag is non-zero if clicking on the Event modifies its */
	Boolean e_smallbox;		/* Flag is non-zero if the Event uses the Smallbox data */
} event, *Event, t_event;

#ifndef F_GROWY
#define F_GROWY			2		/* can grow in y direction by dragging */
#define F_GROWBOTH		32		/* can grow independently in both x and y */
#endif
#define F_CONSTANTWIDTH 16		/* constant width */



void message_register(t_symbol *name, t_symbol *superClass,
	t_object *theObject, t_symbol *objectName, t_tltrack *x);
	
void editor_register(t_symbol *dataType, t_symbol *name, method newFN,
	method menuFN, method updateFN);
void event_new(t_event *e, t_tltrack *track, t_symbol *dataType, 
	t_symbol *message, t_symbol *editor, t_symbol *label,
	long start, long duration, long flags, t_box *box);
void event_box(t_event *e, short top, short bottom);
void message_patcherRegister(t_symbol *name, t_symbol *superClass,
	t_object *theObject, t_symbol *objectName, t_patcher *p);
void message_unregister(t_symbol *name, t_symbol *superClass,
	t_object *theObject, t_symbol *objectName, t_tltrack *x);
void message_patcherUnregister(t_symbol *name, t_symbol *superClass,
	struct object *theObject, t_symbol *objectName, t_patcher *p);
void event_spool(t_event *e);
void event_schedule(t_event *e, method fn, t_object *dest, void *arg,
	long delay, long flags);
void track_clipBegin(t_tltrack *x, Rect *r);
void track_clipEnd(t_tltrack *x);
short event_offsetRect(t_event *e);
void track_eraseDragTime(t_tltrack *x);
void track_drawDragParam(t_tltrack *x, char *buf);
void track_drawDragTime(t_tltrack *x, long top, long bottom);
void track_drawTime(t_tltrack *x, long time);
long track_pixToMS(t_tltrack *x, short pix);
short track_MSToPix(t_tltrack *x, long time);
long track_posToMS(t_tltrack *x, short pos);
short track_MSToPos(t_tltrack *x, long time);
GrafPtr	track_setport(t_tltrack *x);
void *event_clock(t_event *e);
t_patcher *event_avoidRect(t_event *e, short id);
void event_save(t_event *e, t_atom *a);
void event_process(void *e, t_wind *w);
void event_run(void);


#if PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif // _EXT_TIMELINE_H_
