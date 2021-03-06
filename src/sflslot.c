/*===========================================================================*
 *                                                                           *
 *  sflslot.c - Time slot functions                                          *
 *                                                                           *
 *  Copyright (c) 1991-2010 iMatix Corporation                               *
 *                                                                           *
 *  ------------------ GPL Licensed Source Code ------------------           *
 *  iMatix makes this software available under the GNU General               *
 *  Public License (GPL) license for open source projects.  For              *
 *  details of the GPL license please see www.gnu.org or read the            *
 *  file license.gpl provided in this package.                               *
 *                                                                           *
 *  This program is free software; you can redistribute it and/or            *
 *  modify it under the terms of the GNU General Public License as           *
 *  published by the Free Software Foundation; either version 3 of           *
 *  the License, or (at your option) any later version.                      *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU General Public License for more details.                             *
 *                                                                           *
 *  You should have received a copy of the GNU General Public                *
 *  License along with this program in the file 'license.gpl'; if            *
 *  not, see <http://www.gnu.org/licenses/>.                                 *
 *                                                                           *
 *  You can also license this software under iMatix's General Terms          *
 *  of Business (GTB) for commercial projects.  If you have not              *
 *  explicitly licensed this software under the iMatix GTB you may           *
 *  only use it under the terms of the GNU General Public License.           *
 *                                                                           *
 *  For more information, send an email to info@imatix.com.                  *
 *  --------------------------------------------------------------           *
 *===========================================================================*/

#include "prelude.h"                    /*  Universal header file            */
#include "sfldate.h"                    /*  Date/time library functions      */
#include "sflslot.h"                    /*  Prototypes for functions         */

#define BIT(x)        (word) (1 << ((x) % 8))
#define BYTE(x)       ((x) / 8)


/*  ---------------------------------------------------------------------[<]-
    Function: year_range_empty

    Synopsis: Excludes all days in the year (sets all bits to zero).
    ---------------------------------------------------------------------[>]-*/

void
year_range_empty (byte *range)
{
    memset (range, 0, sizeof (year_range));
}


/*  ---------------------------------------------------------------------[<]-
    Function: year_range_fill

    Synopsis: Includes all days in the year (sets all bits to 1).
    ---------------------------------------------------------------------[>]-*/

void
year_range_fill (byte *range)
{
    memset (range, 255, sizeof (year_range));
}


/*  ---------------------------------------------------------------------[<]-
    Function: year_slot_clear

    Synopsis: Clears the slots for the specified day range.  If day_to is
    zero, it is ignored; only the slot for day_from is cleared.  Returns 0
    if okay, -1 if the specified range is invalid.
    ---------------------------------------------------------------------[>]-*/

int
year_slot_clear (byte *range, int day_from, int day_to)
{
    if (day_to == 0)
        day_to = day_from;              /*  Range is just one day            */

    if (day_from > day_to)
        return (-1);                    /*  Bad range                        */

    while (day_from <= day_to)          /*  Find and clear each bit          */
      {
        ASSERT (day_from >= 0 && day_from < MAX_DAY);
        range [BYTE (day_from)] &= 255 - BIT (day_from);
        day_from++;
      }
    return (0);                         /*  No errors                        */
}


/*  ---------------------------------------------------------------------[<]-
    Function: year_slot_set

    Synopsis: Sets the slots for the specified day range.  If day_to is
    zero, it is ignored; only the slot for day_from is set.  Returns 0
    if okay, -1 if the specified range is invalid.
    ---------------------------------------------------------------------[>]-*/

int
year_slot_set (byte *range, int day_from, int day_to)
{
    if (day_to == 0)
        day_to = day_from;              /*  Range is just one day            */

    if (day_from > day_to)
        return (-1);                    /*  Bad range                        */

    while (day_from <= day_to)          /*  Find and set each bit            */
      {
        ASSERT (day_from >= 0 && day_from < MAX_DAY);
        range [BYTE (day_from)] |= BIT (day_from);
        day_from++;
      }
    return (0);                         /*  No errors                        */
}


