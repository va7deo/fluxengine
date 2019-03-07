FluxEngine
==========

(If you're reading this on GitHub, the formatting's a bit messed up. [Try the
version on cowlark.com instead.](http://cowlark.com/fluxengine/)

What?
-----

The FluxEngine is a very cheap USB floppy disk interface capable of reading and
writing exotic non-PC floppy disk formats. It allows you to use a conventional
PC drive to accept Amiga disks, CLV Macintosh disks, bizarre 128-sector CP/M
disks, and other weird and bizarre formats. (Although not all of these are
supported yet. I could really use samples.)

The hardware consists of a single, commodity part with a floppy drive
connector soldered onto it. No ordering custom boards, no fiddly surface
mount assembly, and no fuss: nineteen simpler solder joints and you're done.

Don't believe me? Watch the demo reel!

<div style="text-align: center">
<iframe width="373" height="210" src="https://www.youtube.com/embed/m_s1iw8eW7o" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
</div>

**Important note.** On 2019-02-09 I did a hardware redesign and moved the pins on
the board. Sorry for the inconvenience, but it means you don't have to modify
the board any more to make it work. If you built the hardware prior to then,
you'll need to adjust it.

Where?
------

It's [open source on GitHub!](https://github.com/davidgiven/fluxengine)

How?
----

This page was getting kinda unwieldy so I've broken it up. Please consult the
following friendly articles:

  - [Frequently asked questions](doc/faq.md) ∾ but why...? ∾ does it...? ∾ can it...?
  
  - [How the FluxEngine works](doc/technical.md) ∾ nitty gritty of the
    sampler/sequencer hardware ∾ useful links on floppy drives ∾ why I'm not
    using an Arduino/STM32/ESP32/Raspberry Pi

  - [Making a FluxEngine](doc/building.md) ∾ what parts you need ∾ building it ∾
    setting up the toolchain ∾ compiling the firmware ∾ programming the board

  - [Using a FluxEngine](doc/using.md) ∾ what to do with your new hardware ∾
    flux files and image files ∾ knowing what you're doing

  - [Reading dubious disks](doc/problems.md) ∾ it's not an exact science ∾
    the sector map ∾ clock detection and the histogram ∾ tuning the clock ∾
    manual adjustment

Supported disk formats
----------------------

The current support state is as follows.

| Format                                   | Read? | Write? | Notes |
|:-----------------------------------------|:-----:|:------:|-------|
| IBM PC compatible                        |  🦄   |        | and compatibles (like the Atari ST) |
| [Acorn ADFS](doc/disk-acornadfs.md)      |  🦄   |        | single- and double- sided           |
| [Acorn DFS](doc/disk-acorndfs.md)        |  🦄   |        |                                     |
| [AES Superplus / No Problem](doc/disk-aeslanier.md) |  🦖   | | hard sectors! and _very_ experimental |
| [Ampro Little Board](doc/disk-ampro.md)  |  🦖   |        |                                     |
| [Apple II DOS 3.3](doc/disk-apple2.md)   |  🦖   |        | doesn't do logical sector remapping |
| [Amiga](doc/disk-amiga.md)               |  🦄   |        |                                     |
| [Commodore 64 1541](doc/disk-c64.md)     |  🦖   |        | and probably the other GCR formats  |
| [Brother 120kB](doc/disk-brother.md)     |  🦄   |        |                                     |
| [Brother 240kB](doc/disk-brother.md)     |  🦄   |   🦄   |                                     |
| [Macintosh 800kB](doc/disk-macintosh.md) |  🦖   |        | and probably the 400kB too          |
| [TRS-80](doc/disk-trs80.md)              |  🦖   |        | a minor variation of the IBM scheme |
| [Victor 9000](doc/disk-victor9k.md)      |  🦖   |        | experimental, probably buggy        |
{: .datatable }

Dinosaurs (🦖) have yet to be observed in real life --- I've written the
decoder based on Kryoflux (or other) dumps I've found. I don't (yet) have
real, physical disks in my hand to test the capture process.

Unicorns (🦄) are completely real --- this means that I've read actual,
physical disks with these formats and so know they work.

Notes:

  - IBM PC disks are the lowest-common-denominator standard. A number of other
    systems use this format in disguise (the Atari ST, late-era Apple
    machines, Acorn). FluxEngine supports both FM and MFM disks, although you
    have to tell it which one. If you have an unknown disk, try this; you may
    get something. Then [tell me about
    it](https://github.com/davidgiven/fluxengine/issues/new).

  - Not many formats support writing yet. That's because I need actual,
    physical hardware to test with in order to verify it works, and I only
    have a limited selection. (Plus a lot of the write code needs work.)
    There hasn't been a lot of demand for this yet; if you have a pressing
    need to write weird disks, [please
    ask](https://github.com/davidgiven/fluxengine/issues/new). I haven't
    implement write support for PC disks because they're boring and I'm lazy,
    and also because they vary so much that figuring out how to specify them
    is hard.

If you have samples of weird disks, and want to send them to me --- either
FluxEngine or Kryoflux dumps, or (even better) actually physically --- I can
identify them and add support.

Please note that at this point I am *not interested in copy protected disks*.
It's not out of principle. It's just they'll drive me insane. FluxEngine will
most likely be able to read the data fine, unless they're doing bizarre
things like spiral tracks or partially encoded data, but let's stick with
normal conventionally formatted disks for the time being!

Who?
----

The FluxEngine was designed, built and written by me, David Given. You may
contact me at dg@cowlark.com, or visit my website at http://www.cowlark.com.
There may or may not be anything interesting there.

License
-------

Everything here _except the contents of the `dep` directory_ is © 2019 David
Given and is licensed under the MIT open source license. Please see
[COPYING](COPYING) for the full text. The tl;dr is: you can do what you like
with it provided you don't claim you wrote it.

As an exception, `dep/fmt` contains a copy of [fmt](http://fmtlib.net),
maintained by Victor Zverovich (`vitaut <https://github.com/vitaut>`_) and
Jonathan Müller (`foonathan <https://github.com/foonathan>`_) with
contributions from many other people. It is licensed under the terms of the
BSD license. Please see the contents of the directory for the full text.