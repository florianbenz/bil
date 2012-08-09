BIL
====

# Introduction
The Bitstream Interpretation Library, in short BIL, is an open library for
reading and interpreting [Xilinx](http://xilinx.com) bitstream files targeted
at Virtex FPGAs. Its main features are:
* Configuration raw data extraction from bitstream files. This is done using
  an emulator of the FPGA's packet processor.
* XDL design regeneration out of configuration raw data. The required mapping
  between raw data bits and resulting FPGA configuration is fetched from a
  database generated in a previous step. At the moment this does not recover a
  full netlist, but only the inter-tile PIPs.
* Automated configuration mapping analyzation of a device. This is done by
  correlating a XDL design with the corresponding bitstream.
* Usage of XDLRC device descriptions as data source for available resources
  and XDL entities. In order to facilitate their usage, they are converted
  into a much smaller custom format.
* Support for all devices in the Virtex-5 family.


# Target platform
BIL is written in plain C++ and uses no hardware or software platform specific
features. It should be compilable by every standard conforming C++ compiler.


# Usage
BIL comes as a set of C++ classes that you can use directly in your project.
All neccessary headers and implementation files can be found in the _src_ folder.

If you do not want to compile BIL everytime you include it in a project, you
may wish to use it as a static library. Therefore, there is a project for
building BIL that way. Additionally, precompiled x86 Windows versions of the
library are located in the _lib_ folder.

Instead of integrating BIL into your project, you can also use the applications
that come along with it. These are precompiled for x86 Windows (in the _bin_
folder). For building them on your own, there are appropriate projects.

At the moment all project files are MS Visual Studio 2008 projects.


# Documentation
You can find the documentation in the _doc_ folder. Alternatively, it is
available online at http://florianbenz.github.com/bil.


# License
BIL is licensed under the terms of the FreeBSD License, see included LICENSE file.