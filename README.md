PLATOTerm for Sharp X68000
==========================

PLATOTerm is a terminal emulator to access CYBIS services now available
on the Internet utilizing a WIFI Modem.

For the purposes of this documentation. PLATO and CYBIS are interchangeable
names for the same platform.

Requirements
------------
* Sharp X68000 computer
* 1MB of RAM
* 31kHz display
* WIFI modem attached to RS-232-C port

--------------------------------------------------------------
What services are currently available to access via PLATOTerm?
--------------------------------------------------------------
As of writing this preliminary documentation (January 2019), there are
two major CYBIS systems running. CYBER1.ORG and IRATA.ONLINE.

---------------------------
WHAT IS PLATO? (aka CYBIS?)
---------------------------
(from the PLATO wikipedia page:)

PLATO (Programmed Logic for Automatic Teaching Operations), was the first
generalized computer-asisted instruction system. Starting in 1960, it ran
on the University of Illinois ILLIAC I computer. By the late 1970s, it
supported several thousand graphics terminals distributed worldwide, running
on nearly a dozen different networked mainframe computers. Many modern
concepts in multi-user computing were originally developed on PLATO, including
forums, message boards, online testing, e-mail, chat rooms, picture languages,
instant messaging, remote screen sharing, and multi-player games.

-------------------
What is CYBER1.ORG?
-------------------

CYBER1.ORG is a CYBIS system initially set up in 2004, as a haven for
ex-PLATO users to experience a classic PLATO author experience.

CYBER1.ORG is home to many thousands of classic PLATO lessons and
notesfiles which have been restored from various sources, and have
been made available in the interests of preserving PLATO.

---------------------
What is IRATA.ONLINE?
---------------------

IRATA.ONLINE is a CYBIS system that has been set up for the benefit of
the greater vintage computing community, in the interest to provide
a unique experience that can be accessed on a wide variety of
vintage computers with a bitmapped graphics display. To this end,
IRATA.ONLINE develops PLATOTerm for dozens of platforms, so that they
can access CYBIS systems, as well as provide a community and learning
infrastructure for vintage computing users of all types, in the hopes
that as a cohesive community, something unique can hopefully
emerge.

-----------------------------------------------------------
What is the connection between IRATA.ONLINE and CYBER1.ORG?
-----------------------------------------------------------

CYBER1.ORG and IRATA.ONLINE are independent of one another. With that said,
the reason IRATA.ONLINE and PLATOTerm exist, are because of the efforts of
CYBER1.ORG to not only preserve a running PLATO system, and provide the
necessary information for interested parties to write terminal software
to access CYBIS systems, but also in their effort to produce a publically
available distribution of CYBIS that others who are interested may also
run their own CYBIS installation. IRATA.ONLINE is a direct result of the
public release of this distribution.

Loading PLATOTerm
-----------------

PLATOTerm can be loaded by executing '''plato.x''' from Human68K. For
best results, run '''tmsio.x''' before launching '''plato.x''' to get
improved serial port performance, using a command such as:

```
tmsio -b16
```

Default Settings
----------------
This Pre-release version of PLATOTerm99 is configured for the following settings:

* Built-in RS232 Port
* 19200 baud
* No Parity
* 8 Data Bits
* 1 Stop Bit

Connecting to IRATA.ONLINE
--------------------------

Once PLATOTerm is started, you can connect to CYBER1.ORG using your WIFI modem,
using a command such as:

```
ATDTIRATA.ONLINE:8005
```

Connecting to CYBER1.ORG
------------------------

Once PLATOTerm is started, you can connect to CYBER1.ORG using your WIFI modem,
using a command such as:

```
ATDTCYBERSERV.ORG:8005
```

PLATO Keyboard
-------------------
The PLATO keyboard is mapped to the Atari keys, like so:

(TODO: Map all the keys)

| PLATO KEY  	| X68000 Key  	|
|---	|---	|
| ANS  	| CTRL A  	|
| BACK  	| CTRL B  	|
| SHIFT-BACK | SHIFT CTRL B |
| COPY | CTRL C |
| SHIFT-COPY | SHIFT CTRL 1  |
| DATA | CTRL D |
| SHIFT-DATA | SHIFT CTRL D |
| EDIT | CTRL E |
| SHIFT-EDIT | SHIFT CTRL E |
| ERASE | BACKSPACE |
| SHIFT-ERASE | SHIFT BACKSPACE |
| FONT | CTRL F |
| &#247; | CTRL G | 
| HELP | CTRL H |
| SHIFT-HELP | SHIFT CTRL H |
| LAB | CTRL L |
| SHIFT-LAB | SHIFT CTRL L |
| MICRO | CTRL M |
| NEXT | ENTER |
| SHIFT-NEXT | SHIFT ENTER |
| SUPER | CTRL P |
| SHIFT-SUPER | SHIFT CTRL P |
| SQUARE | CTRL Q | 
| ACCESS | SHIFT CTRL Q |
| STOP | CTRL S |
| SHIFT-STOP | SHIFT CTRL S | 
| TERM | CTRL T |
| &#215; | CTRL X |
| SUB | CTRL Y |
| SHIFT-SUB | SHIFT CTRL Y |
| SIGMA | CTRL + |
| DELTA | CTRL - |
| ASSIGN | ESC |
| UNION | SHIFT CTRL + |
| INTERSECT | SHIFT CTRL - |

TTY Mode Keys
-------------
In addition, the following keys are available in TTY mode:

| Key | Function |
|---  |---       |
| F1 | PLATO Mode |
| F2 | TTY Mode |
| F10 | Quit |
| BREAK | Hang Up |
| CTRL D | Dial |
| CTRL 3 | 300 Baud |
| CTRL 1 | 1200 Baud |
| CTRL 2 | 2400 Baud |
| CTRL 6 | 9600 Baud |
| CTRL 9 | 19200 Baud |
| CTRL 8 | 38400 Baud |
| SHIFT CTRL D | Edit Dial String |
| SHIFT CTRL I | Edit Init String |


Credits
=======

* '''Thomas Cherryhomes''' - Terminal coding, sleepless nights.
* '''Steve Peltz''' - original PAD protocol decoder from MacPAD.
* '''Shaun Thompson''' - Testing, and toolchain guidance