#include <iocslib.h>
#include <graph.h>
#include "screen.h"
#include "font.h"
#include "protocol.h"
#include "io.h"

char tmp[64];
int previousMode;
unsigned char CharWide=8;
unsigned char CharHigh=16;
padPt TTYLoc;
padPt statusLoc={0,0};
unsigned char fontm23[2048];
extern padBool FastText; /* protocol.c */
padRGB palette[16];
unsigned long current_foreground=1;
unsigned long current_background=0;
padRGB current_foreground_rgb={255,255,255};
padRGB current_background_rgb={0,0,0};
int highest_color_index;

/* Transform 8-bit RGB to X68000 palette value. */
#define X68_GRB(r, g, b, i) ( ( ((b&0xF8)>>2) | (((g)&0xF8)<<8) | (((r)&0xF8)<<3) ) | i )
#define FONTPTR(a) (a<<4)
#define X(x) (x)
#define Y(y) (y^0x1FF)

/**
 * screen_init() - Set up the screen
 */
void screen_init(void)
{
  /* 512x512 16 colors 31kHz */
  previousMode=_iocs_crtmod(-1);
  _iocs_crtmod(4);
  _iocs_g_clr_on();
  _iocs_b_curoff();
  screen_clear();
}

/**
 * screen_update_colors() - Set the terminal colors
 */
void screen_update_colors(void)
{
  long i=0;
  for (i=0;i<16;i++)
    {
      palet(i,X68_GRB(palette[i].red,palette[i].green,palette[i].blue,0));
    }

}

/**
 * screen_clear_palette - Clear the palette
 */
void screen_clear_palette(void)
{
  int i;
  for (i=0;i<8;i++)
    {
      palette[i].red=0;
      palette[i].green=0;
      palette[i].blue=0;
    }
}


/**
 * screen_wait(void) - Sleep for approx 16.67ms
 */
void screen_wait(void)
{
}

/**
 * screen_beep(void) - Beep the terminal
 */
void screen_beep(void)
{
  _iocs_b_putc(0x07); /* BELL */
}

/**
 * screen_clear - Clear the screen
 */
void screen_clear(void)
{
  highest_color_index=0;
  screen_clear_palette();

  current_foreground=current_background=0;
  
  palette[0].red=current_background_rgb.red;
  palette[0].green=current_background_rgb.green;
  palette[0].blue=current_background_rgb.blue;

  if ((current_background_rgb.red   != current_foreground_rgb.red) &&
      (current_background_rgb.green != current_foreground_rgb.green) &&
      (current_background_rgb.blue  != current_foreground_rgb.blue))
    {
      palette[1].red=current_foreground_rgb.red;
      palette[1].green=current_foreground_rgb.green;
      palette[1].blue=current_foreground_rgb.blue;
      highest_color_index++;
      current_foreground=1;
    }

  if ((palette[1].red==0) &&
      (palette[1].green==0) &&
      (palette[1].blue==0) &&
      (palette[0].red==0) &&
      (palette[0].green==0) &&
      (palette[0].blue==0))
    {
      palette[0].red=palette[0].green=palette[0].blue=0;
      palette[1].red=palette[1].green=palette[1].blue=255;
      current_foreground=1;
      current_background=0;
      current_foreground_rgb.red=current_foreground_rgb.green=current_foreground_rgb.blue=255;
      current_background_rgb.red=current_foreground_rgb.green=current_foreground_rgb.blue=0;
    }
  
  screen_update_colors();

  wipe();

  /* fill(0,0,511,511,current_background); */
}

/**
 * screen_color_matching(color) - return index of matching color, or a new index, 
 * if not found.
 */
unsigned char screen_color_matching(padRGB* theColor)
{
  unsigned char i;
  for (i=0;i<8;i++)
    {
      if (i>highest_color_index)
	{
	  palette[i].red=theColor->red;
	  palette[i].green=theColor->green;
	  palette[i].blue=theColor->blue;
	  highest_color_index++;
	  return i;
	}
      else
	{
	  if ((palette[i].red==theColor->red) && 
	      (palette[i].green==theColor->green) && 
	      (palette[i].blue==theColor->blue))
	    {
	      return i;
	    }
	}
    }
}

/**
 * screen_foreground - set foreground color
 */
