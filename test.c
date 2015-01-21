// for getline
#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <fish-util.h>

#include "fasound.h"

void sig_handler(int signum) {
    // When called within readline, this keeps it from breaking the readline
    // but not exiting.
    if (signum == SIGINT) {
        info("Ctl-c detected.");
    }
    else {
        say ("Got unexpected signal %d", signum);
    }
}

int main(int argc, char** argv) {
    char *objects;
    int num_objects;
    if (!fasound_init(&objects, &num_objects))
        return -1;

    size_t size;
    char* buf = NULL;

    f_sig(SIGINT, (void*) sig_handler);

    say("Press enter to read.");

    // getline allocates buf.
    while (-1 != getline(&buf, &size, stdin)) {
        if (! strncmp(buf, "\n", 1)) {
            int val;
            if (!fasound_get(0, &val)) 
                pieprneg1;

            _();
            spr("%d", val);
            M(_s);
            say("Got master val: %s", _t);

            if (!fasound_get(1, &val))
                pieprneg1;
            _();
            spr("%d", val);
            M(_s);
            say("Got pcm val: %s", _t);
        }
        else {
            // 0 if weird string.
            int val = atoi(buf);
            if (!fasound_set(0, val)) 
                pieprneg1;
        }
    }
    if (!fasound_finish())
        pieprneg1;

    return 0;
}


