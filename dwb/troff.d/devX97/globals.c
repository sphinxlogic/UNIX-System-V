char gloxver[] = "@(#)globals.c	1.1";		/* SCCS */

# include "structs.h"

int		size ;
int		cur_font ;
int		xpos ;
int		ypos ;
int		page ;
int		input_line_num ;

struct	dev	dev ;
short		*sizes ;
short		*indices ;
char		*charnames ;

struct	line	**lines ;
struct	line	*line_pool ;
int		line_avail ;

struct	Font	*Fonts ;
int		font_map[15] ;
char		pde_name[BUFSIZE] ;

char		*prog_name ;

int	plotmap[NOFFSETS][NSLOPES][NVERTICES][NVERTICES] =
{
	0041 ,	/* 0 0 0 0 */
	0053 ,	/* 0 0 0 1 */
	0054 ,	/* 0 0 0 2 */
	0055 ,	/* 0 0 0 3 */
	0056 ,	/* 0 0 0 4 */
	0057 ,	/* 0 0 0 5 */
	0060 ,	/* 0 0 0 6 */
	0061 ,	/* 0 0 0 7 */
	0062 ,	/* 0 0 0 8 */
	0063 ,	/* 0 0 0 9 */
	0042 ,	/* 0 0 1 0 */
	0064 ,	/* 0 0 1 1 */
	0066 ,	/* 0 0 1 2 */
	0070 ,	/* 0 0 1 3 */
	0072 ,	/* 0 0 1 4 */
	0074 ,	/* 0 0 1 5 */
	0076 ,	/* 0 0 1 6 */
	0100 ,	/* 0 0 1 7 */
	0102 ,	/* 0 0 1 8 */
	0104 ,	/* 0 0 1 9 */
	0043 ,	/* 0 0 2 0 */
	0106 ,	/* 0 0 2 1 */
	0110 ,	/* 0 0 2 2 */
	0112 ,	/* 0 0 2 3 */
	0114 ,	/* 0 0 2 4 */
	0116 ,	/* 0 0 2 5 */
	0120 ,	/* 0 0 2 6 */
	0122 ,	/* 0 0 2 7 */
	0124 ,	/* 0 0 2 8 */
	0126 ,	/* 0 0 2 9 */
	0044 ,	/* 0 0 3 0 */
	0130 ,	/* 0 0 3 1 */
	0132 ,	/* 0 0 3 2 */
	0134 ,	/* 0 0 3 3 */
	0136 ,	/* 0 0 3 4 */
	0140 ,	/* 0 0 3 5 */
	0142 ,	/* 0 0 3 6 */
	0144 ,	/* 0 0 3 7 */
	0146 ,	/* 0 0 3 8 */
	0150 ,	/* 0 0 3 9 */
	0045 ,	/* 0 0 4 0 */
	0152 ,	/* 0 0 4 1 */
	0154 ,	/* 0 0 4 2 */
	0156 ,	/* 0 0 4 3 */
	0160 ,	/* 0 0 4 4 */
	0162 ,	/* 0 0 4 5 */
	0164 ,	/* 0 0 4 6 */
	0166 ,	/* 0 0 4 7 */
	0170 ,	/* 0 0 4 8 */
	0172 ,	/* 0 0 4 9 */
	0046 ,	/* 0 0 5 0 */
	0174 ,	/* 0 0 5 1 */
	0176 ,	/* 0 0 5 2 */
	0201 ,	/* 0 0 5 3 */
	0203 ,	/* 0 0 5 4 */
	0205 ,	/* 0 0 5 5 */
	0210 ,	/* 0 0 5 6 */
	0212 ,	/* 0 0 5 7 */
	0214 ,	/* 0 0 5 8 */
	0220 ,	/* 0 0 5 9 */
	0047 ,	/* 0 0 6 0 */
	0222 ,	/* 0 0 6 1 */
	0224 ,	/* 0 0 6 2 */
	0226 ,	/* 0 0 6 3 */
	0231 ,	/* 0 0 6 4 */
	0233 ,	/* 0 0 6 5 */
	0240 ,	/* 0 0 6 6 */
	0242 ,	/* 0 0 6 7 */
	0244 ,	/* 0 0 6 8 */
	0246 ,	/* 0 0 6 9 */
	0050 ,	/* 0 0 7 0 */
	0250 ,	/* 0 0 7 1 */
	0252 ,	/* 0 0 7 2 */
	0254 ,	/* 0 0 7 3 */
	0256 ,	/* 0 0 7 4 */
	0260 ,	/* 0 0 7 5 */
	0262 ,	/* 0 0 7 6 */
	0264 ,	/* 0 0 7 7 */
	0266 ,	/* 0 0 7 8 */
	0270 ,	/* 0 0 7 9 */
	0051 ,	/* 0 0 8 0 */
	0272 ,	/* 0 0 8 1 */
	0274 ,	/* 0 0 8 2 */
	0276 ,	/* 0 0 8 3 */
	0300 ,	/* 0 0 8 4 */
	0302 ,	/* 0 0 8 5 */
	0304 ,	/* 0 0 8 6 */
	0306 ,	/* 0 0 8 7 */
	0310 ,	/* 0 0 8 8 */
	0312 ,	/* 0 0 8 9 */
	0052 ,	/* 0 0 9 0 */
	0315 ,	/* 0 0 9 1 */
	0317 ,	/* 0 0 9 2 */
	0321 ,	/* 0 0 9 3 */
	0323 ,	/* 0 0 9 4 */
	0325 ,	/* 0 0 9 5 */
	0327 ,	/* 0 0 9 6 */
	0331 ,	/* 0 0 9 7 */
	0333 ,	/* 0 0 9 8 */
	0335 ,	/* 0 0 9 9 */
	0041 ,	/* 0 1 0 0 */
	0053 ,	/* 0 1 0 1 */
	0054 ,	/* 0 1 0 2 */
	0055 ,	/* 0 1 0 3 */
	0056 ,	/* 0 1 0 4 */
	0057 ,	/* 0 1 0 5 */
	0060 ,	/* 0 1 0 6 */
	0061 ,	/* 0 1 0 7 */
	0062 ,	/* 0 1 0 8 */
	0063 ,	/* 0 1 0 9 */
	0042 ,	/* 0 1 1 0 */
	0065 ,	/* 0 1 1 1 */
	0067 ,	/* 0 1 1 2 */
	0071 ,	/* 0 1 1 3 */
	0073 ,	/* 0 1 1 4 */
	0075 ,	/* 0 1 1 5 */
	0077 ,	/* 0 1 1 6 */
	0101 ,	/* 0 1 1 7 */
	0103 ,	/* 0 1 1 8 */
	0105 ,	/* 0 1 1 9 */
	0043 ,	/* 0 1 2 0 */
	0107 ,	/* 0 1 2 1 */
	0111 ,	/* 0 1 2 2 */
	0113 ,	/* 0 1 2 3 */
	0115 ,	/* 0 1 2 4 */
	0117 ,	/* 0 1 2 5 */
	0121 ,	/* 0 1 2 6 */
	0123 ,	/* 0 1 2 7 */
	0125 ,	/* 0 1 2 8 */
	0127 ,	/* 0 1 2 9 */
	0044 ,	/* 0 1 3 0 */
	0131 ,	/* 0 1 3 1 */
	0133 ,	/* 0 1 3 2 */
	0135 ,	/* 0 1 3 3 */
	0137 ,	/* 0 1 3 4 */
	0141 ,	/* 0 1 3 5 */
	0143 ,	/* 0 1 3 6 */
	0145 ,	/* 0 1 3 7 */
	0147 ,	/* 0 1 3 8 */
	0151 ,	/* 0 1 3 9 */
	0045 ,	/* 0 1 4 0 */
	0153 ,	/* 0 1 4 1 */
	0155 ,	/* 0 1 4 2 */
	0157 ,	/* 0 1 4 3 */
	0161 ,	/* 0 1 4 4 */
	0163 ,	/* 0 1 4 5 */
	0165 ,	/* 0 1 4 6 */
	0167 ,	/* 0 1 4 7 */
	0171 ,	/* 0 1 4 8 */
	0173 ,	/* 0 1 4 9 */
	0046 ,	/* 0 1 5 0 */
	0175 ,	/* 0 1 5 1 */
	0200 ,	/* 0 1 5 2 */
	0202 ,	/* 0 1 5 3 */
	0204 ,	/* 0 1 5 4 */
	0207 ,	/* 0 1 5 5 */
	0211 ,	/* 0 1 5 6 */
	0213 ,	/* 0 1 5 7 */
	0217 ,	/* 0 1 5 8 */
	0221 ,	/* 0 1 5 9 */
	0047 ,	/* 0 1 6 0 */
	0223 ,	/* 0 1 6 1 */
	0225 ,	/* 0 1 6 2 */
	0230 ,	/* 0 1 6 3 */
	0232 ,	/* 0 1 6 4 */
	0235 ,	/* 0 1 6 5 */
	0241 ,	/* 0 1 6 6 */
	0243 ,	/* 0 1 6 7 */
	0245 ,	/* 0 1 6 8 */
	0247 ,	/* 0 1 6 9 */
	0050 ,	/* 0 1 7 0 */
	0251 ,	/* 0 1 7 1 */
	0253 ,	/* 0 1 7 2 */
	0255 ,	/* 0 1 7 3 */
	0257 ,	/* 0 1 7 4 */
	0261 ,	/* 0 1 7 5 */
	0263 ,	/* 0 1 7 6 */
	0265 ,	/* 0 1 7 7 */
	0267 ,	/* 0 1 7 8 */
	0271 ,	/* 0 1 7 9 */
	0051 ,	/* 0 1 8 0 */
	0273 ,	/* 0 1 8 1 */
	0275 ,	/* 0 1 8 2 */
	0277 ,	/* 0 1 8 3 */
	0301 ,	/* 0 1 8 4 */
	0303 ,	/* 0 1 8 5 */
	0305 ,	/* 0 1 8 6 */
	0307 ,	/* 0 1 8 7 */
	0311 ,	/* 0 1 8 8 */
	0313 ,	/* 0 1 8 9 */
	0052 ,	/* 0 1 9 0 */
	0316 ,	/* 0 1 9 1 */
	0320 ,	/* 0 1 9 2 */
	0322 ,	/* 0 1 9 3 */
	0324 ,	/* 0 1 9 4 */
	0326 ,	/* 0 1 9 5 */
	0330 ,	/* 0 1 9 6 */
	0332 ,	/* 0 1 9 7 */
	0334 ,	/* 0 1 9 8 */
	0336 ,	/* 0 1 9 9 */
} ;
