# Copyright (c) 2002, Adam Dunkels.
# All rights reserved. 
#
# Redistribution and use in source and binary forms, with or without 
# modification, are permitted provided that the following conditions 
# are met: 
# 1. Redistributions of source code must retain the above copyright 
#    notice, this list of conditions and the following disclaimer. 
# 2. Redistributions in binary form must reproduce the above copyright 
#    notice, this list of conditions and the following disclaimer in the 
#    documentation and/or other materials provided with the distribution. 
# 3. The name of the author may not be used to endorse or promote
#    products derived from this software without specific prior
#    written permission.  
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
# GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
#
# This file is part of the Contiki desktop environment
#
# $Id: Makefile,v 1.9 2005/05/07 13:29:39 oliverschmidt Exp $
#

all: contiki loader-arch-module.o loader-arch-module-dsc.o contiki-labels.o \
     about.prg about.dsc processes.prg processes.dsc \
     netconf.prg netconf.dsc memstat.prg memstat.dsc 

CONTIKI=../contiki
CONTIKICC65=../contiki-cc65
SYS=c128

include $(CONTIKI)/Makefile.common
include $(CONTIKICC65)/Makefile.cc65

CFLAGS=$(CFLAGSCC65) -DWITH_LOADER_ARCH

contiki: contiki-main.o strncasecmp.o petsciiconv.o \
 ctk-conio.o ctk.o arg.o ek.o timer.o \
 program-handler.o loader-arch.o \
 about-dsc.o netconf-dsc.o processes-dsc.o memstat-dsc.o
	$(CL) $(CLFLAGS) -o contiki -t $(SYS) $^

