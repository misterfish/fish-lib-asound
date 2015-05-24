#define _GNU_SOURCE

// libasound2-dev
#include <alsa/asoundlib.h>

#include <poll.h>
#include <limits.h>

#include <string.h> //strdup

#include <fish-util.h>

#define FASOUND_MAX_SOUND_CARDS 5
#define FASOUND_MAX_ELEMS 10
#define FASOUND_MAX_FDS 5 // per card
#define FASOUND_MAX_ELEM_NAME_SIZE 15
#define FASOUND_MAX_CARD_NAME_HW_SIZE 15 // e.g. hw:99
#define FASOUND_MAX_CARD_NAME_STRING_SIZE 100 // e.g. USB audio generic etc.

#define FASOUND_OPTIONS_QUIET   0x01

#define FASOUND_CHAN_ALL    -1
    
bool fasound_init(int options, 
        const char *card_names_string[FASOUND_MAX_SOUND_CARDS], 
        const char *card_names_hw[FASOUND_MAX_SOUND_CARDS],
        const char *ctls[FASOUND_MAX_SOUND_CARDS][FASOUND_MAX_ELEMS],
        int fds[FASOUND_MAX_SOUND_CARDS][FASOUND_MAX_FDS]
);

bool fasound_set(int card, int ctl, int chan, double val_perc);
bool fasound_set_rel(int card, int ctl, int chan, int delta_perc);

bool fasound_update(int, int, bool*);
bool fasound_get(int, int, double*);
bool fasound_handle_event(int);
bool fasound_finish();

/* Copy of warn from fish_util.
 * Name 'warn' clashes with perl.h.
 */
void f_warn(const char* format, ...) ;

