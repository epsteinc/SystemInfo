/**
 * systeminfo.cpp - 
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
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cinttypes>
#include <sys/utsname.h>

#if __linux
#include <unistd.h>
#include <sys/sysinfo.h>
#ifndef __USE_GNU
#define __USE_GNU 1
#endif
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>

/** just in case thee aren't defined, go ahead and define them **/
#ifndef  SCHED_BATCH
#define  SCHED_BATCH 3
#endif
#ifndef  SCHED_IDLE
#define  SCHED_IDLE  5
#endif

#endif

#if __APPLE__
#include <errno.h>
#include <sys/sysctl.h>
#include <libProc.h>
#endif

#include "systeminfo.hpp"

int getrlimit_trait (const Trait trait)
{
   	struct rlimit rlim;
   	int val = 0;
   	
   	switch (trait) {
   		case (VirtualMemory): 
   			val = getrlimit(RLIMIT_AS, &rlim);
   			break;
   		case (CoreFile): 
   		   	val = getrlimit(RLIMIT_CORE, &rlim);
   			break;
   		case (CPUTime):
   			val = getrlimit(RLIMIT_CPU, &rlim);
   			break;
		case (DataSegment):
   			val = getrlimit(RLIMIT_DATA, &rlim);
   			break;		 
		case (MaxFileSize): 
   			val = getrlimit(RLIMIT_FSIZE, &rlim);
   			break;		
		case (LockLimit): 
   			val = getrlimit(RLIMIT_LOCKS, &rlim);
   			break;		
		case (MaxMemLock): 
   			val = getrlimit(RLIMIT_MEMLOCK, &rlim);
   			break;		
		case (MsgQueueLimit):
   			val = getrlimit(RLIMIT_MSGQUEUE, &rlim);
   			break;		
		case (MaxNice):
   			val = getrlimit(RLIMIT_NICE, &rlim);
   			break;		
		case (MaxFD):
   			val = getrlimit(RLIMIT_NOFILE, &rlim);
   			break;		
		case (MaxNumProcesses):
   			val = getrlimit(RLIMIT_NPROC, &rlim);
   			break;		
		case (MaxRAMPages):
   			val = getrlimit(RLIMIT_RSS, &rlim);
   			break;		
		case (MaxPriority):
   			val = getrlimit(RLIMIT_RTPRIO, &rlim);
   			break;		
		case (MaxRTime):
#ifdef RLIMIT_RTTIME
   			val = getrlimit(RLIMIT_RTTIME, &rlim);
#endif   			
   			break;		
		case (MaxSignalQueue):
   			val = getrlimit(RLIMIT_SIGPENDING, &rlim);
   			break;		
		case (MaxStackSize):
   			val = getrlimit(RLIMIT_STACK, &rlim);
   			break;		
   	}

   	if (val < 0)
   		perror("getrlimit");
   	
   	return rlim.rlim_max;
}

std::string schedule_str (const int schedule)
{
	switch (schedule) {
		case SCHED_OTHER:
			return "SCHED_OTHER";
		case SCHED_BATCH:
			return "SCHED_BATCH";
		case SCHED_IDLE:
			return "SCHED_IDLE";
		case SCHED_FIFO:
			return "SCHED_FIFO";
		case SCHED_RR:
			return "SCHED_RR";
	}
}

int cache_handle (const Trait trait)
{
	switch (trait) {
		case LevelOneICacheSize:
			return _SC_LEVEL1_ICACHE_SIZE;
		case LevelOneICacheAssociativity:
			return _SC_LEVEL1_ICACHE_ASSOC;
		case LevelOneICacheLineSize:
			return _SC_LEVEL1_ICACHE_LINESIZE;
		case LevelOneDCacheSize:
			return _SC_LEVEL1_DCACHE_SIZE;
		case LevelOneDCacheAssociativity:
			return _SC_LEVEL1_DCACHE_ASSOC;
		case LevelOneDCacheLineSize:
			return _SC_LEVEL1_DCACHE_LINESIZE;
		case LevelTwoCacheSize:
			return _SC_LEVEL2_CACHE_SIZE;
		case LevelTwoCacheAssociativity:
			return _SC_LEVEL2_CACHE_ASSOC;
		case LevelTwoCacheLineSize:
			return _SC_LEVEL2_CACHE_LINESIZE;
		case LevelThreeCacheSize:
			return _SC_LEVEL3_CACHE_SIZE;
		case LevelThreeCacheAssociativity:
			return _SC_LEVEL3_CACHE_ASSOC;
		case LevelThreeCacheLineSize:
			return _SC_LEVEL3_CACHE_LINESIZE;
		case LevelFourCacheSize:
			return _SC_LEVEL4_CACHE_SIZE;
		case LevelFourCacheAssociativity:
			return _SC_LEVEL4_CACHE_ASSOC;
		case LevelFourCacheLineSize:
			return _SC_LEVEL4_CACHE_LINESIZE;
	}
	
	return 0;
}

