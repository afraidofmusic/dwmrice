/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nogroup";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#282936",   /* after initialization */
	[INPUT] =  "#00f769",   /* during input */
	[FAILED] = "#b45bcf",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;
