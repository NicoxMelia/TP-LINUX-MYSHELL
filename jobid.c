#include "jobid.h"


pid_t jobId;

void setJobId(pid_t id){
    jobId = id;
}

pid_t getJobId(){
    return jobId;
}