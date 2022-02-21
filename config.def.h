/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 23;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 23;       /* vert inner gap between windows */
static const unsigned int gappoh    = 23;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 23;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int systraypinning = 2;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */
static const char *upvol[]               = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%",     NULL };
static const char *downvol[]             = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%",     NULL };
static const char *mutevol[]             = { "/usr/bin/pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle",  NULL };
// static const char *fonts[]               = { "robotomono:size=13",  "fontawesome:size=24" };

static const char *fonts[]          = { "JetBrainsMono Nerd Font:style:medium:size=13",
                                        "JoyPixels:pixelsize=24:antialias=true:autohint=true",
                                      };
// static const char dmenufont[]       = "JetBrainsMono Nerd Font:style:medium:size=13";
// static const char *fonts[]          = { "Ubuntu:size=13",
//                                         "JoyPixels:pixelsize=24:antialias=true:autohint=true",
                                      // };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:style:medium:size=14";
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#000000";
static const char col_gray3[]       = "#c5c5c5";
static const char col_gray4[]       = "#ffffff";
// static const char col_cyan[]        = "#005577";
static const char col_cyan[]        = "#9f9f9f";
static const unsigned int baralpha = 0x70;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* staticstatus */
static const int statmonval = 0;

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
	// { "[@]",      spiral },
	// { "[\\]",     dwindle },
	// { "D[]",      deck },
	// { "TTT",      bstack },
	// { "===",      bstackhoriz },
	// { "HHH",      grid },
	// { "###",      nrowgrid },
	// { "---",      horizgrid },
	// { ":::",      gaplessgrid },
	// { "|M|",      centeredmaster },
	// { ">M>",      centeredfloatingmaster },
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
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "kitty", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,            {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,            {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,        {0} },
	{ MODKEY,                       XK_j,      focusstack,       {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,             {0} },
	{ MODKEY,                       XK_Down,   setmfact,         {.f = -0.05} },
	{ MODKEY,                       XK_Up,     setmfact,         {.f = +0.05} },
	{ MODKEY,                       XK_Left,   setmfact,         {.f = -0.05} },
	{ MODKEY,                       XK_Right,  setmfact,         {.f = +0.05} },
	{ MODKEY,                       XK_g,      togglegaps,       {0} },
	{ MODKEY,                       XK_l,      shiftviewclients, { .i = +1 } },
	{ MODKEY,                       XK_h,      shiftviewclients, { .i = -1 } },
	{ MODKEY,                       XK_semicolon,    view,             {0} },
	{ MODKEY,                       XK_q,      killclient,       {0} },
	{ MODKEY,                       XK_t,      setlayout,        {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,        {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating,   {0} },
	// { MODKEY|ShiftMask,             XK_f,      setlayout,        {.v = &layouts[2]} },
	{ MODKEY,			                  XK_p,           spawn,		      SHCMD("restream") },
	{ MODKEY,                       XK_s,           spawn,          SHCMD("screenkey -s small --scr 2 -p fixed -g 400x100+4700+25 --opacity .6 --font-color white") },
	{ MODKEY|ShiftMask,             XK_s,           spawn,          SHCMD("killall screenkey") },
	{ MODKEY,			                  XK_e,           spawn,		      SHCMD("nautilus") },
	{ MODKEY,			                  XK_w,           spawn,		      SHCMD("$BROWSER") },
	{ MODKEY,			                  XK_r,           spawn,		      SHCMD("$TERMINAL -e ranger") },
	{ MODKEY,			                  XK_y,           spawn,		      SHCMD("flameshot gui -p ~/Pictures/screenshots") },
	{ MODKEY|ShiftMask,			        XK_y,           spawn,		      SHCMD("flameshot full -p ~/Pictures/screenshots") },
	{ MODKEY|ShiftMask,			        XK_v,           spawn,		      SHCMD("mpv --profile=low-latency /dev/video0") },
	{ MODKEY,                       XK_Tab,         spawn,          SHCMD("skippy-xd") },
	{ MODKEY,                       XK_Escape,      spawn,          SHCMD("sudo systemctl suspend") },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
	{ 0,                            XF86XK_AudioMute, spawn, {.v = mutevol } },
	{ MODKEY,                       XK_minus, spawn, {.v = downvol } },
	{ MODKEY,                       XK_equal, spawn, {.v = upvol   } },
	{ MODKEY,                       XK_0, spawn, {.v = mutevol } },
	// { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	// { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	// TAGKEYS(                        XK_6,                      5)
	// TAGKEYS(                        XK_7,                      6)
	// TAGKEYS(                        XK_8,                      7)
	// TAGKEYS(                        XK_9,                      8)

  // TODO: remap these
	// { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	// { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	// { MODKEY,                       XK_space,  setlayout,      {0} },
	// { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	// { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      dragmfact,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

