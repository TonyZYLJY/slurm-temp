#ifndef _SLURM_SJF_H
#define _SLURM_SJF_H

extern void *sjf_agent(void *args);

extern void stop_sjf_agent(void);

extern void sjf_reconfig(void);

#endif
