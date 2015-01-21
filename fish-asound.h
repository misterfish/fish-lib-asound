#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

// libasound2-dev
#include <alsa/asoundlib.h>

#include <poll.h>
#include <limits.h>

#include <string.h> //strdup

#include <fish-util.h>

#define NUM_CTLS 4

// see enum _snd_mixer_selem_channel_id in mixer.h
#define CHAN_MIN 0
#define CHAN_MAX 8
#define NUM_CHANS 9

#define MAX_SOUND_CARDS 5
#define MAX_ELEMS 10
#define MAX_FDS 5 // per card
#define MAX_ELEM_NAME_SIZE 15
#define MAX_CARD_NAME_HW_SIZE 15 // e.g. hw:99
#define MAX_CARD_NAME_STRING_SIZE 100 // e.g. USB audio generic etc.

#define FASOUND_OPTIONS_QUIET   0x01

/*
#define F_ASOUND_END 0
#define F_ASOUND_MASTER 0x01
#define F_ASOUND_PCM 0x01
#define F_ASOUND_SPEAKER 0x01
#define F_ASOUND_HEADPHONE 0x01
*/
    
#define f_warnp(x, ...) do {\
    char *pref = f_get_warn_prefix(__FILE__, __LINE__); \
    int len = strlen(pref); \
    char *warning = str(__FISH_WARN_LENGTH); \
    snprintf(warning, __FISH_WARN_LENGTH, x, ##__VA_ARGS__); \
    int len2 = strnlen(warning, __FISH_WARN_LENGTH);  \
    char *new = str(len + len2 + 1);   \
    sprintf(new, "%s%s", pref, warning);  \
    f_warn(new); \
    free(warning); \
    free(new); \
} while (0);

#define f_piep do { \
    f_warn("Something's wrong (%s:%d)", __FILE__, __LINE__); \
} while(0) ;

#define f_pieprf do { \
    f_piep; \
    return false; \
} while (0) ;

#define f_piepr do { \
    f_piep; \
    return; \
} while (0) ;

#define f_piepbr do { \
    f_piep; \
    break; \
} while (0) ;

#define f_piepc do { \
    f_piep; \
    continue; \
} while (0) ;

#define f_pieprnull do { \
    f_piep; \
    return null; \
} while (0) ;

#define f_pieprneg1 do { \
    f_piep; \
    return -1; \
} while (0) ;

#define f_piepr0 do { \
    f_piep; \
    return 0; \
} while (0) ;

#define _errorrf(x) do { \
    _error(x); \
    return false; \
} while (0);

#define _errorrnull(x) do { \
    _error(x); \
    return NULL; \
} while (0);

#define _errormsg(errnum, msg, msg_strlen) { \
    const char *err = snd_strerror(errnum); \
    char *s; \
    if (msg) { \
        s = str(msg_strlen + strlen(err) + 3 + 1); \
        sprintf(s, "%s (%s)", msg, err); \
        f_warnp(s); \
    } \
    else { \
        f_warnp(err); \
    } \
} while (0);

#define _error(errnum) do { \
    _errormsg(errnum, NULL, 0); \
} while (0);

bool fasound_init(int options, 
        const char *card_names_string[MAX_SOUND_CARDS], 
        const char *card_names_hw[MAX_SOUND_CARDS],
        const char *ctls[MAX_SOUND_CARDS][MAX_ELEMS],
        int fds[MAX_SOUND_CARDS][MAX_FDS]
);
bool fasound_set(int, int, double);
bool fasound_set_rel(int, int, int);
bool fasound_update(int, int, bool*);
bool fasound_get(int, int, double*);
bool fasound_handle_event(int);
bool fasound_finish();

/* Copy of warn from fish_util.
 * Name 'warn' clashes with perl.h.
 */
void f_warn(const char* format, ...) ;

