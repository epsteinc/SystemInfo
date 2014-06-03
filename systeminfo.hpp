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
	Name,
	State,
	Tgid,
	Pid,
	PPid,
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
   static std::string   getSystemProperty( const Trait trait );
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
		"Name",
		"State",
		"Tgid",
		"Pid",
		"PPid"};

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
