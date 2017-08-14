/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 8;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Sans Pro:size=13:antialias=true:autohint=slight" };
static const char dmenufont[]       = "Source Sans Pro:size=13";
static const char col_base00[]      = "#282936";
static const char col_base01[]      = "#3a3c4e";
static const char col_base05[]      = "#e9e9f4";
static const char *colors[][3]      = {
	/*               fg         bg          border   */
	[SchemeNorm] = { col_base05, col_base00, col_base01 },
	[SchemeSel]  = { col_base05, col_base01, col_base01 },
};

/* tagging */
static const char *tags[] = { "Ⅰ", "Ⅱ", "Ⅲ", "Ⅳ", "Ⅴ" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance    title	     tags mask     isfloating    monitor */
	{  NULL,       NULL,       NULL,	     0,            0,            -1 },
	{  "Nitrogen", NULL,       NULL,	     0,            1,            -1 },
	{  NULL,       NULL,       "streamlink",     0,            1,            -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_base00, "-nf", col_base05, "-sb", col_base01, "-sf", col_base05, NULL };
static const char *termcmd[]  = { "st", NULL };
/* Backlight */
static const char *uplight[] = { "xbacklight", "-inc", "5", "-time", "0", NULL };
static const char *dwlight[] = { "xbacklight", "-dec", "5", "-time", "0", NULL };
/* Volume */
static const char *upvol [] = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *dwvol [] = { "pactl", "set-sink-volume", "0", "-5%", NULL };
/* Player */
static const char *prev[]  = { "playerctl", "previous",   NULL };
static const char *stop[]  = { "playerctl", "play-pause", NULL };
static const char *next[]  = { "playerctl", "next",       NULL };
/* slock */
static const char *slock[]  = { "slock", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	/* Backlight */
	{ MODKEY,			XK_Right,  spawn,          {.v = uplight} },
	{ MODKEY,			XK_Left,   spawn,          {.v = dwlight} },
	/* Volume */
	{ MODKEY,			XK_Up,     spawn,          {.v = upvol} },
	{ MODKEY,			XK_Down,   spawn,          {.v = dwvol} },
	/* Player */
	{ MODKEY|ShiftMask,		XK_Right,  spawn,          {.v = next}  },
	{ MODKEY|ShiftMask,		XK_Down,   spawn,          {.v = stop}  },
	{ MODKEY|ShiftMask,		XK_Left,   spawn,          {.v = prev}  },
	/* slock */
	{ MODKEY|ShiftMask,		XK_l,   spawn,             {.v = slock}  },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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
