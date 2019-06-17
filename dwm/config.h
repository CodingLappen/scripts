/* See LICENSE file for copyright and license details. */
/* appearance */

#define OPAQUE                  0xffU
/*static unsigned int borderalpha     = OPAQUE;*/
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=8";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_red[]	   	= "#cc0000";
static const char col_green[]	  	= "#859900";
static const char col_purple[]	= "#5c3566";
static const char col_black[]		= "#000000";
static const char col_brown[] = "#B73602";
static const int baralpha = 0x00;
static const int borderalpha = OPAQUE;

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_green, col_black, col_purple },
	[SchemeSel]  = { col_brown, col_black,  col_cyan  },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE,0x11, 0xFF  },
	[SchemeSel]  = { OPAQUE, 0x11,0xFF  },
};




/* tagging */
static const char *tags[] = { "☕️", "📞️", "👀", "🍻️" , "🕶️", "M"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,    	 "gimp",    NULL,       0,            0,           -1 },
	{ "firefox",  	"firefox",	NULL,       1 << 3,       0,           0 },
	{NULL,	"discord",	NULL,		24, /*  Tags one to four  */ 		0, 		1}, /* I want to start Discord always on the second monitor */ {NULL, 	"obs", 	NULL, 	1<<4 ,	0 ,		-1}

};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */ /**/
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

void fibonacci(Monitor *mon, int s) {
	unsigned int i, n, nx, ny, nw, nh;
	Client *c;

	for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;
	
	nx = mon->wx;
	ny = 0;
	nw = mon->ww;
	nh = mon->wh;
	
	for(i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
		if((i % 2 && nh / 2 > 2 * c->bw)
		   || (!(i % 2) && nw / 2 > 2 * c->bw)) {
			if(i < n - 1) {
				if(i % 2)
					nh /= 2;
				else
					nw /= 2;
				if((i % 4) == 2 && !s)
					nx += nw;
				else if((i % 4) == 3 && !s)
					ny += nh;
			}
			if((i % 4) == 0) {
				if(s)
					ny += nh;
				else
					ny -= nh;
			}
			else if((i % 4) == 1)
				nx += nw;
			else if((i % 4) == 2)
				ny += nh;
			else if((i % 4) == 3) {
				if(s) 
					nx +=nw;
				else
					nx -= nw;
			}
			if(i == 0)
			{
				if(n != 1)
					nw = mon->ww * mon->mfact;
				ny = mon->wy;
			}
			else if(i == 1)
				nw = mon->ww - nw;
			i++;
		}
		resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);
	}
}

void dwindle(Monitor *mon) {
	fibonacci(mon, 1);
}

void spiral(Monitor *mon) {
	fibonacci(mon,0);
}