std::string SystemInfo::sysinfo_to_string (const Trait trait, struct sysinfo info)
{
	switch (trait) {
		case UpTime:
			return std::to_string(info.uptime);   
		case OneMinLoad:
			return std::to_string(info.loads[0]);
		case FiveMinLoad:
			return std::to_string(info.loads[1]);
		case FifteenMinLoad:
			return std::to_string(info.loads[2]);
		case TotalMainMemory:
			return std::to_string(info.totalram);
		case FreeRam:
			return std::to_string(info.freeram);
		case SharedRam:
			return std::to_string(info.sharedram);
		case BufferRam:
			return std::to_string(info.bufferram);
		case TotalSwap:
			return std::to_string(info.totalswap);
		case FreeSwap:
			return std::to_string(info.freeswap);
		case NumberOfProcessesRunning:
			return std::to_string(info.procs);
		case TotalHighMemory:
			return std::to_string(info.totalhigh);
		case FreeHighMemory:
			return std::to_string(info.freehigh);
		case MemoryUnit:
			return std::to_string(info.mem_unit);
	}
}

int parse_named_value (const char *path, const char *name, char *buf)
{
	FILE *fp = NULL;
      	char key[128], val[128];
      	int count = EOF;
      	
	errno = 0;
	
	if ((fp = fopen(path, "r")) == NULL)
		return -1;
		
	memset(key, 0, sizeof(key));
	memset(val, 0, sizeof(val));

	while ((count = fscanf(fp, "%[^:]:%[^\n]\n", key, val)) != EOF) {
		if (count == 2) {
			if (!strncmp(key, name, strlen(name))) {
				fclose(fp);
				fp = NULL;
				
				strcpy(buf, val);
				return 0;
			}
		}
	}

	if (fp) {
		fclose(fp);
		fp = NULL;
	}
	
	return -1;
}

std::string cstr_to_string (const char *cstr)
{
	std::string tmp(cstr);
	return tmp;
}

