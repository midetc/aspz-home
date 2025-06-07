#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

volatile sig_atomic_t handled = 0;
volatile sig_atomic_t sent    = 0;
timer_t timerid;

void handler(int sig) {
    int over = timer_getoverrun(timerid);
    sent += 1 + (over > 0 ? over : 0);
    handled++;
}

int main(void) {
    if (signal(SIGRTMIN, handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    struct sigevent sev = {0};
    sev.sigev_notify          = SIGEV_SIGNAL;
    sev.sigev_signo           = SIGRTMIN;
    sev.sigev_value.sival_ptr = &timerid;

    if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1) {
        perror("timer_create");
        exit(EXIT_FAILURE);
    }

    struct itimerspec its = {{0, 1000000}, {0, 1000000}};
    if (timer_settime(timerid, 0, &its, NULL) == -1) {
        perror("timer_settime");
        exit(EXIT_FAILURE);
    }

    printf("Timer started: signals every 1 ms for 2 seconds...\n");
    fflush(stdout);

    sleep(2);

    its.it_value.tv_sec    = 0;
    its.it_value.tv_nsec   = 0;
    its.it_interval        = its.it_value;
    timer_settime(timerid, 0, &its, NULL);

    sleep(1);

    printf("Sent (with overruns): %d\n", sent);
    printf("Handler calls:        %d\n", handled);
    printf("Lost signals:         %d\n", sent - handled);

    timer_delete(timerid);
    return 0;
}