/*  ---------------------------------------------------------------------[<]-
    Function: year_slot_filled

    Synopsis: Returns TRUE if the specified day slot is set; returns FALSE
    if the slot is not set.
    ---------------------------------------------------------------------[>]-*/

Bool
year_slot_filled (const byte *range, int day)
{
    ASSERT (day >= 0 && day < MAX_DAY);
    return ((range [BYTE (day)] & BIT (day)) > 0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: day_range_empty

    Synopsis: Excludes all minutes in the day (sets all bits to zero).
    ---------------------------------------------------------------------[>]-*/

void
day_range_empty (byte *range)
{
    memset (range, 0, sizeof (day_range));
}


/*  ---------------------------------------------------------------------[<]-
    Function: day_range_fill

    Synopsis: Includes all minutes in the day (sets all bits to 1).
    ---------------------------------------------------------------------[>]-*/

void
day_range_fill (byte *range)
{
    memset (range, 255, sizeof (day_range));
}


/*  ---------------------------------------------------------------------[<]-
    Function: day_slot_clear

    Synopsis: Clears the slots for the specified minute range.  If min_to
    is zero, it is ignored; only the slot for min_from is cleared.  Returns
    0 if okay, -1 if the specified range is invalid.
    ---------------------------------------------------------------------[>]-*/

int
day_slot_clear (byte *range, int min_from, int min_to)
{
    if (min_to == 0)
        min_to = min_from;              /*  Range is just one minute         */

    if (min_from > min_to)
        return (-1);                    /*  Bad range                        */

    while (min_from <= min_to)          /*  Find and clear each bit          */
      {
        ASSERT (min_from >= 0 && min_from < MAX_MIN);
        range [BYTE (min_from)] &= 255 - BIT (min_from);
        min_from++;
      }
    return (0);                         /*  No errors                        */
}


/*  ---------------------------------------------------------------------[<]-
    Function: day_slot_set

    Synopsis: Sets the slots for the specified minute range.  If min_to is
    zero, it is ignored; only the slot for min_from is set.   Returns 0 if
    okay, -1 if the specified range is invalid.
    ---------------------------------------------------------------------[>]-*/

int
day_slot_set (byte *range, int min_from, int min_to)
{
    if (min_to == 0)
        min_to = min_from;              /*  Range is just one minute         */

    if (min_from > min_to)
        return (-1);                    /*  Bad range                        */

    while (min_from <= min_to)          /*  Find and set each bit            */
      {
        ASSERT (min_from >= 0 && min_from < MAX_MIN);
        range [BYTE (min_from)] |= BIT (min_from);
        min_from++;
      }
    return (0);                         /*  No errors                        */
}


/*  ---------------------------------------------------------------------[<]-
    Function: day_slot_filled

    Synopsis: Returns TRUE if the specified minute slot is set; returns
    FALSE if the slot is not set.
    ---------------------------------------------------------------------[>]-*/

Bool
day_slot_filled (const byte *range, int minute)
{
    ASSERT (minute >= 0 && minute < MAX_MIN);
    return ((range [BYTE (minute)] & BIT (minute)) > 0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: date_to_day

    Synopsis: Extracts the day value (1..366) for the specified date.
    The date is an 8-digit number: YYYYMMDD.
    ---------------------------------------------------------------------[>]-*/

int
date_to_day (long date)
{
    return (julian_date (date));
}


/*  ---------------------------------------------------------------------[<]-
    Function: time_to_min

    Synopsis: Extracts the minute value (0..1439) for the specified time.
    The time is an 8-digit number: HHMMSSCC.
    ---------------------------------------------------------------------[>]-*/

int
time_to_min (long time)
{
    int
        hour,                           /*  Hour component of time           */
        minute;                         /*  Minute component of time         */

    hour   = (int)  (time / 1000000L);
    minute = (int) ((time % 1000000L) / 10000L);
    minute += hour * 60;
    return (minute);
}
