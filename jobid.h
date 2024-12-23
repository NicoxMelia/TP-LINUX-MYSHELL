#ifndef JOBID_H
#define JOBID_H

#include <stdio.h>
#include <sys/types.h>


void setJobId(pid_t id);
pid_t getJobId();

#endif