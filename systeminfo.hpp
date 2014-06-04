/**
 * systeminfo.hpp - 
 * @author: Jonathan Beard
 * @version: Wed Apr 23 15:32:06 2014
 * 
 * Copyright 2014 Jonathan Beard
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _SYSTEMINFO_HPP_
#define _SYSTEMINFO_HPP_  1
#include <string>

/**
 * TODO list:
 * 1) Add getrlimit info
 * 2) Add /proc info such as context swap data, add option of specifying thread/proc id
 * 3) Add /proc/<pid>/stat info
 * 4) Add processor specific performance monitors, which will enable things like branch predictors,etc.
 */

/**
 * enum Trait - defines all the system parameters
 * for which we typically have information and 
 * corresponding methods are defined internally
 * to get the information.
 */
 
struct ProcStatData{
   int pid;
   char executable[100];
   char state;
   int parent_pid;
   int group_id;
   int session_id;
   int tty_nr; /* controlling terminal */
   int foreground_id; /* id of foreground process group of controlling terminal process */
   unsigned int flags;
   long unsigned int minor_faults;
   long unsigned int child_minor_faults;
   long unsigned int major_faults;
   long unsigned int child_major_faults;
   long unsigned int uptime;
   long unsigned int scheduled_time; /* in clock ticks, divide by sysconf(__SC_CLK_TCK) */
   long int child_uptime;
   long int child_scheduled_time;
   long int priority;
   long int nice;
   long int number_threads;
   long int itrealvalue; /* not used */
   long long unsigned int start_time; /* in jiffies */
   long unsigned int virtual_mem_size_bytes;
   long int resident_mem_size;
   long unsigned int resident_mem_soft_limit;
   long unsigned int startcode; /* address above which program text can run */
   long unsigned int endcode; /* address below which program text can run */
   long unsigned int startstack; /* bottom of stack */
   long unsigned int curr_esp; /* current value of stack pointer */
   long unsigned int curr_eip; /* current instruction pointer */ 
   long unsigned int signal_unused;
   long unsigned int signal_ignore_unused;
   long unsigned int signal_caught_unused;
   long unsigned int channel;
   long unsigned int pages_swapped;
   long unsigned int cumulative_child_swapped_pages;
   int exit_signal;
   int processor_last_executed_on;
   unsigned int rt_schedule; /* 0-99 for RT process, otherwise 0 */
   unsigned int policy; /* defined in linux/sched.h */
   long long unsigned int delayed_io_ticks; /* clock ticks process was delayed for io */
   long unsigned int guest_time; /* time spent running a virtual cpu for guest OS */
   long int child_guest_time;
};


struct ProcStatusData{
   int voluntary_context_swaps;
   int non_voluntary_context_swaps;
}; 
enum Trait {
   LevelOneICacheSize = 0,
   LevelOneICacheAssociativity,
   LevelOneICacheLineSize,
   LevelOneDCacheSize,
   LevelOneDCacheAssociativity,
   LevelOneDCacheLineSize,
   LevelTwoCacheSize,
   LevelTwoCacheAssociativity,
   LevelTwoCacheLineSize,
   LevelThreeCacheSize,
   LevelThreeCacheAssociativity,
   LevelThreeCacheLineSize,
   LevelFourCacheSize,
   LevelFourCacheAssociativity,
   LevelFourCacheLineSize,
   NumberOfProcessors,
   ProcessorName,
   ProcessorFrequency,
   SystemName,
   NodeName,
   OSRelease,
   OSVersion,
   MachineName,
   UpTime,
   OneMinLoad,
   FiveMinLoad,
   FifteenMinLoad,
   TotalMainMemory,
   FreeRam,
   SharedRam,
   BufferRam,
   TotalSwap,
   FreeSwap,
   NumberOfProcessesRunning,
   TotalHighMemory,
   FreeHighMemory,
   MemoryUnit,
   Scheduler,
   Priority,
#ifdef __linux
   VirtualMemory,
   CoreFile,
   CPUTime,
   DataSegment,
   MaxFileSize,
   LockLimit,
   MaxMemLock,
   MsgQueueLimit,
   MaxNice,
   MaxFD,
   MaxNumProcesses,
   MaxRAMPages,
   MaxPriority,
   MaxRTime,
   MaxSignalQueue,
   MaxStackSize,
MemTotal,
MemFree,
Buffers,
Cached,
SwapCached,
Active,
Inactive,
Activeanon,
Inactiveanon,
Activefile,
Inactivefile,
SwapTotal,
SwapFree,
Dirty,
Writeback,
AnonPages,
Mapped,
Shmem,
Slab,
SReclaimable,
SUnreclaim,
KernelStack,
PageTables,
CommitLimit,
Committed_AS,
VMallocTotal,
VMallocUsed,
VMallocChunk,
HardwareCorrupted,
AnonHugePages,
HugePages_Total,
HugePages_Free,
Hugepagesize,
	voluntary_ctxt_switches,
	nonvoluntary_ctxt_switches,
pid1,
executable,
state,
parent_pid,
group_id,
session_id,
tty_nr,
foreground_id,
flags,
minor_faults,
child_minor_faults,
major_faults,
child_major_faults,
uptime,
scheduled_time,
child_uptime,
child_scheduled_time,
priority1,
nice1,
number_threads,
itrealvalue,
start_time,
virtual_mem_size_bytes,
resident_mem_size,
resident_mem_soft_limit,
startcode,
endcode,
startstack,
curr_esp,
curr_eip,
signal_unused,
signal_ignore_unused,
signal_caught_unused,
channel,
pages_swapped,
cumulative_child_swapped_pages,
exit_signal,
processor_last_executed_on,
rt_schedule,
policy,
delayed_io_ticks,
guest_time,
child_guest_time,	
#endif
   N
};

