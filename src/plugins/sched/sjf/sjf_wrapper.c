#include <stdio.h>
#include "slurm/slurm_errno.h"
#include "src/common/plugin.h"
#include "src/common/select.h"
#include "src/slurmctld/job_scheduler.h"
#include "src/slurmctld/reservation.h"
#include "src/slurmctld/slurmctld.h"

const char     plugin_name[]  = "Slurm SJF Scheduler  plugin";
const char     plugin_type[]  = "sched/sjf";
const uint32_t plugin_version = SLURM_VERSION_NUMBER;

static pthread_t       sjf_thread = 0;
static pthread_mutex_t thread_flag_mutex = PTHREAD_MUTEX_INITIALIZER;

int init(void){
	sched_verbose("SJF scheduler plugin loaded");
	
	slurm_mutex_lock(&thread_flag_mutex);
	if(sjf_thread){
		debug2("SJF scheduler thread already running, not starting another");
		slurm_mutex_unlock(&thread_flag_mutex);
		return SLURM_ERROR;
	}

	
	slurm_mutex_unlock(&thread_flag_mutex);

	return SLURM_SUCCESS;
}
