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

Loading PLATOTerm99
-------------------
PLATOTerm99 can be loaded using option 5 of the Editor/Assembler cartridge.
The filename is PLATO

Default Settings
----------------
This Pre-release version of PLATOTerm99 is configured for the following settings:

* RS232 Port 1
* 1200 Baud
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

| PLATO KEY  	| TI Key  	|
|---	|---	|
| ANS  	| CTRL A  	|
| BACK  	| FCTN 9  	|
| SHIFT-BACK | CTRL 9 |
| COPY | FCTN 1 |
| SHIFT-COPY | CTRL 1  |
| DATA | FCTN 2 |
| SHIFT-DATA | CTRL 2 |
| EDIT | FCTN 5 |
| SHIFT-EDIT | CTRL 5 |
| ERASE | FCTN S |
| SHIFT-ERASE | CTRL S |
| FONT | CTRL F |
| &#247; | CTRL 8 | 
| HELP | FCTN H |
| SHIFT-HELP | CTRL H |
| LAB | FCTN L |
| SHIFT-LAB | CTRL L |
| MICRO | FCTN M |
| NEXT | ENTER |
| SHIFT-NEXT | FCTN ; |
| SUPER | FCTN N |
| SHIFT-SUPER | CTRL N |
| SQUARE | FCTN Q | 
| ACCESS | CTRL Q |
| STOP | FCTN 0 |
| SHIFT-STOP | CTRL 0 | 
| TERM | FCTN 3 |
| &#215; | FCTN 8 |
| SUB | FCTN B |
| SHIFT-SUB | CTRL B |
| SIGMA | FCTN + |
| DELTA | FCTN - |
| ASSIGN | FCTN 4 |
| UNION | FCTN 7 |
| INTERSECT | CTRL 7 |

Credits
=======

* '''Thomas Cherryhomes''' - Terminal coding, sleepless nights.
* '''Steve Peltz''' - original PAD protocol decoder from MacPAD.
* '''Ron Klein''' - Testing, testing, and more testing
* '''Gregory McGill''' - Testing, keyboard mapping help
* '''Tursi''' - libti99, and the needed rs232 routines
* '''jedimatt42''' - TIPI support code.
* '''insomniac''' - GCC for TI