int getrlimit_trait (const Trait trait);
std::string schedule_str (const int schedule);
int cache_handle (const Trait trait);
int parse_named_value (const char *path, const char *name, char *buf);
std::string cstr_to_string (const char *cstr);

class SystemInfo
{
public:
   SystemInfo()            = delete;
   virtual ~SystemInfo()   = delete;

   static std::string sysinfo_to_string (const Trait trait, struct sysinfo info);

   /**
    * getSystemProperty - call with a trait from the enum defined
    * above, returns the property from whatever system / processor
    * calls are available.  If there is no info for that field then
    * zero is returned as a string.
    * @param trait - const Trait
    * @return  - std::string representation of the system property
    */
   static std::string getSystemProperty (const Trait trait, int pid);
   
   static struct ProcStatData data;
   /**
    * getName - raturn the string name of the trait passed in
    * by the parameter.
    * @param   trait - const Trait
    * @return  std::string - name of system trait
    */
   static const char *getName (const Trait trait)
{
 	static const char *traitStrings[Trait::N] = {
		"LevelOneICacheSize",
		"LevelOneICacheAssociativity",
		"LevelOneICacheLineSize",
		"LevelOneDCacheSize",
		"LevelOneDCacheAssociativity",
		"LevelOneDCacheLineSize",
		"LevelTwoCacheSize",
		"LevelTwoCacheAssociativity",
		"LevelTwoCacheLineSize",
		"LevelThreeCacheSize",
		"LevelThreeCacheAssociativity",
		"LevelThreeCacheLineSize",
		"LevelFourCacheSize",
		"LevelFourCacheAssociativity",
		"LevelFourCacheLineSize",
		"NumberOfProcessors",
		"ProcessorName",
		"ProcessorFrequency",
		"SystemName",
		"NodeName",
		"OSRelease",
		"OSVersion",
		"MachineName",
		"UpTime",
		"OneMinLoad",
		"FiveMinLoad",
		"FifteenMinLoad",
		"TotalMainMemory",
		"FreeRam",
		"SharedRam",
		"BufferRam",
		"TotalSwap",
		"FreeSwap",
		"NumberOfProcessesRunning",
		"TotalHighMemory",
		"FreeHighMemory",
		"MemoryUnit",
		"Scheduler",
		"Priority",
		"VirtualMemory",
		"CoreFile",
		"CPUTime",
		"DataSegment",
		"MaxFileSize",
		"LockLimit",
		"MaxMemLock",
		"MsgQueueLimit",
		"MaxNice",
		"MaxFD",
		"MaxNumProcesses",
		"MaxRAMPages",
		"MaxPriority",
		"MaxRTime",
		"MaxSignalQueue",
		"MaxStackSize",
		"MemTotal",
		"MemFree",
		"Buffers",
		"Cached",
		"SwapCached",
		"Active",
		"Inactive",
		"Active(anon)",
		"Inactive(anon)",
		"Active(file)",
		"Inactive(file)",
		"SwapTotal",
		"SwapFree",
		"Dirty",
		"Writeback",
		"AnonPages",
		"Mapped",
		"Shmem",
		"Slab",
		"SReclaimable",
		"SUnreclaim",
		"KernelStack",
		"PageTables",
		"CommitLimit",
		"Committed_AS",
		"VMallocTotal",
		"VMallocUsed",
		"VMallocChunk",
		"HardwareCorrupted",
		"AnonHugePages",
		"HugePages_Total",
		"HugePages_Free",
		"Hugepagesize",
		"voluntary_ctxt_switches",
		"nonvoluntary_ctxt_switches",
"pid",
"executable",
"state",
"parent_pid",
"group_id",
"session_id",
"tty_nr",
"foreground_id",
"flags",
"minor_faults",
"child_minor_faults",
"major_faults",
"child_major_faults",
"uptime",
"scheduled_time",
"child_uptime",
"child_scheduled_time",
"priority1",
"nice1",
"number_threads",
"itrealvalue",
"start_time",
"virtual_mem_size_bytes",
"resident_mem_size",
"resident_mem_soft_limit",
"startcode",
"endcode",
"startstack",
"curr_esp",
"curr_eip",
"signal_unused",
"signal_ignore_unused",
"signal_caught_unused",
"channel",
"pages_swapped",
"cumulative_child_swapped_pages",
"exit_signal",
"processor_last_executed_on",
"rt_schedule",
"policy",
"delayed_io_ticks",
"guest_time",
"child_guest_time"};

	return traitStrings[trait];
}

   /**
    * getNumTraits - returns the total number of defined traits, which
    * is the value Trait::N defined above.
    * @return  size_t - number of traits.
    */
   static size_t        getNumTraits();
protected:
   /**
    * getUTSNameInfo - helper method to get UTSName info for both
    * OS X and Linux platforms.
    * @param t - const Trait
    * @return  - std::string - string representation of sytem property
    */
   static std::string   getUTSNameInfo( const Trait t );

};
#endif /* END _SYSTEMINFO_HPP_ */