std::string
SystemInfo::getSystemProperty (const Trait trait)
{
#if __linux
	if (trait <= LevelFourCacheLineSize) {
		int handle = cache_handle(trait);
		long val(0);
		
		errno = 0;
		
		if ((val = sysconf(handle)) == -1)
			perror("Failed to get config info");

		return std::to_string(val);
	}
	else if (trait == NumberOfProcessors) {
		return std::to_string(get_nprocs()); 
	}
	else if (ProcessorName <= trait && trait <= ProcessorFrequency) {
   		char buf[128];
		const char *path = "/proc/cpuinfo";
	
		memset(buf, 0, sizeof(buf));
		
		switch (trait) {
			case ProcessorName: 
				parse_named_value("/proc/cpuinfo", "model name", buf);
				
				return cstr_to_string(buf);
			case ProcessorFrequency:
				parse_named_value(path, "cpu MHz", buf);
				
				errno = 0;
				uint64_t frequency(strtof(buf, (char**)NULL) * 1e6f);
				if (errno) {
					perror("Failed to convert frequency from /proc/cpuinfo");
					exit(EXIT_FAILURE);
				}
				return std::to_string(frequency);
		}
	}
	else if (SystemName <= trait && trait <= MachineName) {
		return SystemInfo::getUTSNameInfo(trait);
	}
	else if (UpTime <= trait && trait <= MemoryUnit) {
		struct sysinfo info;
		
		std::memset(&info, 0, sizeof(struct sysinfo));
		errno = 0;
		if (sysinfo(&info) != 0)
			perror( "Failed to get sysinfo!!" );
			
		return SystemInfo::sysinfo_to_string(trait, info);
	}
	else if (trait == Scheduler) {
		return schedule_str(sched_getscheduler(0));
	}
	else if( trait == Priority ) {
		errno = 0;
		int priority(getpriority(PRIO_PROCESS, 0 /* self */ ) );
		if (errno != 0)
			perror("Failed to get process priority");
		return std::to_string(priority);
	}
	else if (trait >= VirtualMemory && trait <= MaxStackSize) {
		return std::to_string(getrlimit_trait(trait));
	} 
	else if (trait >= MemTotal && trait <= Hugepagesize) {
		char buf[100];
		int pos = 0;
		const char *path = "/proc/meminfo";
	
		memset(buf, 0, sizeof(buf));
	
		parse_named_value(path, getName(trait), buf);
	
		while (isspace(buf[pos]))
			pos++;

		std::string tmp(&buf[pos]);
   		return tmp;
	}
	else if (trait >= Name && trait <= PPid) {
		char *path = (char *)malloc(128);
		int pid = 1;
		char buf[100];
		int pos = 0;
		
		sprintf(path, "/proc/%d/status", pid);
	
		memset(buf, 0, sizeof(buf));
	
		parse_named_value(path, getName(trait), buf);
	
		while (isspace(buf[pos]))
			pos++;

		std::string tmp(&buf[pos]);
		free(path);
   		return tmp;
	}
   
#elif __APPLE__
   typedef int mib_t;
   mib_t mib[4];
   std::memset( mib, 0, sizeof( mib_t ) * 4 );
   switch( trait )
   {
      case( LevelOneICacheSize ):
      {
         uint64_t size( 0 );
         size_t len( sizeof( size ) );
         mib[0] = CTL_HW;
         mib[1] = HW_L1ICACHESIZE;
         sysctl( mib, 
                 2, 
                 &size,
                 &len,
                 NULL,
                 0 );
         return( std::to_string( size ) );
      }
      break;
      case( LevelOneICacheAssociativity ):
      {
      }
      break;
      case( LevelOneICacheLineSize ):
      {
         uint64_t size( 0 );
         size_t len( sizeof( size ) );
         sysctlbyname( "hw.cachelinesize", 
                 &size,
                 &len,
                 NULL,
                 0 );
         return( std::to_string( size ) );
      }
      break;
      case( LevelOneDCacheSize ):
      {
         uint64_t size( 0 );
         size_t len( sizeof( size ) );
         mib[0] = CTL_HW;
         mib[1] = HW_L1DCACHESIZE;
         sysctl( mib, 
                 2, 
                 &size,
                 &len,
                 NULL,
                 0 );
         return( std::to_string( size ) );
      }
      break;
      case( LevelOneDCacheAssociativity ):
      {
      }
      break;
      case( LevelOneDCacheLineSize ):
      {
         uint64_t size( 0 );
         size_t len( sizeof( size ) );
         sysctlbyname( "hw.cachelinesize", 
                 &size,
                 &len,
                 NULL,
                 0 );
         return( std::to_string( size ) );
      }
      break;
      case( LevelTwoCacheSize ):
      {
         uint64_t size( 0 );
         size_t len( sizeof( size ) );
         mib[0] = CTL_HW;
         mib[1] = HW_L2CACHESIZE;
         sysctl( mib, 
                 2, 
                 &size,
                 &len,
                 NULL,
                 0 );
         return( std::to_string( size ) );
      }
      break;
      case( LevelTwoCacheAssociativity ):
      {
         uint64_t assoc( 0 );
         size_t len( sizeof( assoc ) );
         sysctlbyname( "machdep.cpu.cache.L2_associativity", 
                 &assoc,
                 &len,
                 NULL,
                 0 );
         return( std::to_string( assoc ) );
      }
      break;
      case( LevelTwoCacheLineSize ):
      {
         uint64_t size( 0 );
         size_t len( sizeof( size ) );
         sysctlbyname( "hw.cachelinesize", 
                 &size,
                 &len,
                 NULL,
                 0 );
         return( std::to_string( size ) );
      }
      break;
      case( LevelThreeCacheSize ):
      {
         uint64_t size( 0 );
         size_t len( sizeof( size ) );
         mib[0] = CTL_HW;
         mib[1] = HW_L3CACHESIZE;
         sysctl( mib, 
                 2, 
                 &size,
                 &len,
                 NULL,
                 0 );
         return( std::to_string( size ) );
      }
      break;
      case( LevelThreeCacheAssociativity ):
      {
      }
      break;
      case( LevelThreeCacheLineSize ):
      {
         uint64_t size( 0 );
         size_t len( sizeof( size ) );
         sysctlbyname( "hw.cachelinesize", 
                 &size,
                 &len,
                 NULL,
                 0 );
         return( std::to_string( size ) );
      }
      break;
      case( LevelFourCacheSize ):
      {
      }
      break;
      case( LevelFourCacheAssociativity ):
      {
      }
      break;
      case( LevelFourCacheLineSize ):
      {
      }
      break;
      case( NumberOfProcessors ):
      {
         mib[0] = CTL_HW;
         mib[1] = HW_AVAILCPU;
         uint32_t n_procs( 0 );
         size_t len( sizeof( n_procs ) );
         sysctl( mib, 
                 2, 
                 &n_procs, 
                 &len, 
                 nullptr, 
                 0 );
         return( std::to_string( n_procs ) );
      }
      break;
      case( ProcessorName ):
      {
         const size_t buff_size( 1000 );
         char buff[ buff_size ];
         std::memset( buff,
                      '\0',
                      sizeof( char ) * buff_size );

         size_t len( sizeof( char ) *		char buf[100];
		int pos = 0;
		const char *path = "/proc/meminfo";
	
		memset(buf, 0, sizeof(buf));
	
		parse_named_value(path, getName(trait), buf);
	
		while (isspace(buf[pos]))
			pos++;

		std::string tmp(&buf[pos]);
   		return tmp; buff_size );
         sysctlbyname( "machdep.cpu.brand_string", 
                 buff,
                 &len,
                 NULL,
                 0 );
         return( std::string( buff ) );
      }
      break;
      case( ProcessorFrequency ):
      {
         mib[0] = CTL_HW;
         mib[1] = HW_CPU_FREQ;
         uint64_t freq( 0 );
         size_t len( sizeof( freq ) );
         sysctl(  mib, 
                  2, 
                  &freq, 
                  &len , 
                  nullptr, 
                  0 );
         return( std::to_string( freq ) );
      }
      break;
      case( SystemName ):
      case( NodeName ):
      case( OSRelease ):
      case( OSVersion ):
      case( MachineName ):
      {
         return( SystemInfo::getUTSNameInfo( trait ) );
      }
      break;
      case( UpTime ):
      {
         struct timeval uptime;
         size_t   len( sizeof( struct timeval ) );
         std::memset( &uptime, 0, len );
         mib[ 0 ] = CTL_KERN;
         mib[ 1 ] = KERN_BOOTTIME;
         errno = 0;
         if( sysctl( mib, 2, &uptime, &len, nullptr, 0 ) != 0 )
         {
            perror( "Failed to get uptime!" );
         }
         double sec( uptime.tv_sec );
         const double us( uptime.tv_usec * 1e-6f );
         sec += us;
         return( std::to_string( sec ) );
      }
      break;
      case( OneMinLoad ):
      {
         struct loadavg load;
         size_t len( sizeof( struct loadavg ) );
         std::memset( &load, 0, len );
         sysctlbyname( "vm.loadavg", 
                 &load,
                 &len,
                 NULL,
                 0 );
         return( std::to_string( (double) load.ldavg[0] / (double ) load.fscale ) );
      }
      break;
      case( FiveMinLoad ):
      {
         struct loadavg load;
         size_t len( sizeof( struct loadavg ) );
         std::memset( &load, 0, len );
         sysctlbyname( "vm.loadavg", 
                 &load,
                 &len,
                 NULL,
                 0 );
         return( std::to_string( (double) load.ldavg[1] / (double ) load.fscale ) );
      }
      break;
      case( FifteenMinLoad ):
      {
         struct loadavg load;
         size_t len( sizeof( struct loadavg ) );
         std::memset( &load, 0, len );
         sysctlbyname( "vm.loadavg", 
                 &load,
                 &len,
                 NULL,
                 0 );
         return( std::to_string( (double) load.ldavg[2] / (double ) load.fscale ) );
      }
      break;
      case( TotalMainMemory ):
      {
         uint64_t physmem( 0 );
         size_t   len( sizeof( physmem ) );
         mib[0] = CTL_HW;
         mib[1] = HW_MEMSIZE;
         errno = 0;
         if( sysctl( mib,
                        2,
                        &physmem,
                        &len,
                        nullptr,
                        0 ) != 0 )
         {
            perror( "Failed to get physical mem from sysctl." );
         }
         return( std::to_string( physmem ) );
      }
      break;
      case( FreeRam ):
      {
         /** get page size **/
         uint64_t pagesize( 0 );
         size_t   len( sizeof( pagesize ) );
         mib[0] = CTL_HW;
         mib[1] = HW_PAGESIZE;
         errno = 0;
         if( sysctl( mib,
                     2,
                     &pagesize,
                     &len,
                     nullptr,
                     0 ) != 0 )
         {
            perror( "Failed to get page size." );
         }
         uint64_t freepagecount( 0 );
         len = ( sizeof( freepagecount ) );
         errno = 0;
         if( sysctlbyname( "vm.page_free_count",
                           &freepagecount,
                           &len,
                           nullptr,
                           0 ) != 0 )
         {
            perror( "Failed to get free page count." );
         }
         return( std::to_string( pagesize * freepagecount ) );
      }
      break;
      case( SharedRam ):
      {
      }
      break;
      case( BufferRam ):
      {
      }
      break;
      case( TotalSwap ):
      {
          struct xsw_usage swap;
          size_t len( sizeof(  struct xsw_usage ) );
          std::memset( &swap, 0 , len );
          errno = 0;
          if( sysctlbyname( "vm.swapusage",
                            &swap,
                            &len,
                            nullptr,
                            0 ) != 0 )
          {
            perror( "Failed to get swap usage" );
          }
          return( std::to_string( swap.xsu_total ) );
      }
      break;
      case( FreeSwap ):
      {
          struct xsw_usage swap;
          size_t len( sizeof(  struct xsw_usage ) );
          std::memset( &swap, 0 , len );
          errno = 0;
          if( sysctlbyname( "vm.swapusage",
                            &swap,
                            &len,
                            nullptr,
                            0 ) != 0 )
          {
            perror( "Failed to get swap usage" );
          }
          return( std::to_string( swap.xsu_avail ) );
      }
      break;
      case( NumberOfProcessesRunning ):
      {
         const auto numberOfProcesses( proc_listpids( PROC_ALL_PIDS,
                                                      0,
                                                      nullptr,
                                                      0 ) );
         return( std::to_string( numberOfProcesses ) );
      }
      break;
      case( TotalHighMemory ):
      {
      }
      break;
      case( FreeHighMemory ):
      {
      }
      break;
      case( MemoryUnit ):
      {
         return( std::to_string( 1 ) );
      }
      break;
      case( Scheduler ):
      {
         const size_t buff_size( 100 );
         char buffer[ buff_size ];
         std::memset( buffer, '\0', buff_size * sizeof( char ) );
         size_t len( buff_size );
         errno = 0;
         if( sysctlbyname( "kern.sched",
                           buffer,
                           &len,
                           nullptr,
                           0 ) != 0 )
         {
            perror( "Failed to get scheduler." );
         }
         return( std::string( buffer ) );
      }
      break;
      case( Priority ):
      {
         errno = 0;
         int priority( getpriority( PRIO_PROCESS, 0 /* self */ ) );
         if( errno != 0 )
         {
            perror( "Failed to get process priority" );
         }
         return( std::to_string( priority ) );
      }
      break;
      default:
         break;
   }
#endif
   return( std::to_string( 0 ) );
}


size_t
SystemInfo::getNumTraits()
{
   return( Trait::N );
}

std::string 
SystemInfo::getUTSNameInfo( const Trait t )
{
      struct utsname un;
      std::memset( &un, 
                   0,
                   sizeof( struct utsname ) );
      errno = 0;
      if( uname( &un ) != 0 )
      {
         perror( "Failed to get umame data!!" );
      }
      switch( t )
      {
         case( SystemName ):
         {
            return( std::string( un.sysname ) );     
         }
         break;
         case( NodeName ):
         {
            return( std::string( un.nodename ) );
         }
         break;
         case( OSRelease ):
         {
            return( std::string( un.release ) );
         }
         break;
         case( OSVersion ):
         {
            return( std::string( un.version ) );
         }
         break;
         case( MachineName ):
         {
            return( std::string( un.machine ) );
         }
         break;
         default:
            break;
      }
      return( std::string( 0 ) );
}