static void grid(Monitor *m);
static void grid2(Monitor *m);
static void sgrid(Monitor *m);
static const Layout layouts[] = {
	/* symbol     arrange function */

	{"HHH", grid2 },
	{ "[]",      tile, NULL },    /* first entry is default */    /* no layout function means
									 
floating behavior */
	{ "[@]", spiral , NULL},
	{"[\\\\]", dwindle, NULL },
	{"[MAX]", monocle, NULL},
	{ "", NULL, NULL} ,
	{ "|M|"  , centeredmaster, NULL},
	{ "<M>" , centeredfloatingmaster, NULL },
/*	{ "FLOAT", NULL, NULL}, */
/*l	{ "SGRID", sgrid, NULL }, */
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

void movestack(const Arg *arg) {
	Client *c = NULL, *p = NULL, *pc = NULL, *i;

	if(arg->i > 0) {
		/* find the client after selmon->sel */
		for(c = selmon->sel->next; c && (!ISVISIBLE(c) || c->isfloating); c = c->next);
		if(!c)
			for(c = selmon->clients; c && (!ISVISIBLE(c) || c->isfloating); c = c->next);

	}
	else {
		/* find the client before selmon->sel */
		for(i = selmon->clients; i != selmon->sel; i = i->next)
			if(ISVISIBLE(i) && !i->isfloating)
				c = i;
		if(!c)
			for(; i; i = i->next)
				if(ISVISIBLE(i) && !i->isfloating)
					c = i;
	}
	/* find the client before selmon->sel and c */
	for(i = selmon->clients; i && (!p || !pc); i = i->next) {
		if(i->next == selmon->sel)
			p = i;
		if(i->next == c)
			pc = i;
	}

	/* swap c and selmon->sel selmon->clients in the selmon->clients list */
	if(c && c != selmon->sel) {
		Client *temp = selmon->sel->next==c?selmon->sel:selmon->sel->next;
		selmon->sel->next = c->next==selmon->sel?c:c->next;
		c->next = temp;

		if(p && p != c)
			p->next = c;
		if(pc && pc != selmon->sel)
			pc->next = selmon->sel;

		if(selmon->sel == selmon->clients)
			selmon->clients = c;
		else if(c == selmon->clients)
			selmon->clients = selmon->sel;

		arrange(selmon);
	}
}

static void killunsel(const Arg *arg)
{
	Client *i = NULL;

	if (!selmon->sel)
		return;

	for (i = selmon->clients; i; i = i->next) {
		if (ISVISIBLE(i) && i != selmon->sel) {
			if (!sendevent(i, wmatom[WMDelete])) {
				XGrabServer(dpy);
				XSetErrorHandler(xerrordummy);
				XSetCloseDownMode(dpy, DestroyAll);
				XKillClient(dpy, i->win);
				XSync(dpy, False);
				XSetErrorHandler(xerror);
				XUngrabServer(dpy);
			}
		}
	}
}

/* custom functions declarations */
static void focusstackf(const Arg *arg);
static void setltor1(const Arg *arg);
static void toggletorall(const Arg *arg);
static void togglevorall(const Arg *arg);
static void vieworprev(const Arg *arg);
static void warptosel(const Arg *arg);
static void zoomf(const Arg *arg);
static void killunsel(const Arg *arg);

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#include "zoomswap.c"
#include "maximize.c"
/*#include "movestack.c" */
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *art_of_screenshots[] = {"take_screenshot",NULL};
static const char *art_loading_screenshots[] = {"reaction2",NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *discord[] = {"discord", NULL};
static const char *obs[] = {"obs", NULL};
static const char *firefox[] ={"firefox", NULL};
static const char *bluetooth[] = {" bluetooth", NULL};
static const char *mate_settings[] = { "mate_settings",  NULL};

/*  modkey is is the alt key usually so I just add some configs so I can open my standard programs faster*/
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ControlMask,         	XK_q,      	setlayout,      {.v = &layouts[1] } },
	{ MODKEY|ControlMask,       	XK_w,     	setlayout,      {.v = &layouts[2] } },
	{ MODKEY|ControlMask,       	XK_e,      	setlayout,      {.v = &layouts[3] } },
	{ MODKEY|ControlMask,		XK_r,		setlayout,	   {.v = &layouts[4] } },
	{ MODKEY|ControlMask, 		XK_a, 		setlayout, 	{.v = &layouts[0]}},
	{ MODKEY|ControlMask,		XK_u, 		cyclelayout, 	{.i = -1}},
	{ MODKEY|ControlMask, 		XK_i, 		cyclelayout, 	{.i = +1}},
	{ MODKEY|ControlMask,         	XK_b,  	   	togglebar,      {0} },
	{ MODKEY|ControlMask,           XK_j,      	focusstack,     {.i = +1 } },
	{ MODKEY|ControlMask,          	XK_k,      	focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask|ShiftMask,	XK_j,		movestack,      {.i = +1 }}, { MODKEY|ControlMask|ShiftMask,	XK_k,		movestack,      {.i = -1 }},	{ MODKEY|ControlMask,          	XK_n,      	incnmaster,     {.i = +1 } },
	{ MODKEY|ControlMask,       	XK_m,     	incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,          	XK_h,       	setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,          	XK_l,       	setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,            	XK_o, 	 	zoom,           {0} },
	{ MODKEY,			XK_Return,	zoom,           {0} },
	{ MODKEY,			XK_f,		view, 		{0}},
/*	{ MODKEY,                      	XK_Tab,    view,           {0} }, */
	
	{ MODKEY|ShiftMask,		XK_minus, 		togglemaximize, {0}},
	{ MODKEY|ControlMask,		XK_v, 		toggleverticalmax, {0} },
	{ MODKEY|ShiftMask,		XK_v, 		togglehorizontalmax, {0} },



	{MODKEY|ShiftMask,			XK_Tab,		rotatestack, 	{.i =-1}},	
	{MODKEY,				XK_Tab, 	rotatestack, 	{.i=+1} },
	{MODKEY|ShiftMask,			XK_Tab,		focusstack, 	{.i = 0} },	
	{MODKEY,				XK_Tab,		focusstack, 	{.i = 0} },


	{ MODKEY|ControlMask,           XK_c,      	killunsel,       {0} },
	{ MODKEY,            		XK_q,      	killclient,     {0} },	
/*	{ MODKEY|ControlMask,       		XK_q,      killunsel,     {0} },
*/
/*	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, */ /*Important LINE CHANGES the layout to different capabilities, since I don't use any other than tiling I just deleted them' */
	/*{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} }, */



	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	/*{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, */
	TAGKEYS(                        XK_6,                      0) /* Changing the setup so it won't us any good keys for the TAGS*/
	TAGKEYS(                        XK_7,                      1)
	TAGKEYS(                        XK_8,                      2)
	TAGKEYS(                        XK_9,                      3)
	{ MODKEY,			XK_comma,		focusmon,	{.i = -1 }},
	{ MODKEY,			XK_period,		focusmon,	{.i = +1 }},
	{ MODKEY|ControlMask,		XK_comma,	tagmon,		{.i = +1}},
	{ MODKEY|ControlMask,		XK_period,	tagmon,	   	{.i = -1 }},

/*   Moving from one things from one Monitor to another and also switching the goddamn Monitor*/
	{ MODKEY|ShiftMask, 		XK_period,	tagmon, 	{.i = +1}},
	{ MODKEY|ShiftMask,		XK_period,	focusmon,	{.i = +1}},
	{ MODKEY|ShiftMask, 		XK_comma,	tagmon, 	{.i = -1}},
	{ MODKEY|ShiftMask,		XK_comma,	focusmon,	{.i = -1}},
	
	{ MODKEY,               XK_p,   		spawn,         	{.v = dmenucmd } },
	{ MODKEY|ControlMask,   XK_t,		 	spawn,		{.v = termcmd } },
	{ MODKEY, 			XK_1,			spawn,	 	{.v = discord }},  /* spawns discord */
	{ MODKEY,			XK_2, 		spawn, 		{.v = firefox}}, /*I usually use firefox */
	{ MODKEY,			XK_3, 		spawn, 		{.v = obs }}, /*I obs */
	{ MODKEY|ShiftMask,     XK_q,    	  	quit,           {0} },
	{ MODKEY,			XK_o, 		spawn, 		{ .v = art_of_screenshots } },
	{ MODKEY|ControlMask,		XK_5,		spawn, 	{ .v =	mate_settings}},
	{ MODKEY|ControlMask,		XK_6, 		spawn, { .v =	bluetooth}},

{ MODKEY|ControlMask, 	XK_z,			spawn, 		{.v = art_loading_screenshots} }
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2] } },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};