void screen_foreground(padRGB* theColor)
{
  current_foreground_rgb.red=theColor->red;
  current_foreground_rgb.green=theColor->green;
  current_foreground_rgb.blue=theColor->blue;
  current_foreground=screen_color_matching(theColor);
  screen_update_colors();
}

/**
 * screen_background - set background_color
 */
void screen_background(padRGB* theColor)
{
  current_background_rgb.red=theColor->red;
  current_background_rgb.green=theColor->green;
  current_background_rgb.blue=theColor->blue;
  current_background=screen_color_matching(theColor);
  screen_update_colors();
}

/**
 * screen_current_color(void) - Set the current pen mode
 */
int screen_current_color(void)
{
  if (CurMode==ModeInverse || CurMode==ModeErase)
    return current_background;
  else
    return current_foreground;
}

/**
 * screen_block_draw(Coord1, Coord2) - Perform a block fill from Coord1 to Coord2
 */
void screen_block_draw(padPt* Coord1, padPt* Coord2)
{
  fill(X(Coord1->x),Y(Coord1->y),X(Coord2->x),Y(Coord2->y),screen_current_color());
}

/**
 * screen_dot_draw(Coord) - Plot a mode 0 pixel
 */
void screen_dot_draw(padPt* Coord)
{
  pset(X(Coord->x),Y(Coord->y),screen_current_color());
}

/**
 * screen_line_draw(Coord1, Coord2) - Draw a mode 1 line
 */
void screen_line_draw(padPt* Coord1, padPt* Coord2)
{
  line(X(Coord1->x),Y(Coord1->y),X(Coord2->x),Y(Coord2->y),screen_current_color(),0xffff);
}

/**
 * screen_char_draw(Coord, ch, count) - Output buffer from ch* of length count as PLATO characters
 */
void screen_char_draw(padPt* Coord, unsigned char* ch, unsigned char count)
{

  short offset; /* due to negative offsets */
  unsigned short x;      /* Current X and Y coordinates */
  unsigned short y;
  unsigned short* px;   /* Pointers to X and Y coordinates used for actual plotting */
  unsigned short* py;
  unsigned char i; /* current character counter */
  unsigned char a; /* current character byte */
  unsigned char j,k; /* loop counters */
  char b; /* current character row bit signed */
  unsigned char width=8;
  unsigned char height=16;
  unsigned char FONT_SIZE_X=8;
  unsigned char FONT_SIZE_Y=16;
  unsigned short deltaX=1;
  unsigned short deltaY=1;
  unsigned char mainColor=1;
  unsigned char altColor=0;
  unsigned char *p;
  unsigned char* curfont;
  
  switch(CurMem)
    {
    case M0:
      curfont=font;
      offset=-32;
      break;
    case M1:
      curfont=font;
      offset=64;
      break;
    case M2:
      curfont=fontm23;
      offset=-32;
      break;
    case M3:
      curfont=fontm23;
      offset=32;      
      break;
    }

  if (CurMode==ModeRewrite)
    {
      altColor=current_background;
    }
  else if (CurMode==ModeInverse)
    {
      altColor=current_foreground;
    }
  
  if (CurMode==ModeErase || CurMode==ModeInverse)
    mainColor=current_background;
  else
    mainColor=current_foreground;

  x=X(Coord->x&0x1FF);

  if (ModeBold)
    y=Y((Coord->y)+30&0x1FF);
  else
    y=Y((Coord->y)+15&0x1FF);
  
  if (FastText==padF)
    {
      goto chardraw_with_fries;
    }

  /* the diet chardraw routine - fast text output. */
  
  for (i=0;i<count;++i)
    {
      a=*ch;
      ++ch;
      a+=offset;
      p=&curfont[FONTPTR(a)];
      
      for (j=0;j<FONT_SIZE_Y;++j)
  	{
  	  b=*p;
	  
  	  for (k=0;k<FONT_SIZE_X;++k)
  	    {
  	      if (b<0) /* check sign bit. */
		{
		  pset(x,y,mainColor);
		}

	      ++x;
  	      b<<=1;
  	    }

	  ++y;
	  x-=width;
	  ++p;
  	}

      x+=width;
      y-=height;
    }

  return;

 chardraw_with_fries:
  if (Rotate)
    {
      deltaX=-abs(deltaX);
      width=-abs(width);
      px=&y;
      py=&x;
    }
    else
    {
      px=&x;
      py=&y;
    }
  
  if (ModeBold)
    {
      deltaX = deltaY = 2;
      width<<=1;
      height<<=1;
    }
  
  for (i=0;i<count;++i)
    {
      a=*ch;
      ++ch;
      a+=offset;
      p=&curfont[FONTPTR(a)];
      for (j=0;j<FONT_SIZE_Y;++j)
  	{
  	  b=*p;

	  if (Rotate)
	    {
	      px=&y;
	      py=&x;
	    }
	  else
	    {
	      px=&x;
	      py=&y;
	    }

  	  for (k=0;k<FONT_SIZE_X;++k)
  	    {
  	      if (b<0) /* check sign bit. */
		{
		  if (ModeBold)
		    {
		      pset(*px+1,*py,mainColor);
		      pset(*px,*py+1,mainColor);
		      pset(*px+1,*py+1,mainColor);
		    }
		  pset(*px,*py,mainColor);
		}
	      else
		{
		  if (CurMode==ModeInverse || CurMode==ModeRewrite)
		    {
		      if (ModeBold)
			{
			  pset(*px+1,*py,altColor);
			  pset(*px,*py+1,altColor);
			  pset(*px+1,*py+1,altColor);
			}
		      pset(*px,*py,altColor); 
		    }
		}

	      x += deltaX;
  	      b<<=1;
  	    }

	  y+=deltaY;
	  x-=width;
	  ++p;
  	}

      Coord->x+=width;
      x+=width;
      y-=height;
    }

  return;
  
}

