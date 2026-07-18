// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// $Log:$
//
// DESCRIPTION:
//    Main program, simply calls D_DoomMain high level loop.
//
//-----------------------------------------------------------------------------
#include <limits.h>

#include <stdlib.h>

#include <inttypes.h>
#include <libdragon.h>

#include "doomdef.h"
#include "m_argv.h"
#include "d_main.h"
#include "g_game.h"

extern void DoomIsOver();

void check_and_init_mempak(void)
{
    struct controller_data output;
    get_accessories_present(&output);

    switch (identify_accessory(0))
    {
        case ACCESSORY_NONE:
        {
            printf("No accessory inserted!\n");
            break;
        }
        case ACCESSORY_MEMPAK:
        {
            int err;
            // I left the below in the code #ifdef'd out for when I needed an easy way to nuke a controller pak
#if 0
            if (format_mempak(0))
            {
                printf("Error formatting mempak!\n");
            }
            else
            {
                printf("Memory card formatted!\n");
            }
#endif
            if ((err = validate_mempak(0)))
            {
                if (err == -3)
                {
                    printf("Mempak is not formatted! Formatting it automatically.\n");

                    if (format_mempak(0))
                    {
                        printf("Error formatting mempak!\n");
                    }
                    else
                    {
                        printf("Memory card formatted!\n");
                    }
                }
                else
                {
                    printf("Mempak bad or removed during read!\n");
                }
            }
            else
            {
                // this will print the details of each entry on the controller pak
#if 0
                for(int j = 0; j < 16; j++)
                {
                    entry_structure_t entry;

                    get_mempak_entry(0, j, &entry);

                    if(entry.valid)
                    {
                        printf("%s - %d blocks\n", entry.name, entry.blocks);
                    }
                    else
                    {
                        printf("(EMPTY)\n");
                    }
                }
#endif
                printf("\nFree space: %d blocks\n", get_mempak_free_space(0));
            }

            break;
        }
        case ACCESSORY_RUMBLEPAK:
        {
            printf("Cannot read data off of rumblepak!\n");
            break;
        }
    }
}


extern int center_x, center_y;

int main(void)
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP,
                 2, GAMMA_NONE, FILTERS_RESAMPLE);

    rdpq_init();
    joypad_init();
    debug_init_isviewer();

    int rc = dfs_init(DFS_DEFAULT_LOCATION);
    assertf(rc == DFS_ESUCCESS, "dfs_init failed: %d", rc);

    D_DoomMain();

    for (;;);
}