void 
grid(Monitor *m){


	unsigned int i, n ,cx,cy,cw,ch,aw,ah,cols,rows;
	Client *c;


	for (n=0, c= nexttiled(m->clients); c; c=nexttiled(c->next))
		n++;

	for(rows=0 ;rows <=n/2; rows++)
		if(rows*rows >=n )
			break;
	cols =(rows && (rows -1) * rows >=n) ? rows -1 :rows;

	ch=m->wh /(rows ? rows :1);
	cw=m->ww / (cols ? cols :1) ;
	for (i=0, c= nexttiled (m->clients); c; c=nexttiled(c->next)) {
		cx = m->wx +(i/rows) *cw ;
		cy = m->wy + (i% rows) *ch;
		
		ah =((i+1) % rows == 0) ? m->wh -ch *rows  :0;
		aw= (i >= rows * (cols -1)) ? m->ww -cw *cols :0;
		resize (c,cx,cy,cw-2*c->bw *aw, ch -2 *c->bw +ah,False);
		i++;

}



}






/* custom functions */
/*
void
focusstackf(const Arg *arg) {
	Client *c = NULL, *i;

	if(!sel)
		return;
	if(lt[sellt]->arrange) {
		if (arg->i > 0) {
			for(c = sel->next; c && (!ISVISIBLE(c) || c->isfloating != sel->isfloating); c = c->next);
			if(!c)
				for(c = clients; c && (!ISVISIBLE(c) || c->isfloating == sel->isfloating); c = c->next);
		}
		else {
			for(i = clients; i != sel; i = i->next)
				if(ISVISIBLE(i) && i->isfloating == sel->isfloating)
					c = i;
			if(!c)
				for(i =  sel; i; i = i->next)
					if(ISVISIBLE(i) && i->isfloating != sel->isfloating)
						c = i;
		}
	}
	if(c) {
		focus(c);
		restack();
	}
	else
		focusstack(arg);
}

void
setltor1(const Arg *arg) {
	Arg a = {.v = &layouts[1]};

	setlayout((lt[sellt] == arg->v) ? &a : arg);
}

void
toggletorall(const Arg *arg) {
	Arg a;

	if(sel && ((arg->ui & TAGMASK) == sel->tags)) {
		a.ui = ~0;
		tag(&a);
	}
	else
		toggletag(arg);
}

void
togglevorall(const Arg *arg) {
	Arg a;

	if(sel && ((arg->ui & TAGMASK) == tagset[seltags])) {
		a.ui = ~0;
		view(&a);
	}
	else
		toggleview(arg);
}

void
vieworprev(const Arg *arg) {
	Arg a = {0};

	view(((arg->ui & TAGMASK) == tagset[seltags]) ? &a : arg);
}

void
warptosel(const Arg *arg) {
	XEvent ev;

	if(sel)
		XWarpPointer(dpy, None, sel->win, 0, 0, 0, 0, 0, 0);
	XSync(dpy, False);
	while(XCheckMaskEvent(dpy, EnterWindowMask, &ev));
}

void
zoomf(const Arg *arg) {
	if(sel && (lt[sellt]->arrange != tile || sel->isfloating)) 
		togglefloating(NULL);
	else
		zoom(NULL);
} 

*/


