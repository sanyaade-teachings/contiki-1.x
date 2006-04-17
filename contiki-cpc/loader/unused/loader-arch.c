/**
 * \file
 * File loader implementation.
 * \author Adam Dunkels <adam@dunkels.com>
 *
 * This file implements dynamically loadable files for Contiki using
 * the cc65 module loading system. The actual file operations are
 * implemented in other files.
 */

/*
 * Copyright (c) 2003, Adam Dunkels.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution. 
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.  
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
 *
 * This file is part of the Contiki desktop OS
 *
 * $Id: loader-arch.c,v 1.1 2006/04/17 15:02:38 kthacker Exp $
 *
 */

#include <stdlib.h>
#include "modload.h" 

#ifndef NULL
#define NULL (void *)0
#endif /* NULL */

#include "cfs.h"

#include "loader.h"

#include "loader-arch.h"

static int __fastcall__
do_read(int f, char *buf, unsigned int len)
{
  return cfs_read(f, buf, len);
}

static struct mod_ctrl ctrl = {
  (void *)do_read            /* Read from disk */
};


struct loader_arch_hdr {
  char arch[8];
  char version[8];

  char initfunc[1];
};

/*-----------------------------------------------------------------------------------*/
/**
 * \internal
 * Load a program from disk and execute it.
 *
 * Code originally written by Ullrich von Bassewitz.
 */
/*-----------------------------------------------------------------------------------*/
static unsigned char
load(const char *name)
{
  unsigned char res;
  
  /* Now open the file */
  ctrl.callerdata = cfs_open(name, 0);
  if(ctrl.callerdata < 0) {
    /* Could not open the file, display an error and return */
    /* ### */
    return LOADER_ERR_OPEN;
  }
  
  /* Load the module */
  res = mod_load(&ctrl);
  
  /* Close the input file */
  cfs_close(ctrl.callerdata);
  
  /* Check the return code */
  if(res != MLOAD_OK) {
    /* Wrong module, out of memory or whatever. Print an error
     * message and return.
     */
    /* ### */
    return res;
  }
  
  /* We've successfully loaded the module. */
  
  return LOADER_OK;
}
/*-----------------------------------------------------------------------------------*/
/**
 * Load and start a program.
 *
 * \param name The name of the program file.
 * \param arg A pointer that will be passed to the new process.
 */
/*-----------------------------------------------------------------------------------*/
unsigned char
loader_arch_load(const char *name, char *arg)
{
  unsigned char r;
  struct loader_arch_hdr *hdr;
  
  r = load(name);
  if(r != MLOAD_OK) {
    return r;
  }
  hdr = (struct loader_arch_hdr *)ctrl.module;
  
  /* Check the program header and see that version and architecture
     matches. */
  
  /* Call the init function. */
  ((void (*)(char *))hdr->initfunc)(arg);

  return LOADER_OK;
}
/*-----------------------------------------------------------------------------------*/
/**
 * Load a DSC file into memory.
 *
 * The memory must be deallocated with the loader_arch_free() function
 * after is has been used.
 *
 * \param name The name of the DSC file.
 *
 * \return A pointer to the struct dsc or NULL if the DSC file could
 * not be loaded.
 */
/*-----------------------------------------------------------------------------------*/
struct dsc *
loader_arch_load_dsc(const char *name)
{
  unsigned char r;

  r = load(name);
  if(r == MLOAD_OK) {
    return (struct dsc *)ctrl.module;
  }
  return NULL;
}
/*-----------------------------------------------------------------------------------*/
/**
 * Deallocate memory previously allocated by the loader.
 *
 * The loader allocates memory when it loads programs or DSC
 * files. All such memory must be deallocated with this function. Memory for programs is automatically deallocated when calling the LOADER_UNLOAD() function, but memory for DSCs must be explicitly deallcated with this function.
 *
 * \param addr A pointer to memory allocated by the loader.
 */
/*-----------------------------------------------------------------------------------*/
void
loader_arch_free(void *addr)
{
  mod_free(addr);
}
/*-----------------------------------------------------------------------------------*/

