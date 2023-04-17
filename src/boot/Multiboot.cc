/*****************************************************************************
 *                                                                           *
 *                  M U L T I B O O T                                        *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Wir am Ende des Bootvorgangs vom Assembler-Code gerufen. *
 *                  Hier lesen wir Infos von Multiboot aus. Danach wird main *
 *                  aufgerufen.                                              *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 16.2.2023                       *
 *****************************************************************************/

#include "boot/Multiboot.h"
#include "lib/Types.h"
#include "kernel/Globals.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))


extern "C" {
	void main(); 
	void mb_init(uint64_t mbi_addr);
}


void mb_init(uint64_t mbi_addr) {
   multiboot_info_t *mbi;

   /* Set MBI to the address of the Multiboot information structure. */
   mbi = (multiboot_info_t *) mbi_addr;

/*
   if (CHECK_FLAG (mbi->flags, 12)) {
      kout.set_graphic_infos( mbi->framebuffer_addr, mbi->framebuffer_width, 
                              mbi->framebuffer_height, mbi->framebuffer_pitch,
                              mbi->framebuffer_bpp
                            );
    }
*/    
    main();
}
