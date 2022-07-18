#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "slurm/slurm.h"
#include "slurm/slurm_errno.h"

#include "src/common/list.h"
#include "src/common/macros.h"
#include "src/common/parse_time.h"
#include "src/common/select.h"
#include "src/common/slurm_protocol_api.h"
#include "src/common/xmalloc.h"
#include "src/common/xstring.h"

#include "src/slurmctld/burst_buffer.h"
#include "src/slurmctld/locks.h"
#include "src/slurmctld/preempt.h"
#include "src/slurmctld/reservation.h"
#include "src/slurmctld/slurmctld.h"
#include "src/plugins/sched/sjf/sjf.h"

#ifndef BACKFILL_INTERVAL
#define BACKFILL_INTERVAL 30
#endif

// variables
static bool stop_sjf = false;
static pthread_mutex_t term_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  term_cond = PTHREAD_COND_INITIALIZER;
static int sjf_interval = BACKFILL_INTERVAL;

// functions
extern void stop_sjf_agent(void){
	slurm_mutex_lock(&term_lock);
	stop_sjf=true;
	slurm_cond_signal(&term_cond);
	slurm_mutex_unlock(&term_lock);
}

static void sjf_sleep(int sec){
	struct timespec ts = {0, 0};
	struct timeval now;

	gettimeofday(&now, NULL);
	ts.tv_sec = now.tv_sec + sec;
	ts.tv_nsec= now.tv_usec*1000;
	slurm_mutex_lock(&term_lock);
	if(!stop_sjf){
		slurm_cond_timedwait(&term_cond, &term_lock, &ts);
	}
	slurm_mutex_unlock(&term_lock);
}

static void display_job_list(){

}

// sort queue by time
extern void sort_by_time(List l){
	
}

extern void *sjf_agent(void *args){
	time_t now;
	double wait_time;
	static time_t last_sched_time=0;
	slurmctld_lock_t all_locks = {READ_LOCK, WRITE_LOCK, READ_LOCK, READ_LOCK, READ_LOCK};

	last_sched_time=time(NULL);
	while(!stop_sjf){
		sjf_sleep(sjf_interval);
		now = time(NULL);
		wait_time=difftime(now, last_sched_time);
		if(wait_time<sjf_interval){
			continue;
		}

		lock_slurmctld(all_locks);
		// process scheduling here
		unlock_slurmctld(all_locks);
	}

	return NULL;
}