/**
 * screen_tty_char - Called to plot chars when in tty mode
 */
void screen_tty_char(padByte theChar)
{
  if ((theChar >= 0x20) && (theChar < 0x7F)) {
    screen_char_draw(&TTYLoc, &theChar, 1);
    TTYLoc.x += CharWide;
  }
  else if ((theChar == 0x0b)) /* Vertical Tab */
    {
      TTYLoc.y += CharHigh;
    }
  else if ((theChar == 0x08) && (TTYLoc.x > 7))	/* backspace */
    {
      padPt ec1,ec2;
      TTYLoc.x -= CharWide;
      ec1.x=TTYLoc.x;
      ec1.y=TTYLoc.y;
      ec2.x=TTYLoc.x+CharWide;
      ec2.y=TTYLoc.y+CharHigh;
      CurMode=ModeErase;
      screen_block_draw(&ec1,&ec2);
      CurMode=ModeRewrite;
   }
  else if (theChar == 0x0A)			/* line feed */
    TTYLoc.y -= CharHigh;
  else if (theChar == 0x0D)			/* carriage return */
    TTYLoc.x = 0;
  
  if (TTYLoc.x + CharWide > 511) {	/* wrap at right side */
    TTYLoc.x = 0;
    TTYLoc.y -= CharHigh;
  }
  
  if (TTYLoc.y < 0) {
    screen_clear();
    TTYLoc.y=495;
  }

}

/**
 * screen_paint - Called to paint at location.
 */
void screen_paint(padPt* Coord)
{
  paint(X(Coord->x),Y(Coord->y),current_foreground);
}

/**
 * screen_clear_status(void)
 * Clear status area
 */
void screen_clear_status(void)
{
  fill(X(0),Y(0),X(511),Y(16),1);
}

/**
 * screen_show_status(msg)
 */
void screen_show_status(unsigned char* msg)
{
  int previous_foreground=current_foreground;
  int previous_background=current_background;
  padPt coord={0,0};
  screen_clear_status();
  current_foreground=0;
  current_background=1;
  screen_char_draw(&coord,msg,strlen(msg));
  current_foreground=previous_foreground;
  current_background=previous_background;
}

/**
 * screen_show_baud_rate - Show baud rate
 */
void screen_show_baud_rate(int baud)
{
  sprintf(tmp,"%d Baud",baud);
  screen_show_status(tmp);
}

/**
 * screen_show_hang_up - Show hang-up message
 */
void screen_show_hang_up(void)
{
  screen_show_status("Hanging up...");
}

/**
 * screen_done()
 * Close down TGI
 */
void screen_done(void)
{
  _iocs_crtmod(previousMode);
  _iocs_g_clr_on();
  _iocs_b_curon();
  wipe();
}
